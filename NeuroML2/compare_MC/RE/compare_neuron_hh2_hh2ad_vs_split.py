#!/usr/bin/env python3
"""
Compare pure NEURON RE hh2 cell using:

- Combined Traub mechanism `hh2ad` from HH2.mod
- Split NeuroML-exported mechanisms `hh2_na.mod` + `hh2_k.mod`

Both simulations are run separately by:
- `run_neuron_hh2.py` (hh2ad combined mechanism)
- `run_neuron_hh2_split.py` (hh2_na + hh2_k split mechanisms)

Both use identical geometry, passive leak, temperature, and stimulus.

For now we only compare the membrane voltage traces (no gates/currents).
"""
from __future__ import annotations

import json
from pathlib import Path

import numpy as np
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


BASE_DIR = Path(__file__).resolve().parent
OUT_DIR = BASE_DIR / "compare_out" / "hh2_hh2ad_vs_split_neuron"

OUT_DIR.mkdir(parents=True, exist_ok=True)


def _plot_overlay_and_diff(x_ms, y_ad, y_split, title, ylabel, fname):
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7), sharex=True)

    ax1.plot(x_ms, y_ad, "b-", lw=1.6, label="hh2ad")
    ax1.plot(x_ms, y_split, "m--", lw=1.2, label="hh2_na+hh2_k")
    ax1.set_title(title)
    ax1.set_ylabel(ylabel)
    ax1.grid(True, ls="--", alpha=0.6)
    ax1.legend()

    diff = y_ad - y_split
    ax2.plot(x_ms, diff, color="#2ca02c", lw=1.2)
    ax2.axhline(0.0, color="k", lw=0.8, ls=":")
    ax2.set_xlabel("Time (ms)")
    ax2.set_ylabel("Δ")
    ax2.grid(True, ls="--", alpha=0.6)

    fig.tight_layout()
    fig.savefig(OUT_DIR / fname, dpi=300, bbox_inches="tight")
    plt.close(fig)


def compare():
    print("=" * 80)
    print("Comparing RE hh2: hh2ad vs hh2_na+hh2_k (pure NEURON)")
    print("=" * 80)

    # Combined Traub mechanism (hh2ad) from HH2.mod
    ad_path = BASE_DIR / "NEURON_hh2_data.json"
    with ad_path.open() as f:
        data_ad = json.load(f)

    # Split NeuroML-exported mechanisms (hh2_na + hh2_k)
    split_path = BASE_DIR / "NEURON_hh2_split_data.json"
    with split_path.open() as f:
        data_split = json.load(f)

    d_ad = data_ad["simData"]
    d_split = data_split["simData"]

    # Time stored in ms in the JSON
    t_ad = np.array(d_ad["t"], dtype=float)
    t_split = np.array(d_split["t"], dtype=float)

    n = min(len(t_ad), len(t_split))
    t_ms = t_ad[:n]

    if not np.allclose(t_ad[:n], t_split[:n]):
        print("[warn] Time vectors differ; using hh2ad time axis for alignment.")

    v_ad = np.array(d_ad["V_soma"], dtype=float)[:n]
    v_split = np.array(d_split["V_soma"], dtype=float)[:n]

    _plot_overlay_and_diff(
        t_ms,
        v_ad,
        v_split,
        "Membrane voltage: RE hh2 hh2ad vs hh2_na+hh2_k",
        "V_soma (mV)",
        "voltage_overlay_diff_hh2_hh2ad_vs_split.png",
    )

    print("\nComparison complete. See:", OUT_DIR)


if __name__ == "__main__":
    compare()

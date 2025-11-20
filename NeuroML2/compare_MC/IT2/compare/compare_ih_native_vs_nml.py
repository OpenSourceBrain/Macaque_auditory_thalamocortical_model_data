#!/usr/bin/env python3
"""
Compare full-geometry IT2 simulations using:

- Native Ih channel `ih` (h_kole.mod) + pas
  -> compare/NEURON_ih_native.json
- NeuroML-exported `ih_nml` (ih_nml.mod) + pas
  -> compare/NEURON_ih_nml.json

Both use the same IT2 geometry and IClamp.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path

import numpy as np
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


SCRIPT_DIR = Path(__file__).resolve().parent      # IT2/compare
BASE_DIR = SCRIPT_DIR.parent                      # IT2/


def _plot_overlay_and_diff(x_ms, y_native, y_nml, title, ylabel, out_dir: Path, fname: str):
    out_dir.mkdir(parents=True, exist_ok=True)
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7), sharex=True)

    ax1.plot(x_ms, y_native, "b-", lw=1.4, label="ih native")
    ax1.plot(x_ms, y_nml, "m--", lw=1.2, label="ih_nml")
    ax1.set_title(title)
    ax1.set_ylabel(ylabel)
    ax1.grid(True, ls="--", alpha=0.6)
    ax1.legend()

    diff = y_native - y_nml
    ax2.plot(x_ms, diff, color="#ff7f0e", lw=1.2)
    ax2.axhline(0.0, color="k", lw=0.8, ls=":")
    ax2.set_xlabel("Time (ms)")
    ax2.set_ylabel("Δ")
    ax2.grid(True, ls="--", alpha=0.6)

    fig.tight_layout()
    fig.savefig(out_dir / fname, dpi=300, bbox_inches="tight")
    plt.close(fig)


def compare(native_json: Path, nml_json: Path, out_dir: Path, title: str, out_png_name: str):
    print("=" * 80)
    print("Comparing ih: native vs ih_nml (full IT2 geometry)")
    print("=" * 80)
    print(f"[paths] native JSON : {native_json}")
    print(f"[paths] nml JSON    : {nml_json}")

    with native_json.open() as f:
        d_native = json.load(f)["simData"]
    with nml_json.open() as f:
        d_nml = json.load(f)["simData"]

    t_native = np.array(d_native["t"], dtype=float)
    t_nml = np.array(d_nml["t"], dtype=float)

    v_native_raw = np.array(d_native["V_soma"], dtype=float)
    v_nml_raw = np.array(d_nml["V_soma"], dtype=float)

    n = min(len(t_native), len(t_nml), len(v_native_raw), len(v_nml_raw))
    t_ms = t_native[:n]

    dt_diff = np.max(np.abs(t_native[:n] - t_nml[:n]))
    if dt_diff > 1e-6:
        print(
            f"[warn] Time vectors differ by up to {dt_diff:.3e} ms; "
            "using native time axis and aligning by index."
        )
    else:
        print(
            f"[info] Time vectors nearly identical (max |Δt| = {dt_diff:.3e} ms); "
            "aligning by index."
        )

    v_native = v_native_raw[:n]
    v_nml = v_nml_raw[:n]

    diff = v_native - v_nml
    print(f"[stats] V_native range: {v_native.min():.5f} .. {v_native.max():.5f} mV")
    print(f"[stats] V_nml    range: {v_nml.min():.5f} .. {v_nml.max():.5f} mV")
    print(f"[stats] mean Δ(V_native - V_nml): {diff.mean():.5f} mV")
    print(f"[stats] max |ΔV|: {np.max(np.abs(diff)):.5f} mV")

    _plot_overlay_and_diff(
        t_ms,
        v_native,
        v_nml,
        title,
        "V_soma (mV)",
        out_dir,
        out_png_name,
    )

    print("\nComparison complete. See:", out_dir)


def main():
    parser = argparse.ArgumentParser(
        description="Compare native ih vs ih_nml full-geometry NEURON simulations."
    )
    parser.add_argument(
        "--native-json",
        type=str,
        default=str(BASE_DIR / "compare" / "NEURON_ih_native.json"),
        help="Path to native ih JSON (default: IT2/compare/NEURON_ih_native.json)",
    )
    parser.add_argument(
        "--nml-json",
        type=str,
        default=str(BASE_DIR / "compare" / "NEURON_ih_nml.json"),
        help="Path to NML-exported ih_nml JSON (default: IT2/compare/NEURON_ih_nml.json)",
    )
    parser.add_argument(
        "--out-dir",
        type=str,
        default=str(SCRIPT_DIR / "ih_native_vs_nml"),
        help="Output directory for comparison plots/statistics.",
    )
    parser.add_argument(
        "--title",
        type=str,
        default="Membrane voltage: ih (native vs ih_nml)",
        help="Title for the voltage comparison plot.",
    )
    parser.add_argument(
        "--out-png-name",
        type=str,
        default="voltage_overlay_diff_ih_native_vs_nml.png",
        help="Filename for the output PNG plot.",
    )

    args = parser.parse_args()

    compare(
        native_json=Path(args.native_json),
        nml_json=Path(args.nml_json),
        out_dir=Path(args.out_dir),
        title=args.title,
        out_png_name=args.out_png_name,
    )


if __name__ == "__main__":
    main()


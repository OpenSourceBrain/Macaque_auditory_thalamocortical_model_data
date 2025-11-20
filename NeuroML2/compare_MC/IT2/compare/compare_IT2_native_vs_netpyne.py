#!/usr/bin/env python3
"""
Generic comparison tool for IT2_reduced (and similar) cells simulated in
pure NEURON vs NetPyNE using native mechanisms.

Default IT2 usage (when this file is under IT2/compare/):

- Native NEURON: run_neuron_IT2_native.py
  -> NEURON_IT2_reduced_data.json (in IT2/)
- NetPyNE: IT2_netpy.py
  -> IT2_reduced_all_data.json (in IT2/)

Traces are aligned by integer time step (index). Time vectors should be
identical (dt=0.01 ms), but we check for small floating-point jitter.

You can reuse this script for other cells by passing different JSON paths
and output directories via CLI arguments.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path

import numpy as np
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


SCRIPT_DIR = Path(__file__).resolve().parent          # IT2/compare
BASE_DIR = SCRIPT_DIR.parent                          # IT2/


def _plot_overlay_and_diff(
    x_ms,
    y_native,
    y_netpyne,
    title,
    ylabel,
    out_dir: Path,
    fname: str,
):
    out_dir.mkdir(parents=True, exist_ok=True)
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7), sharex=True)

    ax1.plot(x_ms, y_native, "b-", lw=1.4, label="NEURON native")
    ax1.plot(x_ms, y_netpyne, "g--", lw=1.2, label="NetPyNE (native mechs)")
    ax1.set_title(title)
    ax1.set_ylabel(ylabel)
    ax1.grid(True, ls="--", alpha=0.6)
    ax1.legend()

    diff = y_native - y_netpyne
    ax2.plot(x_ms, diff, color="#ff7f0e", lw=1.2)
    ax2.axhline(0.0, color="k", lw=0.8, ls=":")
    ax2.set_xlabel("Time (ms)")
    ax2.set_ylabel("Δ")
    ax2.grid(True, ls="--", alpha=0.6)

    fig.tight_layout()
    fig.savefig(out_dir / fname, dpi=300, bbox_inches="tight")
    plt.close(fig)


def compare(
    native_json: Path,
    netpyne_json: Path,
    out_dir: Path,
    title: str,
    out_png_name: str,
):
    print("=" * 80)
    print("Comparing cell (native): NEURON vs NetPyNE")
    print("=" * 80)
    print(f"[paths] native JSON : {native_json}")
    print(f"[paths] netpyne JSON: {netpyne_json}")

    # Native NEURON
    with native_json.open() as f:
        d_native = json.load(f)["simData"]

    # NetPyNE
    with netpyne_json.open() as f:
        d_np = json.load(f)["simData"]

    t_native = np.array(d_native["t"], dtype=float)
    t_np = np.array(d_np["t"], dtype=float)

    # NetPyNE stores V_soma as dict keyed by "cell_0"
    v_native_raw = np.array(d_native["V_soma"], dtype=float)
    v_np_raw = np.array(d_np["V_soma"]["cell_0"], dtype=float)

    n = min(len(t_native), len(t_np), len(v_native_raw), len(v_np_raw))
    t_ms = t_native[:n]

    dt_diff = np.max(np.abs(t_native[:n] - t_np[:n]))
    if dt_diff > 1e-6:
        print(
            f"[warn] Time vectors differ by up to {dt_diff:.3e} ms; "
            "using NEURON native time axis and aligning by index."
        )
    else:
        print(
            f"[info] Time vectors nearly identical (max |Δt| = {dt_diff:.3e} ms); "
            "aligning by index."
        )

    v_native = v_native_raw[:n]
    v_np = v_np_raw[:n]

    diff = v_native - v_np
    print(f"[stats] V_native range: {v_native.min():.5f} .. {v_native.max():.5f} mV")
    print(f"[stats] V_netpyne range: {v_np.min():.5f} .. {v_np.max():.5f} mV")
    print(f"[stats] mean Δ(V_native - V_netpyne): {diff.mean():.5f} mV")
    print(f"[stats] max |ΔV|: {np.max(np.abs(diff)):.5f} mV")

    _plot_overlay_and_diff(
        t_ms,
        v_native,
        v_np,
        title,
        "V_soma (mV)",
        out_dir,
        out_png_name,
    )

    print("\nComparison complete. See:", out_dir)


def main():
    parser = argparse.ArgumentParser(
        description=(
            "Compare NEURON-native vs NetPyNE simulations for IT2_reduced or "
            "similar cells, based on JSON outputs."
        )
    )
    parser.add_argument(
        "--native-json",
        type=str,
        default=str(BASE_DIR / "NEURON_IT2_reduced_data.json"),
        help="Path to NEURON native JSON (default: IT2/NEURON_IT2_reduced_data.json)",
    )
    parser.add_argument(
        "--netpyne-json",
        type=str,
        default=str(BASE_DIR / "IT2_reduced_all_data.json"),
        help="Path to NetPyNE JSON (default: IT2/IT2_reduced_all_data.json)",
    )
    parser.add_argument(
        "--out-dir",
        type=str,
        default=str(SCRIPT_DIR / "it2_native_vs_netpyne"),
        help="Output directory for comparison plots/statistics.",
    )
    parser.add_argument(
        "--title",
        type=str,
        default="Membrane voltage: IT2_reduced (NEURON native vs NetPyNE)",
        help="Title for the voltage comparison plot.",
    )
    parser.add_argument(
        "--out-png-name",
        type=str,
        default="voltage_overlay_diff_it2_native_vs_netpyne.png",
        help="Filename for the output PNG plot.",
    )

    args = parser.parse_args()

    compare(
        native_json=Path(args.native_json),
        netpyne_json=Path(args.netpyne_json),
        out_dir=Path(args.out_dir),
        title=args.title,
        out_png_name=args.out_png_name,
    )


if __name__ == "__main__":
    main()


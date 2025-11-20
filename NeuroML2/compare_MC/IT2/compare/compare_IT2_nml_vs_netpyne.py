#!/usr/bin/env python3
"""
Compare full-geometry IT2 simulations using:

- NEURON + NML-fix mechanisms (run_neuron_IT2_nml.py)
  -> NEURON_IT2_nml_data.json
- NetPyNE IT2_reduced cell with native mechanisms (IT2_netpy.py)
  -> IT2_reduced_all_data.json

Both use the same IT2 geometry, leak, ionic reversal potentials,
IClamp (0.3 nA from 200–500 ms), dt = 0.025 ms, tstop = 700 ms.
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


def _plot_overlay_and_diff(
    x_ms,
    y_nml,
    y_netpyne,
    title,
    ylabel,
    out_dir: Path,
    fname: str,
):
    out_dir.mkdir(parents=True, exist_ok=True)
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7), sharex=True)

    ax1.plot(x_ms, y_nml, "b-", lw=1.4, label="NEURON NML-fix")
    ax1.plot(x_ms, y_netpyne, "g--", lw=1.2, label="NetPyNE (native mechs)")
    ax1.set_title(title)
    ax1.set_ylabel(ylabel)
    ax1.grid(True, ls="--", alpha=0.6)
    ax1.legend()

    diff = y_nml - y_netpyne
    ax2.plot(x_ms, diff, color="#ff7f0e", lw=1.2)
    ax2.axhline(0.0, color="k", lw=0.8, ls=":")
    ax2.set_xlabel("Time (ms)")
    ax2.set_ylabel("Δ")
    ax2.grid(True, ls="--", alpha=0.6)

    fig.tight_layout()
    fig.savefig(out_dir / fname, dpi=300, bbox_inches="tight")
    plt.close(fig)


def compare(
    nml_json: Path,
    netpyne_json: Path,
    out_dir: Path,
    title: str,
    out_png_name: str,
):
    print("=" * 80)
    print("Comparing cell (NML-fix): NEURON vs NetPyNE")
    print("=" * 80)
    print(f"[paths] NML JSON   : {nml_json}")
    print(f"[paths] NetPyNE JSON: {netpyne_json}")

    with nml_json.open() as f:
        d_nml = json.load(f)["simData"]
    with netpyne_json.open() as f:
        d_np = json.load(f)["simData"]

    t_nml = np.array(d_nml["t"], dtype=float)
    t_np = np.array(d_np["t"], dtype=float)

    v_nml_raw = np.array(d_nml["V_soma"], dtype=float)
    v_np_raw = np.array(d_np["V_soma"]["cell_0"], dtype=float)

    n = min(len(t_nml), len(t_np), len(v_nml_raw), len(v_np_raw))
    t_ms = t_nml[:n]

    dt_diff = np.max(np.abs(t_nml[:n] - t_np[:n]))
    if dt_diff > 1e-6:
        print(
            f"[warn] Time vectors differ by up to {dt_diff:.3e} ms; "
            "using NML-fix time axis and aligning by index."
        )
    else:
        print(
            f"[info] Time vectors nearly identical (max |Δt| = {dt_diff:.3e} ms); "
            "aligning by index."
        )

    v_nml = v_nml_raw[:n]
    v_np = v_np_raw[:n]

    diff = v_nml - v_np
    print(f"[stats] V_nml    range: {v_nml.min():.5f} .. {v_nml.max():.5f} mV")
    print(f"[stats] V_netpyne range: {v_np.min():.5f} .. {v_np.max():.5f} mV")
    print(f"[stats] mean Δ(V_nml - V_netpyne): {diff.mean():.5f} mV")
    print(f"[stats] max |ΔV|: {np.max(np.abs(diff)):.5f} mV")

    _plot_overlay_and_diff(
        t_ms,
        v_nml,
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
            "Compare NEURON NML-fix vs NetPyNE simulations for IT2_reduced, "
            "based on JSON outputs."
        )
    )
    parser.add_argument(
        "--nml-json",
        type=str,
        default=str(BASE_DIR / "NEURON_IT2_nml_data.json"),
        help="Path to NEURON NML-fix JSON (default: IT2/NEURON_IT2_nml_data.json)",
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
        default=str(SCRIPT_DIR / "it2_nml_vs_netpyne"),
        help="Output directory for comparison plots/statistics.",
    )
    parser.add_argument(
        "--title",
        type=str,
        default="Membrane voltage: IT2_reduced (NML-fix vs NetPyNE)",
        help="Title for the voltage comparison plot.",
    )
    parser.add_argument(
        "--out-png-name",
        type=str,
        default="voltage_overlay_diff_it2_nml_vs_netpyne.png",
        help="Filename for the output PNG plot.",
    )

    args = parser.parse_args()

    compare(
        nml_json=Path(args.nml_json),
        netpyne_json=Path(args.netpyne_json),
        out_dir=Path(args.out_dir),
        title=args.title,
        out_png_name=args.out_png_name,
    )


if __name__ == "__main__":
    main()


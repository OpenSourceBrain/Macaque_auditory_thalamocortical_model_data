#!/usr/bin/env python3
"""
Compare pure NEURON (Python) vs NeuroML (NEURON backend) for hh2-only cell.
Both sides use dt=0.025 ms. Align traces by step index to avoid floating-time
drift. Currently we only compare the membrane voltage traces.
"""
import os
import json
import numpy as np
import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt

OUT_DIR = os.path.join('compare_out', 'hh2_neuron_vs_nml')
os.makedirs(OUT_DIR, exist_ok=True)

DT = 2.5e-5  # seconds (0.025 ms)


def axis_by_len(n, dt=DT):
    return dt * np.arange(n, dtype=np.int64)


def window_idx(n, dt=DT, tmin=0.001, tmax=0.999):
    i0 = int(np.ceil(tmin / dt))
    i1 = min(n, int(np.floor(tmax / dt)) + 1)
    return slice(i0, i1)


def _load_xy(path):
    arr = np.loadtxt(path)
    if arr.ndim == 1:
        y = arr
        x = np.arange(len(y)) * DT
    else:
        x, y = arr[:, 0], arr[:, 1]
    return x, y


def _plot_overlay_and_diff(x, y_nml, y_nrn, title, ylabel, fname):
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 7), sharex=True)
    ax1.plot(x, y_nml, 'b-', lw=1.6, label='NeuroML')
    ax1.plot(x, y_nrn, 'm--', lw=1.2, label='NEURON')
    ax1.set_title(title)
    ax1.set_ylabel(ylabel)
    ax1.grid(True, ls='--', alpha=0.6)
    ax1.legend()
    diff = y_nml - y_nrn
    ax2.plot(x, diff, color='#2ca02c', lw=1.2)
    ax2.axhline(0.0, color='k', lw=0.8, ls=':')
    ax2.set_xlabel('Time (s)')
    ax2.set_ylabel('Δ')
    ax2.grid(True, ls='--', alpha=0.6)
    fig.tight_layout()
    fig.savefig(os.path.join(OUT_DIR, fname), dpi=300, bbox_inches='tight')
    plt.close(fig)


def compare():
    print("=" * 80)
    print("Comparing NEURON vs NeuroML - HH2 only (step-aligned)")
    print("=" * 80)

    # 1) Load NEURON: prefer SI .dat if present, else JSON
    nrn_dat = 'NEURON_hh2.RE_hh2_pop.v.dat'
    if os.path.exists(nrn_dat):
        t_nrn, v_nrn_v = _load_xy(nrn_dat)  # volts
        v_nrn = v_nrn_v * 1000.0  # to mV
    else:
        with open('NEURON_hh2_data.json', 'r') as f:
            nrn = json.load(f)['simData']
        v_nrn = np.array(nrn['V_soma'])

    # 2) Load NeuroML outputs
    t_v, v_v = _load_xy('RE_hh2_step_test.RE_hh2_pop.v.dat')
    v_nml = v_v * 1000.0  # V -> mV
    # 3) Step alignment
    n = min(len(v_nml), len(v_nrn))
    idx = window_idx(n)
    if os.path.exists(nrn_dat):
        t_al = t_v[:n][idx]
    else:
        t_al = axis_by_len(n)[idx]

    _plot_overlay_and_diff(
        t_al,
        v_nml[:n][idx],
        v_nrn[:n][idx],
        'Membrane voltage',
        'mV',
        'voltage_overlay_diff_hh2_nrn.png',
    )

    print("\nNEURON vs NeuroML hh2 comparison complete. See:", OUT_DIR)


if __name__ == '__main__':
    compare()

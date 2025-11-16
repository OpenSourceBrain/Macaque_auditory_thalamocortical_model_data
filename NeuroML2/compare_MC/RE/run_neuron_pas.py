#!/usr/bin/env python3
"""
Pure NEURON (Python) simulation for a passive (pas-only) RE soma.

Geometry, temperature, stimulus, and passive parameters match the hh2
setups, but no active Na/K channels are inserted. Outputs are used for
direct comparison with the NeuroML leaky (pas-only) run.
"""
from __future__ import annotations

import json
import os

# Headless NEURON env
os.environ.setdefault("MPLBACKEND", "Agg")
os.environ["NEURON_NO_GUI"] = "1"
os.environ.pop("DISPLAY", None)

import neuron  # type: ignore
from neuron import h  # type: ignore


def _round_list(vals, digits: int = 6):
    return [round(float(x), digits) for x in vals]


def _round_voltage_mV(vals):
    out = []
    for x in vals:
        volt = float(x) / 1000.0
        volt_sig = float(format(volt, ".6e"))
        out.append(round(volt_sig * 1000.0, 6))
    return out


def run():
    h.load_file("stdrun.hoc")
    h.celsius = 36.0

    # Single-compartment soma; geometry via pt3d to match RE_hh2_cell.hoc
    soma = h.Section(name="Seg0_soma")
    h.pt3dclear(sec=soma)
    h.pt3dadd(0.0, 64.86, 0.0, 70.0, sec=soma)
    h.pt3dadd(0.0, 0.0, 0.0, 70.0, sec=soma)
    soma.Ra = 100.0
    soma.cm = 1.0

    # Passive leak only
    soma.insert("pas")
    soma.g_pas = 5e-5
    soma.e_pas = -77.0

    # Stimulus: 200–700 ms, 300 pA (0.2 nA)
    stim = h.IClamp(soma(0.5))
    stim.delay = 200.0
    stim.dur = 500.0
    stim.amp = 0.4

    # Simulation controls
    h.dt = 0.025
    h.tstop = 1000.0
    h.v_init = -70.0

    # Record time and somatic voltage only
    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(soma(0.5)._ref_v)

    h.finitialize(h.v_init)
    h.run()

    sim = {
        "dt": float(h.dt),
        "t": list(t_vec),
        "V_soma": list(v_vec),
        "mech": "pas",
    }
    sim["dt"] = round(sim["dt"], 6)
    sim["t"] = _round_list(sim["t"])
    sim["V_soma"] = _round_voltage_mV(sim["V_soma"])

    with open("NEURON_pas_data.json", "w") as f:
        json.dump({"simData": sim}, f, indent=2, sort_keys=True)
        f.write("\n")
    print("[NEURON] passive (pas-only) simulation complete -> NEURON_pas_data.json")

    # Also save SI-unit traces (time in s, voltage in V) for comparison
    t_sec = [float(t) / 1000.0 for t in sim["t"]]
    with open("time_pas.dat", "w") as f:
        for t in t_sec:
            f.write("%.6f\n" % t)

    v_v = [float(v) / 1000.0 for v in sim["V_soma"]]
    with open("NEURON_pas.RE_leaky_pop.v.dat", "w") as f:
        for t, v in zip(t_sec, v_v):
            f.write("%e\t%e\t\n" % (t, v))
    print(
        "[NEURON] Wrote SI-unit traces: "
        "time_pas.dat, NEURON_pas.RE_leaky_pop.v.dat"
    )


if __name__ == "__main__":
    run()


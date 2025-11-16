#!/usr/bin/env python3
"""
Pure NEURON (Python) simulation for hh2-only cell using the split
NeuroML-exported cnexp mechanisms `hh2_na_cnexp.mod` + `hh2_k_cnexp`
(`SUFFIX hh2_na` / `hh2_k`) plus passive leak.

Geometry, parameters, temperature, and stimulus match `RE_hh2_cell.nml`,
so results can be compared directly to the NeuroML hh2 run
(`run_nml_hh2.py`).
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


def _try_load_mechs():
    """Load compiled NMODL mechanisms from current directory."""
    try:
        neuron.load_mechanisms(os.getcwd())
        print("[run_neuron_hh2_cnexp] Loaded mechanisms from current dir")
        return
    except Exception as exc:  # pragma: no cover
        print(f"[run_neuron_hh2_cnexp] load_mechanisms warn: {exc}")
    dll = os.path.join("x86_64", ".libs", "libnrnmech.so")
    if os.path.exists(dll):
        try:
            h.nrn_load_dll(dll)
            print(
                "[run_neuron_hh2_cnexp] Loaded mechanisms via nrn_load_dll:",
                dll,
            )
            return
        except Exception as exc:  # pragma: no cover
            print(f"[run_neuron_hh2_cnexp] nrn_load_dll fallback failed: {exc}")
    print(
        "[run_neuron_hh2_cnexp] Warning: no mechanisms loaded. "
        "If hh2_na_cnexp/hh2_k_cnexp not found, run: nrnivmodl mod"
    )


def run():
    _try_load_mechs()

    h.load_file("stdrun.hoc")
    h.celsius = 36.0

    # Single-compartment soma; geometry via pt3d to match RE_hh2_cell.hoc
    soma = h.Section(name="Seg0_soma_cnexp")
    h.pt3dclear(sec=soma)
    h.pt3dadd(0.0, 64.86, 0.0, 70.0, sec=soma)
    h.pt3dadd(0.0, 0.0, 0.0, 70.0, sec=soma)
    soma.Ra = 100.0
    soma.cm = 1.0

    # Passive leak
    soma.insert("pas")
    soma.g_pas = 5e-5
    soma.e_pas = -77.0

    # Split cnexp Na/K mechanisms (from hh2_na_cnexp.mod / hh2_k_cnexp.mod)
    soma.insert("hh2_na")
    soma.insert("hh2_k")

    for seg in soma:
        seg.hh2_na.gmax = 0.09
        seg.hh2_k.gmax = 0.01
        try:
            seg.ena = 50.0
            seg.ek = -95.0
        except Exception:
            pass

    # Stimulus: 200–700 ms, 300 pA (0.2 nA)
    stim = h.IClamp(soma(0.5))
    stim.delay = 200.0
    stim.dur = 500.0
    stim.amp = 0.2

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
        "mech": "hh2_na_cnexp+hh2_k_cnexp",
    }
    sim["dt"] = round(sim["dt"], 6)
    sim["t"] = _round_list(sim["t"])
    sim["V_soma"] = _round_voltage_mV(sim["V_soma"])

    out_json = "NEURON_hh2_cnexp_data.json"
    with open(out_json, "w") as f:
        json.dump({"simData": sim}, f, indent=2, sort_keys=True)
        f.write("\n")
    print("[NEURON] hh2 cnexp split simulation ->", out_json)

    # SI-unit traces: time in s, V in V
    t_sec = [float(t) / 1000.0 for t in sim["t"]]
    with open("time_hh2_cnexp.dat", "w") as f:
        for t in t_sec:
            f.write("%.6f\n" % t)

    v_v = [float(v) / 1000.0 for v in sim["V_soma"]]
    dat_path = "NEURON_hh2_cnexp.RE_hh2_pop.v.dat"
    with open(dat_path, "w") as f:
        for t, v in zip(t_sec, v_v):
            f.write("%e\t%e\t\n" % (t, v))
    print(
        "[NEURON] Wrote SI-unit traces for cnexp: "
        "time_hh2_cnexp.dat, NEURON_hh2_cnexp.RE_hh2_pop.v.dat"
    )


if __name__ == "__main__":
    run()


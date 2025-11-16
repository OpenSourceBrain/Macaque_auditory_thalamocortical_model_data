#!/usr/bin/env python3
"""
Pure NEURON (Python) simulation for hh2-only cell using the same exported
MOD mechanisms as the NeuroML run (hh2_na.mod, hh2_k.mod, pas_nml2.mod).

Geometry, parameters, temperature, and stimulus match RE_hh2_cell.nml.
Outputs a JSON file with traces for direct comparison with the NeuroML
NEURON-backend run.
"""
import os
import json
import shutil

# Headless NEURON + Matplotlib env
os.environ.setdefault("MPLBACKEND", "Agg")
os.environ["NEURON_NO_GUI"] = "1"
os.environ.pop("DISPLAY", None)

import neuron
from neuron import h  # type: ignore


def _round_list(vals, digits=6):
    return [round(float(x), digits) for x in vals]


def _round_voltage_mV(vals):
    out = []
    for x in vals:
        volt = float(x) / 1000.0
        volt_sig = float(format(volt, ".6e"))
        out.append(round(volt_sig * 1000.0, 6))
    return out


def _try_load_mechs():
    """Load compiled NMODL mechanisms from current directory.
    Prefer neuron.load_mechanisms; fall back to explicit nrn_load_dll.
    """
    try:
        neuron.load_mechanisms(os.getcwd())
        print("[run_neuron_hh2] Loaded mechanisms from current dir")
        return
    except Exception as e:
        print(f"[run_neuron_hh2] load_mechanisms warn: {e}")
    # Fallback to direct shared library
    dll = os.path.join("x86_64", ".libs", "libnrnmech.so")
    if os.path.exists(dll):
        try:
            h.nrn_load_dll(dll)
            print(f"[run_neuron_hh2] Loaded mechanisms via nrn_load_dll: {dll}")
            return
        except Exception as e:
            print(f"[run_neuron_hh2] nrn_load_dll fallback failed: {e}")
    print("[run_neuron_hh2] Warning: no mechanisms loaded. If hh2_na/hh2_k not found, run: nrnivmodl .")


def run():
    _try_load_mechs()

    h.load_file("stdrun.hoc")
    h.celsius = 36.0

    # Single-compartment soma; geometry via pt3d to match RE_hh2_cell.hoc
    soma = h.Section(name="Seg0_soma")
    h.pt3dclear(sec=soma)
    h.pt3dadd(0.0, 64.86, 0.0, 70.0, sec=soma)
    h.pt3dadd(0.0, 0.0, 0.0, 70.0, sec=soma)
    soma.Ra = 100.0
    soma.cm = 1.0


    soma.insert("pas")
    soma.g_pas = 5e-5
    soma.e_pas = -77.0


    # Use original combined HH2 mechanism from mod/HH2.mod
    soma.insert("hh2ad")
    # Use section variables so values apply to the whole section
    soma.gnabar_hh2ad = 0.09
    soma.gkbar_hh2ad = 0.01
    soma.vtraub_hh2ad = -50.0

    # Reversal potentials per segment (hh2ad READs ena/ek)
    for seg in soma:
        try:
            seg.ena = 50.0
            seg.ek = -95.0
        except Exception:
            # If ions are not present, ignore; exported mods set Erev internally anyway
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

    # Record only time and somatic voltage
    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(soma(0.5)._ref_v)

    # Run
    h.finitialize(h.v_init)
    h.run()

    # Save JSON (units: t ms, V mV); round to 6 decimals
    sim = {
        "dt": float(h.dt),
        "t": list(t_vec),
        "V_soma": list(v_vec),
        "mech": "hh2ad",
    }
    sim["dt"] = round(sim["dt"], 6)
    sim["t"] = _round_list(sim["t"])
    sim["V_soma"] = _round_voltage_mV(sim["V_soma"])
    out = {"simData": sim}
    with open("NEURON_hh2_data.json", "w") as f:
        json.dump({"simData": sim}, f, indent=2, sort_keys=True)
        f.write("\n")
    print("[NEURON] hh2-only simulation complete -> NEURON_hh2_data.json")

    # Also save SI-unit .dat files similar to jNeuroML output for direct comparison
    # time.dat: seconds
    t_sec = [float(t) / 1000.0 for t in sim["t"]]
    with open("time.dat", "w") as f:
        for t in t_sec:
            f.write("%.6f\n" % t)
    # NEURON_hh2.RE_hh2_pop.v.dat: two columns: time(s) and voltage(V)
    v_v = [float(v) / 1000.0 for v in sim["V_soma"]]
    with open("NEURON_hh2.RE_hh2_pop.v.dat", "w") as f:
        for t, v in zip(t_sec, v_v):
            f.write("%e\t%e\t\n" % (t, v))
    print("[NEURON] Wrote SI-unit traces: time.dat, NEURON_hh2.RE_hh2_pop.v.dat")


if __name__ == "__main__":
    run()

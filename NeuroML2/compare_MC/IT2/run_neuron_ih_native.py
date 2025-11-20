#!/usr/bin/env python3
"""
Pure NEURON (Python) single-channel test for the native Ih current
(h_kole.mod: SUFFIX ih) used in the IT2 cell.

Geometry and stimulation use the full IT2_reduced morphology:

- Multi-compartment soma + Adend1–3 + Bdend + axon.
- Only native `ih` + passive leak (`pas`) mechanisms inserted.
- IClamp: 0.3 nA from 200–500 ms, dt = 0.025 ms, tstop = 700 ms.

Outputs (in IT2/compare):
- NEURON_ih_native.json: time (ms) and V_soma (mV)
- NEURON_ih_native.v.dat: time (s), voltage (V)
"""

import json
import os

# Headless NEURON env
os.environ.setdefault("MPLBACKEND", "Agg")
os.environ["NEURON_NO_GUI"] = "1"
os.environ.pop("DISPLAY", None)

import neuron  # type: ignore
from neuron import h  # type: ignore


def _round_list(vals, digits: int = 9):
    return [round(float(x), digits) for x in vals]


def _round_voltage_mV(vals):
    out = []
    for x in vals:
        volt = float(x) / 1000.0
        volt_sig = float(format(volt, ".9e"))
        out.append(round(volt_sig * 1000.0, 9))
    return out


def _try_load_mechs():
    # Mechanisms are compiled with `nrnivmodl mod` from this directory.
    # Importing `neuron` when run from IT2/ should auto-load x86_64,
    # so we do not explicitly call load_mechanisms here.
    return


def _build_it2_with_ih_native():
    """Full IT2 morphology with native ih + pas."""

    soma = h.Section(name="soma")
    h.pt3dclear(sec=soma)
    h.pt3dadd(0.0, 0.0, 0.0, 28.2149102762, sec=soma)
    h.pt3dadd(0.0, 48.4123467666, 0.0, 28.2149102762, sec=soma)
    soma.Ra = 70.0015514222
    soma.cm = 2.4998269977

    Adend1 = h.Section(name="Adend1")
    h.pt3dclear(sec=Adend1)
    h.pt3dadd(0.0, 48.4123467666, 0.0, 1.5831889597, sec=Adend1)
    h.pt3dadd(0.0, 58.941564511066665, 0.0, 1.5831889597, sec=Adend1)
    Adend1.Ra = 70.0015514222
    Adend1.cm = 2.74242941886

    Adend2 = h.Section(name="Adend2")
    h.pt3dclear(sec=Adend2)
    h.pt3dadd(0.0, 58.941564511066665, 0.0, 1.5831889597, sec=Adend2)
    h.pt3dadd(0.0, 69.47078225553334, 0.0, 1.5831889597, sec=Adend2)
    Adend2.Ra = 70.0015514222
    Adend2.cm = 2.74242941886

    Adend3 = h.Section(name="Adend3")
    h.pt3dclear(sec=Adend3)
    h.pt3dadd(0.0, 69.47078225553334, 0.0, 1.5831889597, sec=Adend3)
    h.pt3dadd(0.0, 80.0, 0.0, 1.5831889597, sec=Adend3)
    Adend3.Ra = 70.0015514222
    Adend3.cm = 2.74242941886

    Bdend = h.Section(name="Bdend")
    h.pt3dclear(sec=Bdend)
    h.pt3dadd(0.0, 48.4123467666, 0.0, 2.2799248874, sec=Bdend)
    h.pt3dadd(68.40225, -116.8145967666, 0.0, 2.2799248874, sec=Bdend)
    Bdend.Ra = 70.0015514222
    Bdend.cm = 2.74086279376

    axon = h.Section(name="axon")
    h.pt3dclear(sec=axon)
    h.pt3dadd(0.0, 0.0, 0.0, 1.40966286462, sec=axon)
    h.pt3dadd(0.0, -594.292937602, 0.0, 1.40966286462, sec=axon)
    axon.Ra = 70.0015514222
    axon.cm = 2.4630760526

    # Topology
    Adend1.connect(soma(1.0), 0.0)
    Adend2.connect(Adend1(1.0), 0.0)
    Adend3.connect(Adend2(1.0), 0.0)
    Bdend.connect(soma(0.5), 0.0)
    axon.connect(soma(0.0), 0.0)

    # Passive leak (pas) as in IT2_netpy
    soma.insert("pas")
    soma.g_pas = 0.0001
    soma.e_pas = -86.0

    for sec in [Adend1, Adend2, Adend3]:
        sec.insert("pas")
        sec.g_pas = 7.199592136286027e-05
        sec.e_pas = -87.1335623948

    Bdend.insert("pas")
    Bdend.g_pas = 0.00014147647761414165
    Bdend.e_pas = -87.1335623948

    axon.insert("pas")
    axon.g_pas = 0.00035435694659685776
    axon.e_pas = -87.1335623948

    # Native ih (h_kole.mod) on soma + dendrites (no axon ih)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("ih")
        for seg in sec:
            seg.ih.gbar = 3.3176340367e-05
            seg.ih.ascale = 0.00320887293027
            seg.ih.ashift = 119.696272155
            seg.ih.aslope = 7.09800576233
            seg.ih.bscale = 0.285307415701
            seg.ih.bslope = 23.2995848558

    return soma


def run():
    _try_load_mechs()

    h.load_file("stdrun.hoc")
    h.celsius = 34.0

    soma = _build_it2_with_ih_native()

    # Stimulus: 0.3 nA from 200–500 ms (same as other single-channel tests)
    stim = h.IClamp(soma(0.5))
    stim.delay = 200.0
    stim.dur = 300.0
    stim.amp = 0.8

    # Simulation controls
    h.steps_per_ms = 40.0
    h.dt = 0.025
    h.tstop = 700.0
    h.v_init = -85.7

    t_vec = h.Vector().record(h._ref_t)
    v_vec = h.Vector().record(soma(0.5)._ref_v)

    h.finitialize(h.v_init)
    h.run()

    sim = {
        "dt": float(h.dt),
        "t": list(t_vec),
        "V_soma": list(v_vec),
        "mech": "ih_native",
    }
    sim["dt"] = round(sim["dt"], 9)
    sim["t"] = _round_list(sim["t"])
    sim["V_soma"] = _round_voltage_mV(sim["V_soma"])

    out_dir = "compare"
    os.makedirs(out_dir, exist_ok=True)

    out_json = os.path.join(out_dir, "NEURON_ih_native.json")
    with open(out_json, "w") as f:
        json.dump({"simData": sim}, f, indent=2, sort_keys=True)
        f.write("\n")
    print(f"[NEURON] ih native single-channel simulation -> {out_json}")

    # SI-unit trace
    t_sec = [float(t) / 1000.0 for t in sim["t"]]
    v_v = [float(v) / 1000.0 for v in sim["V_soma"]]
    out_dat = os.path.join(out_dir, "NEURON_ih_native.v.dat")
    with open(out_dat, "w") as f:
        for t, v in zip(t_sec, v_v):
            f.write("%e\t%e\t\n" % (t, v))
    print(f"[NEURON] Wrote SI-unit trace: {out_dat}")


if __name__ == "__main__":
    run()

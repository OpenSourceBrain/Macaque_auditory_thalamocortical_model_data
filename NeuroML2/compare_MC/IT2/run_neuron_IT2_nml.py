#!/usr/bin/env python3
"""
Pure NEURON (Python) simulation for the full IT2_reduced cell using
NeuroML-exported mechanisms (NML-fix version), analogous to RE
`run_neuron_full_nml_fix.py`.

Channels used (SUFFIX in parentheses):

- Leak: pas (native NEURON mechanism)
- Ih: ih_nml.mod          (ih_nml)
- L/N/T Ca: cal_nml.mod   (cal_nml)
              can_nml.mod (can_nml)
              cat_nml.mod (cat_nml)
- BK: kBK_nml.mod         (kBK_nml)
- A-type K: kap_nml.mod   (kap_nml)
- Delayed rectifier K:
    soma:   kdr_soma_nml.mod (kdr_soma_nml)
    dend/axon: kdr_nml.mod   (kdr_nml)
- Na: nax_nml.mod          (nax_nml)
- Ca dynamics:
    soma:   cadad_IT2_soma_nml.mod      (cadad_IT2_soma_nml)
    dend:   cadad_IT2_dend_all_nml.mod  (cadad_IT2_dend_all_nml)

Geometry, passive leak, ionic reversal potentials, and stimulus match
`run_neuron_IT2_native.py` / `IT2_netpy.py`:

- Multi-compartment soma + Adend1–3 + Bdend + axon.
- IClamp: 0.3 nA from 200–500 ms.
- dt = 0.025 ms, tstop = 700 ms.

Outputs:
- NEURON_IT2_nml_data.json: time (ms) and V_soma (mV)
"""

import json
import os

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
    return


def _build_it2_nml_cell():
    """Construct multi-compartment IT2_reduced cell with NML-exported mechanisms."""

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

    # Topology (same as native / NetPyNE)
    Adend1.connect(soma(1.0), 0.0)
    Adend2.connect(Adend1(1.0), 0.0)
    Adend3.connect(Adend2(1.0), 0.0)
    Bdend.connect(soma(0.5), 0.0)
    axon.connect(soma(0.0), 0.0)

    secs = [soma, Adend1, Adend2, Adend3, Bdend, axon]

    # Passive leak: use native pas with same parameters as native/NetPyNE
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("pas")

    soma.g_pas = 0.0001
    soma.e_pas = -86.0
    for sec in [Adend1, Adend2, Adend3]:
        sec.g_pas = 7.199592136286027e-05
        sec.e_pas = -87.1335623948
    Bdend.g_pas = 0.00014147647761414165
    Bdend.e_pas = -87.1335623948
    axon.insert("pas")
    axon.g_pas = 0.00035435694659685776
    axon.e_pas = -87.1335623948

    # NML Ih (ih_nml.mod)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("ih_nml")
        for seg in sec:
            # Match total conductance density via gmax
            seg.ih_nml.gmax = 3.3176340367e-05

    # NML Ca dynamics
    # soma: cadad_IT2_soma_nml; dendrites: cadad_IT2_dend_all_nml
    soma.insert("cadad_IT2_soma_nml")
    for seg in soma:
        seg.cadad_IT2_soma_nml.cainf = 0.00024
        seg.cadad_IT2_soma_nml.depth = 1.1940861e-05
        seg.cadad_IT2_soma_nml.taur = 99.114685

    for sec in [Adend1, Adend2, Adend3, Bdend]:
        sec.insert("cadad_IT2_dend_all_nml")
        for seg in sec:
            seg.cadad_IT2_dend_all_nml.cainf = 0.00024
            seg.cadad_IT2_dend_all_nml.depth = 1.1940861e-05
            seg.cadad_IT2_dend_all_nml.taur = 99.114685

    # NML Ca channels: cal_nml, can_nml, cat_nml
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("cal_nml")
        sec.insert("can_nml")
        sec.insert("cat_nml")
        for seg in sec:
            seg.cal_nml.gmax = 2.39132864454e-06
            seg.can_nml.gmax = 8.13137955053e-07
            seg.cat_nml.gmax = 9.29455717585e-07

    # NML kBK
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("kBK_nml")
        for seg in sec:
            seg.kBK_nml.gmax = 4.45651933019e-05

    # NML A-type K (kap_nml)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("kap_nml")
        for seg in sec:
            seg.kap_nml.gmax = 0.0240195239098

    axon.insert("kap_nml")
    for seg in axon:
        seg.kap_nml.gmax = 0.120097619549

    # NML delayed rectifier K: soma uses kdr_soma_nml, dend/axon use kdr_nml
    soma.insert("kdr_soma_nml")
    for seg in soma:
        seg.kdr_soma_nml.gmax = 0.017

    for sec in [Adend1, Adend2, Adend3, Bdend]:
        sec.insert("kdr_nml")
        for seg in sec:
            seg.kdr_nml.gmax = 0.00833766634808

    axon.insert("kdr_nml")
    for seg in axon:
        seg.kdr_nml.gmax = 0.0416883317404

    # NML Na (nax_nml)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend, axon]:
        sec.insert("nax_nml")
    for seg in soma:
        seg.nax_nml.gmax = 0.043
    for sec in [Adend1, Adend2, Adend3, Bdend]:
        for seg in sec:
            seg.nax_nml.gmax = 0.0768253702194
    for seg in axon:
        seg.nax_nml.gmax = 0.384126851097

    # Ion reversal potentials; Ca concentrations are handled by cadad_IT2_*_nml
    for sec in [soma, Adend1, Adend2, Adend3, Bdend, axon]:
        for seg in sec:
            try:
                seg.ek = -104.0
                seg.ena = 42.0
            except AttributeError:
                pass

    return soma, secs


def run():
    _try_load_mechs()

    h.load_file("stdrun.hoc")
    h.celsius = 34.0

    soma, secs = _build_it2_nml_cell()

    # Stimulus: 0.3 nA from 200–500 ms (match native / NetPyNE)
    stim = h.IClamp(soma(0.5))
    stim.delay = 200.0
    stim.dur = 300.0
    stim.amp = 0.3

    # Fixed-step integration with dt = 0.025 ms, tstop = 700 ms
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
        "mech": "IT2_reduced_nml",
    }
    sim["dt"] = round(sim["dt"], 9)
    sim["t"] = _round_list(sim["t"])
    sim["V_soma"] = _round_voltage_mV(sim["V_soma"])

    out_json = "NEURON_IT2_nml_data.json"
    with open(out_json, "w") as f:
        json.dump({"simData": sim}, f, indent=2, sort_keys=True)
        f.write("\n")
    print("[NEURON] IT2 reduced-cell NML-fix simulation complete ->", out_json)


if __name__ == "__main__":
    run()

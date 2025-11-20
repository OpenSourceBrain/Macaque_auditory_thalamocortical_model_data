#!/usr/bin/env python3
"""
Pure NEURON (Python) simulation for the full IT2_reduced cell using the
same native mechanisms as the NeuroML / NetPyNE versions:

- pas leak (built-in NEURON mechanism)
- h (Ih, h_kole.mod: SUFFIX ih)
- low/high-threshold Ca (cal_mig.mod: cal, can_mig.mod: can, cat_mig.mod: cat)
- BK Ca-activated K (kBK.mod: kBK)
- A-type K (kap_BS.mod: kap)
- delayed rectifier K (kdr_BS.mod: kdr)
- Na (nax_BS.mod: nax)
- Ca dynamics (cadad.mod: cadad)

Geometry, parameters, temperature, and stimulus mirror IT2_netpy.py and
IT2_reduced_cell.nml as closely as possible. For consistency with the
single-channel tests, we use:

- IClamp: 0.3 nA from 200–500 ms
- dt = 0.025 ms, tstop = 700 ms

Outputs:
- NEURON_IT2_reduced_data.json: time (ms) and V_soma (mV)
- NEURON_IT2_reduced.IT2_pop.v.dat: time (s), voltage (V) for possible
  comparison with NeuroML NEURON-backend runs.
"""

import json
import os

# Headless NEURON env (align with RE scripts)
os.environ.setdefault("MPLBACKEND", "Agg")
os.environ["NEURON_NO_GUI"] = "1"
os.environ.pop("DISPLAY", None)

import neuron  # type: ignore
from neuron import h  # type: ignore


def _round_list(vals, digits: int = 9):
    return [round(float(x), digits) for x in vals]


def _round_voltage_mV(vals):
    """Round voltage in mV in a numerically stable way."""
    out = []
    for x in vals:
        volt = float(x) / 1000.0
        volt_sig = float(format(volt, ".9e"))
        out.append(round(volt_sig * 1000.0, 9))
    return out


def _try_load_mechs():
    # As in RE scripts: mechanisms are usually compiled with `nrnivmodl mod`
    # and loaded automatically by NEURON when importing `neuron` from this
    # directory. We avoid explicit load_mechanisms here to prevent duplicate
    # loading warnings.
    return


def _build_it2_cell():
    """Construct multi-compartment IT2_reduced cell with native mechanisms."""

    # Geometry and passive properties copied from IT2_netpy.py
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

    # Topology (match IT2_netpy and IT2_reduced_cell.nml)
    Adend1.connect(soma(1.0), 0.0)
    Adend2.connect(Adend1(1.0), 0.0)
    Adend3.connect(Adend2(1.0), 0.0)
    Bdend.connect(soma(0.5), 0.0)
    axon.connect(soma(0.0), 0.0)

    secs = [soma, Adend1, Adend2, Adend3, Bdend, axon]

    # Insert mechanisms and set parameters (following IT2_netpy.py)

    # Common passive leak (pas); ionic reversal potentials are set below after
    # all mechanisms that USEION have been inserted.
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("pas")

    # Passive leak
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

    # Ih (h_kole.mod: SUFFIX ih)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("ih")
        for seg in sec:
            seg.ih.gbar = 3.3176340367e-05
            seg.ih.ascale = 0.00320887293027
            seg.ih.ashift = 119.696272155
            seg.ih.aslope = 7.09800576233
            seg.ih.bscale = 0.285307415701
            seg.ih.bslope = 23.2995848558

    # Ca dynamics (cadad.mod)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("cadad")
        for seg in sec:
            seg.cadad.cainf = 0.00024
            seg.cadad.depth = 0.119408607923
            seg.cadad.kt = 0.0
            seg.cadad.kd = 0.0
            seg.cadad.taur = 99.1146852282

    # Ca channels (cal, can, cat)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("cal")
        sec.insert("can")
        sec.insert("cat")
        for seg in sec:
            seg.cal.gcalbar = 2.39132864454e-06
            seg.can.gcanbar = 8.13137955053e-07
            seg.cat.gcatbar = 9.29455717585e-07

    # kBK (BK Ca-activated K)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        sec.insert("kBK")
        for seg in sec:
            seg.kBK.gpeak = 4.45651933019e-05
            seg.kBK.caPh = 0.002
            seg.kBK.caPk = 1.0
            seg.kBK.caPmax = 1.0
            seg.kBK.caPmin = 0.0
            seg.kBK.caVhh = 0.002
            seg.kBK.caVhmax = 155.67
            seg.kBK.caVhmin = 43.919142291200004
            seg.kBK.k = 17.0
            seg.kBK.tau = 1.0

    # A-type K (kap)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend, axon]:
        sec.insert("kap")
    for sec in [soma, Adend1, Adend2, Adend3, Bdend]:
        for seg in sec:
            seg.kap.gbar = 0.0240195239098
            seg.kap.sh = 0.0
            seg.kap.tq = -49.7149526489
            seg.kap.vhalfl = -36.7754836348
            seg.kap.vhalfn = 32.179925527
    for seg in axon:
        seg.kap.gbar = 0.120097619549
        seg.kap.sh = 0.0
        seg.kap.tq = -49.7149526489
        seg.kap.vhalfl = -36.7754836348
        seg.kap.vhalfn = 32.179925527

    # Delayed rectifier K (kdr)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend, axon]:
        sec.insert("kdr")
    for seg in soma:
        seg.kdr.gbar = 0.017
        seg.kdr.sh = 0.0
        seg.kdr.vhalfn = 8.0
    for sec in [Adend1, Adend2, Adend3, Bdend, axon]:
        for seg in sec:
            seg.kdr.gbar = 0.00833766634808 if sec is not axon else 0.0416883317404
            seg.kdr.sh = 0.0
            seg.kdr.vhalfn = 11.6427471384

    # Na (nax)
    for sec in [soma, Adend1, Adend2, Adend3, Bdend, axon]:
        sec.insert("nax")
    for seg in soma:
        seg.nax.gbar = 0.043
        seg.nax.sh = 0.0
    for sec in [Adend1, Adend2, Adend3, Bdend]:
        for seg in sec:
            seg.nax.gbar = 0.0768253702194
            seg.nax.sh = 0.0
    for seg in axon:
        seg.nax.gbar = 0.384126851097
        seg.nax.sh = 0.0

    # Set ionic reversal potentials; Ca concentrations will be handled by
    # cadad and channel defaults.
    for sec in [soma, Adend1, Adend2, Adend3, Bdend, axon]:
        for seg in sec:
            try:
                seg.ek = -104.0
                seg.ena = 42.0
            except AttributeError:
                # If the ion mechanism does not exist on this segment yet,
                # skip setting it (should not happen once channels are inserted).
                pass

    return soma, secs


def run():
    _try_load_mechs()

    h.load_file("stdrun.hoc")
    h.celsius = 34.0

    soma, secs = _build_it2_cell()

    # Stimulus: 0.3 nA from 200–500 ms (to match single-channel tests)
    stim = h.IClamp(soma(0.5))
    stim.delay = 200.0
    stim.dur = 300.0
    stim.amp = 0.3

    # Simulation controls (fixed step, dt = 0.025 ms), tstop = 700 ms
    # NEURON internally enforces dt = 1/steps_per_ms at finitialize(),
    # so set steps_per_ms consistently to avoid "Changed dt" and keep
    # this run aligned with IT2_netpy.py (which now uses dt = 0.025).
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
        "mech": "IT2_reduced_native",
    }
    sim["dt"] = round(sim["dt"], 9)
    sim["t"] = _round_list(sim["t"])
    sim["V_soma"] = _round_voltage_mV(sim["V_soma"])

    out_json = "NEURON_IT2_reduced_data.json"
    with open(out_json, "w") as f:
        json.dump({"simData": sim}, f, indent=2, sort_keys=True)
        f.write("\n")
    print(f"[NEURON] IT2 reduced-cell simulation complete -> {out_json}")

    # Also save SI-unit .dat trace (time in s, voltage in V)
    t_sec = [float(t) / 1000.0 for t in sim["t"]]
    v_v = [float(v) / 1000.0 for v in sim["V_soma"]]
    out_dat = "NEURON_IT2_reduced.IT2_pop.v.dat"
    with open(out_dat, "w") as f:
        for t, v in zip(t_sec, v_v):
            f.write("%e\t%e\t\n" % (t, v))
    print(f"[NEURON] Wrote SI-unit trace: {out_dat}")


if __name__ == "__main__":
    run()

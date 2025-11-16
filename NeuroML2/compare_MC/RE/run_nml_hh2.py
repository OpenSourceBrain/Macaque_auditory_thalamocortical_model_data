#!/usr/bin/env python3
"""
Run NeuroML hh2-only cell simulation (NEURON backend), recording V, hh2 gates, and iDensity.
"""
import os
import shutil
import neuroml
from neuroml.loaders import read_neuroml2_file
from pyneuroml.pynml import write_neuroml2_file
from pyneuroml.lems import generate_lems_file_for_neuroml
from pyneuroml.runners import run_lems_with_jneuroml_neuron
from pyneuroml.analysis.NML2ChannelAnalysis import get_channel_gates


def run_hh2_nml():
    # Headless + NEURON backend setup
    os.environ.setdefault("MPLBACKEND", "Agg")
    os.environ["NEURON_NO_GUI"] = "1"
    os.environ.pop("DISPLAY", None)
    # Ensure NEURON_HOME is set so jNeuroML can find nrniv
    if not os.environ.get("NEURON_HOME"):
        nrniv = shutil.which("nrniv")
        if nrniv:
            os.environ["NEURON_HOME"] = os.path.dirname(os.path.dirname(nrniv))

    # Clean compiled mechanisms so jNeuroML will rebuild mods for this NML
    try:
        if os.path.isdir("x86_64"):
            shutil.rmtree("x86_64")
    except Exception:
        pass

    # Load hh2-only cell
    netdoc = read_neuroml2_file("RE_hh2_cell.nml")
    cell = netdoc.cells[0]

    # Create network
    net = netdoc.add(neuroml.Network, id="RE_hh2_net",
                     type="networkWithTemperature", temperature="36 degC", validate=False)
    pop = net.add(neuroml.Population, id="RE_hh2_pop", component=cell.id, size=1)

    # Stimulus: 200–700 ms, 300 pA
    pg1 = netdoc.add(neuroml.PulseGenerator(id="pg1", delay="200ms", duration="500ms", amplitude="200pA"))
    input_list1 = net.add(neuroml.InputList, id="input1_list", component=pg1.id, populations=pop.id)
    input_list1.add(neuroml.Input(id="0", target=f"../{pop.id}[0]", destination="synapses", segment_id="0", fraction_along="0.5"))

    # Write network file
    write_neuroml2_file(netdoc, "RE_hh2_cell.net.nml")

    # Build recorder dict: hh2_na/hh2_k gates and iDensity, plus V
    recorder = {}

    ch_na_doc = read_neuroml2_file("hh2_na.channel.nml")
    gates_na = get_channel_gates(ch_na_doc.ion_channel[0])
    for gate in gates_na:
        recorder[f"{gate}_hh2_na_state.dat"] = [f"{pop.id}[0]/biophys/membraneProperties/hh2_na_soma/hh2_na/{gate}/q"]
    recorder["hh2_na_iDensity.dat"] = [f"{pop.id}[0]/biophys/membraneProperties/hh2_na_soma/iDensity"]

    ch_k_doc = read_neuroml2_file("hh2_k.channel.nml")
    gates_k = get_channel_gates(ch_k_doc.ion_channel[0])
    for gate in gates_k:
        recorder[f"{gate}_hh2_k_state.dat"] = [f"{pop.id}[0]/biophys/membraneProperties/hh2_k_soma/hh2_k/{gate}/q"]
    recorder["hh2_k_iDensity.dat"] = [f"{pop.id}[0]/biophys/membraneProperties/hh2_k_soma/iDensity"]

    # V and spikes always produced via gen_spike_saves_for_all_somas

    generate_lems_file_for_neuroml(
        sim_id="RE_hh2_step_test",
        target=net.id,
        neuroml_file="RE_hh2_cell.net.nml",
        duration="1000ms",
        dt="0.025ms",
        lems_file_name="LEMS_RE_hh2_step_test.xml",
        nml_doc=netdoc,
        gen_spike_saves_for_all_somas=True,
        gen_saves_for_quantities=recorder,
        target_dir=".",
        copy_neuroml=False,
    )

    _ = run_lems_with_jneuroml_neuron("LEMS_RE_hh2_step_test.xml", load_saved_data=True, nogui=True)
    print("[NeuroML] hh2-only simulation complete.")


if __name__ == "__main__":
    run_hh2_nml()

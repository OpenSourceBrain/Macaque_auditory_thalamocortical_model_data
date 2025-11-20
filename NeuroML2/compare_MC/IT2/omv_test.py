#!/usr/bin/env python3
"""
Post process and add biophysics to cells and run a step current protocol
for the IT2_reduced_cell, using jNeuroML with NEURON backend.

Running this script with compile_mods=True will also cause NeuroML to
export corresponding NMODL (.mod) files for the mechanisms.
"""

import os
import random

import yaml
import neuroml
from neuroml.loaders import read_neuroml2_file
from pyneuroml.pynml import write_neuroml2_file, run_lems_with_jneuroml_neuron
from pyneuroml.lems import generate_lems_file_for_neuroml
from pyneuroml.plot import generate_plot
from pyneuroml.neuron import morphinfo, getinfo, load_hoc_or_python_file
from pyneuroml.annotations import create_annotation
from neuroml.utils import component_factory
from textwrap import indent

from pyneuroml.analysis import generate_current_vs_frequency_curve

random.seed(1412)

def step_current_omv():
    """Create a step current simulation OMV LEMS file and export NMODL."""

    # Headless / non-GUI environment for NEURON and plotting
    os.environ.setdefault("MPLBACKEND", "Agg")
    os.environ["NEURON_NO_GUI"] = "1"
    os.environ.pop("DISPLAY", None)

    # Help jNeuroML find NEURON installation (same pattern as RE/omv_test.py)
    if not os.environ.get("NEURON_HOME"):
        import shutil

        nrniv = shutil.which("nrniv")
        if nrniv:
            os.environ["NEURON_HOME"] = os.path.dirname(os.path.dirname(nrniv))

    # read the cell file, modify it, write a new one
    netdoc = read_neuroml2_file("IT2_reduced_cell.nml")
    IT2_reduced_cell = netdoc.cells[0]
    net = netdoc.add(neuroml.Network, id="IT2_reduced_cell_net", type="networkWithTemperature", temperature="34 degC", validate=False)
    pop = net.add(neuroml.Population, id="IT2_reduced_cell_pop", component=IT2_reduced_cell.id, size=1)

    pg1 = netdoc.add(
        neuroml.PulseGenerator(
            id="pg1", delay="200ms", duration="1600ms",
            amplitude="300pA"
        )
    )


    # Add these to cells
    input_list1 = net.add(
        neuroml.InputList(id="input1_list", component=pg1.id, populations=pop.id)
    )
    aninput1 = input_list1.add(
        neuroml.Input(
            id="0",
            target="../%s[0]" % (pop.id),
            destination="synapses",
            segment_id="0",
        )
    )



    write_neuroml2_file(netdoc, "IT2_reduced_cell.net.nml")

    generate_lems_file_for_neuroml(
        sim_id="IT2_reduced_cell_step_test",
        target=net.id,
        neuroml_file="IT2_reduced_cell.net.nml",
        duration="2000ms",
        dt="0.01ms",
        lems_file_name="LEMS_IT2_reduced_cell_step_test.xml",
        nml_doc=netdoc,
        gen_spike_saves_for_all_somas=True,
        target_dir=".",
        copy_neuroml=False
    )

    data = run_lems_with_jneuroml_neuron(
        "LEMS_IT2_reduced_cell_step_test.xml",
        load_saved_data=True,
        nogui=True,
    )

    print(data.keys())

    # print(data)
    generate_plot(
        xvalues=[data["t"]],
        yvalues=[data["IT2_reduced_cell_pop[0]/v"]],
        title="Membrane potential: IT2_reduced_cell",
    )

if __name__ == "__main__":
    step_current_omv()

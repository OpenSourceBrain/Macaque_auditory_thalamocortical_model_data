#!/usr/bin/env python3
"""
Post process and add biophysics to cells.

We make any updates to the morphology, and add biophysics.

File: NeuroML2/postprocess_cells.py

Copyright 2022 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""


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
    """Create a step current simulation OMV LEMS file"""
    # read the cell file, modify it, write a new one
    netdoc = read_neuroml2_file("RE_reduced_cell.nml")
    RE_reduced_cell = netdoc.cells[0]
    net = netdoc.add(neuroml.Network, id="RE_reduced_cell_net", type="networkWithTemperature", temperature="34 degC", validate=False)
    pop = net.add(neuroml.Population, id="RE_reduced_cell_pop", component=RE_reduced_cell.id, size=1)

    pg1 = netdoc.add(
        neuroml.PulseGenerator(
            id="pg1", delay="0ms", duration="1600ms",
            amplitude="-300pA"
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



    write_neuroml2_file(netdoc, "RE_reduced_cell.net.nml")

    generate_lems_file_for_neuroml(
        sim_id="RE_reduced_cell_step_test",
        target=net.id,
        neuroml_file="RE_reduced_cell.net.nml",
        duration="2000ms",
        dt="0.01ms",
        lems_file_name="LEMS_RE_reduced_cell_step_test.xml",
        nml_doc=netdoc,
        gen_spike_saves_for_all_somas=True,
        target_dir=".",
        copy_neuroml=False
    )

    data = run_lems_with_jneuroml_neuron(
        "LEMS_RE_reduced_cell_step_test.xml", load_saved_data=True, compile_mods=True
    )

    print(data.keys())

    # print(data)
    generate_plot(
        xvalues=[data["t"]],
        yvalues=[data["RE_reduced_cell_pop[0]/v"]],
        title="Membrane potential: RE_reduced_cell",
    )

if __name__ == "__main__":
    step_current_omv()



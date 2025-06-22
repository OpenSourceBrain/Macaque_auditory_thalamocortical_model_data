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

random.seed(1412)

def step_current_omv():
    """Create a step current simulation OMV LEMS file"""
    # read the cell file, modify it, write a new one
    netdoc = read_neuroml2_file("IT2_reduced_cell.nml")
    IT2_reduced_cell = netdoc.cells[0]
    net = netdoc.add(neuroml.Network, id="IT2_reduced_cell_net", validate=False)
    pop = net.add(neuroml.Population, id="IT2_reduced_cellpop", component=IT2_reduced_cell.id, size=1)

    # should be same as test_kc.py
    pg = netdoc.add(
        neuroml.PulseGenerator(
            id="pg", delay="200ms", duration="1500ms",
            amplitude="500pA"
        )
    )

    # Add these to cells
    input_list = net.add(
        neuroml.InputList(id="input_list", component=pg.id, populations=pop.id)
    )
    aninput = input_list.add(
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
        duration="3000ms",
        dt="0.01ms",
        lems_file_name="LEMS_IT2_reduced_cell_step_test.xml",
        nml_doc=netdoc,
        gen_spike_saves_for_all_somas=True,
        target_dir=".",
        copy_neuroml=False
    )

    data = run_lems_with_jneuroml_neuron(
        "LEMS_IT2_reduced_cell_step_test.xml", load_saved_data=True, compile_mods=True
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



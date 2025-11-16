#!/usr/bin/env python3
"""
Post process and add biophysics to cells.
We make any updates to the morphology, and add biophysics.
File: NeuroML2/postprocess_cells.py
Copyright 2022 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""
import random
import os
import yaml
import neuroml
from neuroml.loaders import read_neuroml2_file
from pyneuroml.pynml import write_neuroml2_file, run_lems_with_jneuroml_neuron
from pyneuroml.lems import generate_lems_file_for_neuroml
from pyneuroml.plot import generate_plot
from neuroml.utils import component_factory
from textwrap import indent
import copy
import matplotlib
import shutil
import neuroml
import numpy
import subprocess
from pyneuroml.io import write_neuroml2_file, read_neuroml2_file
from pyneuroml.lems import generate_lems_file_for_neuroml
from pyneuroml.runners import run_lems_with_jneuroml
from pyneuroml.plot import generate_plot 
from pyneuroml.analysis.NML2ChannelAnalysis import get_channel_gates
from pyneuroml.utils.plot import get_next_hex_color 
import datetime
import random
from pyneuroml.analysis import generate_current_vs_frequency_curve  
random.seed(1412)
def step_current_omv():
    # Headless + NEURON backend setup
    os.environ.setdefault("MPLBACKEND", "Agg")
    os.environ["NEURON_NO_GUI"] = "1"
    os.environ.pop("DISPLAY", None)
    if not os.environ.get("NEURON_HOME"):
        nrniv = shutil.which("nrniv")
        if nrniv:
            os.environ["NEURON_HOME"] = os.path.dirname(os.path.dirname(nrniv))
    netdoc = read_neuroml2_file("RE_reduced_cell.nml")
    RE_reduced_cell = netdoc.cells[0]
    net = netdoc.add(neuroml.Network, id="RE_reduced_cell_net", type="networkWithTemperature", temperature="34 degC", validate=False)
    pop = net.add(neuroml.Population, id="RE_reduced_cell_pop", component=RE_reduced_cell.id, size=1)
    pg1 = netdoc.add(
        neuroml.PulseGenerator(
            id="pg1", delay="200ms", duration="500ms",
            amplitude="300pA"
        )
    )
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
    recorder_dict = {}
    
    channel_doc1 = read_neuroml2_file(f"hh2_na.channel.nml")
    ion_channel1 = channel_doc1.ion_channel[0]

    channel_doc2 = read_neuroml2_file(f"hh2_k.channel.nml")
    ion_channel2 = channel_doc2.ion_channel[0]

    '''

    recorder_dict[f"{channel}_erev.dat"] = [
        f"{pop.id}[0]/biophys/membraneProperties/itre_soma/erev"
    ]
    
    recorder_dict["caConcExt.dat"] = [
        f"{pop.id}[0]/caConcExt"
    ]


    recorder_dict["caConc.dat"] = [
        f"{pop.id}[0]/caConc"
    ]
    

    '''

    '''
    recorder_dict[f"{channel}_iDensity.dat"] = [
        f"{pop.id}[0]/biophys/membraneProperties/itre_soma/iDensity"
    ]
    '''

    gates1 = get_channel_gates(ion_channel1)
    
    for gate in gates1:
        recorder_dict[f"{gate}_hh2_na_state.dat"] = [
            f"{pop.id}[0]/biophys/membraneProperties/hh2_na_soma/hh2_na/{gate}/q"
        ]

    gates2 = get_channel_gates(ion_channel2)
    
    for gate in gates2:
        recorder_dict[f"{gate}_hh2_k_state.dat"] = [
            f"{pop.id}[0]/biophys/membraneProperties/hh2_k_soma/hh2_k/{gate}/q"
        ]


    recorder_dict[f"hh2_k_iDensity.dat"] = [
        f"{pop.id}[0]/biophys/membraneProperties/hh2_k_soma/iDensity"
    ]
    
    recorder_dict[f"hh2_na_iDensity.dat"] = [
        f"{pop.id}[0]/biophys/membraneProperties/hh2_na_soma/iDensity"
    ]
    
    generate_lems_file_for_neuroml(
        sim_id="RE_reduced_cell_step_test",
        target=net.id,
        neuroml_file="RE_reduced_cell.net.nml",
        duration="1000ms",
        dt="0.025ms",
        lems_file_name="LEMS_RE_reduced_cell_step_test.xml",
        nml_doc=netdoc,
        gen_spike_saves_for_all_somas=True,
        gen_saves_for_quantities=recorder_dict,
        target_dir=".",
        copy_neuroml=False
    )
    data = run_lems_with_jneuroml_neuron(
        "LEMS_RE_reduced_cell_step_test.xml", load_saved_data=True, nogui=True
    )
    print(data.keys())

    '''
    (Plotting disabled for headless runs)
    '''

if __name__ == "__main__":
    step_current_omv()

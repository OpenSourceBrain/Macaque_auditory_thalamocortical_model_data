#!/usr/bin/env python3

import random
import numpy
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

def postprocess1():

    generate_current_vs_frequency_curve(
        nml2_file="IT2_reduced_cell.nml",
        cell_id="IT2_reduced_cell_0_0",
        custom_amps_nA=list(numpy.arange(-0.05, -0.1, -0.01)),
        pre_zero_pulse=200,
        post_zero_pulse=300,
        temperature = "34degC",
        plot_voltage_traces=True,
        plot_iv=True,
        plot_if=False,
        simulator="jNeuroML_NEURON",
        analysis_delay=300.0,
        analysis_duration=600.0,
    )
    

def postprocess2():

    generate_current_vs_frequency_curve(
        nml2_file="IT2_reduced_cell.nml",
        cell_id="IT2_reduced_cell_0_0",
        plot_voltage_traces=True,
        spike_threshold_mV=-10.0,
        # custom_amps_nA=list(numpy.arange(0, 0.3, 0.01)),
        custom_amps_nA=[0.2, 0.3, 0.4, 0.5],
        pre_zero_pulse=200,
        post_zero_pulse=300,
        temperature = "34degC",
        plot_iv=True,
        simulator="jNeuroML_NEURON",
        analysis_delay=300.0,
        analysis_duration=400.0,
    )
if __name__ == "__main__":
    postprocess1()
    postprocess2()


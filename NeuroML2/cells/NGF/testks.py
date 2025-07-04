#!/usr/bin/env python3
"""
Generate scripts to test KS channels.

Since we don't currently have the protocol implemented for the NeuroML
channels.

File: testks.py

Copyright 2024 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""

import matplotlib
import shutil
import neuroml
import numpy
import subprocess
from neuroml.utils import component_factory
from pyneuroml.io import write_neuroml2_file, read_neuroml2_file
from pyneuroml.lems import generate_lems_file_for_neuroml
from pyneuroml.runners import run_lems_with_jneuroml
from pyneuroml.plot import generate_plot
from pyneuroml.neuron.analysis.HHanalyse import get_states
from pyneuroml.analysis.NML2ChannelAnalysis import get_ks_channel_states
from pyneuroml.utils.plot import get_next_hex_color
import neuron
import datetime
import random

matplotlib.rcParams["figure.dpi"] = 200


timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
g_pas = 1 / 120236  # 1/ohm-cm2


def test_channel_mod(channel=None, ion=None, erev=None, gbar_var=None, gbar=None, amplitude=None,
                     ca=False):
    """Generate script for KS channel mod file

    :param channel_file: TODO
    :returns: TODO

    """
    myrand = random.Random(123)
    shutil.rmtree("x86_64", ignore_errors=True)

    h = neuron.h
    h.celsius = 34
    h.load_file("stdrun.hoc")
    h(
        """
    objref p
    p = new PythonObject()
    """
    )
    # Create a section, set size & insert pas, passive channel mechanism
    soma = h.Section(name="soma")

    soma.L = 10
    soma.nseg = 1
    for seg in soma:
        soma.diam = 5
        soma.cm = 0.64
        soma.Ra = 120

    soma.insert("pas")
    soma(0.5).g_pas = g_pas
    soma(0.5).e_pas = -65

    if ca is True:
        try:
            soma.insert("CaClamp")
        except ValueError:
            try:
                subprocess.run(
                    args=["nrnivmodl", "mod"], check=True, capture_output=True
                )
            except subprocess.CalledProcessError as e:
                return 1
            h.nrn_load_dll("x86_64/.libs/libnrnmech.so")
            soma.insert(str("CaClamp"))

            ca_obj = getattr(soma(0.5), "_ref_cai")
            caRec = h.Vector().record(ca_obj)

    if channel:
        states_rec = []
        try:
            soma.insert(str(channel))
        except ValueError:
            try:
                subprocess.run(
                    args=["nrnivmodl", "mod"], check=True, capture_output=True
                )
            except subprocess.CalledProcessError as e:
                return 1
            h.nrn_load_dll("x86_64/.libs/libnrnmech.so")
            soma.insert(str(channel))

        if erev:
            setattr(soma(0.5), f"e{ion}", float(erev))
        if gbar:
            setattr(soma(0.5), f"{gbar_var}_{channel}", float(gbar))

        modFileName = f"mod/{channel}.mod"
        with open(modFileName, "r") as handle:
            modFileTxt = handle.read()
        states = get_states(modFileTxt)

        # remove unused states
        try:
            states.remove("Ca")
        except ValueError:
            pass
        try:
            states.remove("Ia")
        except ValueError:
            pass

        states = sorted(states)
        for s in states:
            chan_obj = getattr(soma(0.5), f"_ref_{s}_{channel}")
            states_rec.append(h.Vector().record(chan_obj))
    else:
        channel = "pas"

    # recording
    vRec = h.Vector().record(soma(0.5)._ref_v)
    tRec = h.Vector().record(h._ref_t)

    if amplitude is not None:
        ic = h.IClamp(soma(0.5))
        ic.delay = 500
        ic.dur = 1000
        ic.amp = float(amplitude)

    v0 = -65.0  # Pre holding potential

    h.finitialize(v0)
    h.dt = 0.01
    h.continuerun(1500)

    colors = [get_next_hex_color(myrand) for i in range(len(states))]

    # print(tRec.to_python())
    generate_plot(
        xvalues=[tRec.to_python()],
        yvalues=[vRec.to_python()],
        title="NEURON",
        labels=["v"],
        show_plot_already=True,
        xaxis="time (ms)",
        yaxis="v (mV)",
        ylim=[-85, 100],
        save_figure_to=f"{timestamp}_test_{channel}_NEURON.png",
        title_above_plot="NEURON",
        legend_position="outer right"
    )

    if ca is not False:
        generate_plot(
            xvalues=[tRec.to_python()],
            yvalues=[caRec.to_python()],
            title="NEURON",
            labels=["caConc"],
            show_plot_already=True,
            xaxis="time (ms)",
            yaxis="conc",
            save_figure_to=f"{timestamp}_test_{channel}_ca_NEURON.png",
            title_above_plot="NEURON",
            legend_position="outer right"
        )

    generate_plot(
        xvalues=[tRec.to_python()] * len(states),
        yvalues=[rec.to_python() for rec in states_rec],
        title="NEURON: states",
        labels=states,
        colors=colors,
        show_plot_already=True,
        xaxis="time (ms)",
        yaxis="rate",
        ylim=[-0.1, 1.1],
        save_figure_to=f"{timestamp}_test_{channel}_states_NEURON.png",
        title_above_plot="NEURON",
        legend_position="outer right"
    )

    return [tRec.to_python()] * len(states), [rec.to_python() for rec in states_rec]
    """
    with open(f"{timestamp}_states_nrn.dat", 'w') as f:
        xvalues = tRec.to_python()
        yvalues = [rec.to_python() for rec in states_rec],
        for t in range(len(xvalues)):
            for ys in yvalues:
                yvalsstrs = [str(v[t]) for v in ys]
                yvalstr = '\t'.join(yvalsstrs)
                print(str(xvalues[t]) + "\t" + yvalstr, file=f)
    """


def test_channel_nml(
    channel=None, ion=None, erev=None, amplitude=None, gbar=None,
    record_data={},
    ca=False
):
    """Generate script for KS channel NML file

    :param channel: TODO
    :returns: TODO

    """
    myrand = random.Random(123)
    shutil.rmtree("x86_64", ignore_errors=True)
    newdoc = component_factory(neuroml.NeuroMLDocument, id="testdoc")

    newcell = newdoc.add(neuroml.Cell, id="testcell", validate=False)  # type: neuroml.Cell
    newcell.setup_nml_cell()
    newcell.set_spike_thresh("10mV")
    newcell.set_specific_capacitance("0.64 uF_per_cm2")
    newcell.set_resistivity("120 ohm_cm")
    newcell.set_init_memb_potential("-65 mV")

    # set calcium concentrations
    if ca is True:
        newdoc.add(neuroml.IncludeType, href="channels/CaClamp.nml")
        newcell.add_intracellular_property(
            "Species", id="ca", ion="ca", concentration_model="CaClamp",
            initial_concentration="5.0E-11 mol_per_cm3",
            initial_ext_concentration="2.0E-6 mol_per_cm3"
        )

    newcell.add_segment(
        prox=[0, 0, 0, 5],
        dist=[10, 0, 0, 5],
        name="soma0",
        seg_type="soma",
        seg_id="0",
        use_convention=True,
    )

    # add passive
    newcell.add_channel_density(
        newdoc,
        cd_id="pas",
        ion_channel="pas",
        ion="non_specific",
        group_id="all",
        erev="-65mV",
        cond_density=f"{g_pas} S_per_cm2",
        ion_chan_def_file="channels/pas.channel.nml",
    )

    if channel:
        newcell.add_channel_density(
            newdoc,
            cd_id=f"{channel}_chan",
            ion_channel=channel,
            ion=ion,
            group_id="all",
            erev=erev,
            cond_density=f"{gbar} S_per_cm2",
            ion_chan_def_file=f"channels/{channel}.channel.nml",
        )

    else:
        channel = "pas"

    newcell.morphinfo(True)
    newcell.biophysinfo()

    newnet = newdoc.add(
        neuroml.Network,
        id="testnet",
        type="networkWithTemperature",
        validate=False,
        temperature="34 degC",
    )
    newpop = newnet.add(neuroml.Population, id="testpop", component=newcell.id, size=1)

    # Define an external stimulus and add it to the model
    if amplitude is not None:
        pg = newdoc.add(
            "PulseGenerator",
            id="pulseGen_0",
            delay="500ms",
            duration="1000ms",
            amplitude=amplitude,
        )
        newnet.add(
            "ExplicitInput", target="%s[%i]" % (newpop.id, 0), input=pg.id
        )

    newdoc.validate(recursive=True)
    write_neuroml2_file(newdoc, f"Test_{channel}.net.nml")

    recorder_dict = {}
    include_extra_files = []
    if channel != "pas":
        include_extra_files = [f"channels/{channel}.channel.nml"]
        # set up recording of state occupancies
        channel_doc = read_neuroml2_file(f"channels/{channel}.channel.nml")
        ion_channel_ks = channel_doc.ion_channel_kses[0]  # type: neuroml.IonChannelKS
        state_info = get_ks_channel_states(ion_channel_ks)
        for gate, states in state_info.items():
            recorder_dict[f"{timestamp}_{gate}_states_nml.dat"] = []
            sorted_states = sorted(states)
            for s in sorted_states:
                recorder_dict[f"{timestamp}_{gate}_states_nml.dat"].append(
                    f"{newpop.id}[0]/biophys/membraneProperties/{channel}_chan/{channel}/{gate}/{s}/occupancy"
                )
    if ca is True:
        recorder_dict[f"{timestamp}_ca_nml.dat"] = [f"{newpop.id}[0]/caConc"]

    generate_lems_file_for_neuroml(
        sim_id=f"testsim_{channel}",
        neuroml_file=f"Test_{channel}.net.nml",
        target=newnet.id,
        duration="1500ms",
        dt="0.01ms",
        lems_file_name=f"LEMS_test_{channel}.xml",
        nml_doc=newdoc,
        target_dir=".",
        gen_saves_for_all_v=True,
        gen_saves_for_quantities=recorder_dict,
        include_extra_files=include_extra_files,
    )

    # run with jneuroml
    data = run_lems_with_jneuroml(
        f"LEMS_test_{channel}.xml",
        nogui=True,
        load_saved_data=True,
        show_plot_already=False,
        max_memory="5G",
    )
    keys = list(data.keys())
    print(f"Recorded data: {keys}")

    # membrane potential
    recorded_time = numpy.array(data.pop(keys[0])) * 1000
    recorded_v = numpy.array(data.pop(keys[1])) * 1000

    if ca is True:
        recorded_ca = numpy.array(data.pop(f"{newpop.id}[0]/caConc"))
        generate_plot(
            xvalues=[recorded_time],
            yvalues=[recorded_ca],
            title="NML",
            labels=["caConc"],
            show_plot_already=True,
            xaxis="time (ms)",
            yaxis="conc",
            save_figure_to=f"{timestamp}_test_{channel.lower()}_ca_NML.png",
            title_above_plot="NML",
            legend_position="outer right"
        )

    generate_plot(
        xvalues=[recorded_time],
        yvalues=[recorded_v],
        title="NML",
        labels=["v"],
        show_plot_already=True,
        xaxis="time (ms)",
        yaxis="v (mV)",
        ylim=[-85, 100],
        save_figure_to=f"{timestamp}_test_{channel.lower()}_NML.png",
        title_above_plot="NML",
        legend_position="outer right"
    )

    colors = [get_next_hex_color(myrand) for i in range(len(data.values()))]
    if channel != "pas":
        # states
        labels = [alab.split("/")[-2] for alab in data.keys()]
        generate_plot(
            xvalues=[recorded_time] * len(data.values()),
            yvalues=list(data.values()),
            title="NML",
            labels=labels,
            colors=colors,
            show_plot_already=True,
            xaxis="time (ms)",
            yaxis="rate",
            ylim=[-0.1, 1.1],
            save_figure_to=f"{timestamp}_test_{channel.lower()}_states_NML.png",
            title_above_plot="NML",
            legend_position="outer right"
        )
        return [recorded_time] * len(data.values()), data


if __name__ == "__main__":
    # passive
    """
    test_channel_nml(channel=None, amplitude="0.001 nA")
    test_channel_mod(channel=None, amplitude=0.001)
    """

    # NaRSG
    """
    test_channel_mod(channel="narsg", ion="na", erev="67", gbar_var="gbar", gbar=0.0, amplitude=0.001, ca=False)

    test_channel_nml(
        channel="NaRSG",
        ion="na",
        erev="67 mV",
        gbar=0.0,
        amplitude="0.001 nA",
        record_data={},
        ca=False
    )
    """

    # SK2: only calcium dependent, not voltage dependent
    """
    x1, y1 = test_channel_mod(channel="SK2", ion="k", erev="-84.69", gbar_var="gkbar", gbar=0.0, amplitude=None, ca=True)

    x2, data = test_channel_nml(
        channel="SK2",
        ion="k",
        erev="-84.69 mV",
        gbar=0.0,
        amplitude=None,
        record_data={},
        ca=True
    )

    # mslo
    x1, y1 = test_channel_mod(channel="mslo", ion="k", erev="-84.69", gbar_var="gbar", gbar=0.0, amplitude=None, ca=True)

    x2, data = test_channel_nml(
        channel="Kmslo",
        ion="k",
        erev="-84.69 mV",
        gbar=0.0,
        amplitude=None,
        record_data={},
        ca=True
    )
    """

    # CaT
    x1, y1 = test_channel_mod(channel="CaT", ion="ca", erev=None,
                              gbar_var=None, gbar=None, amplitude=None, ca=True)

    x2, data = test_channel_nml(
        channel="CaT",
        ion="ca",
        erev="120.0 mV",
        gbar=None,
        amplitude=None,
        record_data={},
        ca=True
    )

    # generate combined plot
    myrand = random.Random(123)
    colors = [get_next_hex_color(myrand) for i in range(len(data.values()))]
    labels = [alab.split("/")[-2] + " nrn" for alab in data.keys()]
    labels += [alab.split("/")[-2] + " nml" for alab in data.keys()]
    generate_plot(
        xvalues=x1 + x2,
        yvalues=y1 + list(data.values()),
        title="Combined states",
        labels=labels,
        colors=colors + colors,
        show_plot_already=True,
        xaxis="time (ms)",
        yaxis="rate",
        ylim=[-0.1, 1.1],
        # save_figure_to=f"{timestamp}_test_{channel.lower()}_states_NML.png",
        title_above_plot="Combined states",
        legend_position="outer right"
    )

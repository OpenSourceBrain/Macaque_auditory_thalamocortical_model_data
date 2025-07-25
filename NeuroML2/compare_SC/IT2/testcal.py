#!/usr/bin/env python3
"""
Generate scripts to test CaP channel (GHK based that requires a new component type definition).

File: testcat.py

Copyright 2024 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""

import copy
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
from pyneuroml.analysis.NML2ChannelAnalysis import get_channel_gates
from pyneuroml.utils.plot import get_next_hex_color
import neuron
import datetime
import random

matplotlib.rcParams["figure.dpi"] = 200


timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
g_pas = 0.0001  # 1/ohm-cm2


def test_channel_mod(channel=None, ion=None, erev=None, gbar_var=None, gbar=None, amplitude=None,
                     ca=False, ca_clamp=False):
    """Generate script for GHK channel mod file

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
        soma.cm = 2.5
        soma.Ra = 70

    soma.insert("pas")
    soma(0.5).g_pas = g_pas
    soma(0.5).e_pas = -86.0

    if ca_clamp is True:
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
            setattr(soma(0.5), "conc0_CaClamp", 1E-5)
            setattr(soma(0.5), "conc1_CaClamp", 1E-4)
            setattr(soma(0.5), "cai", 1E-4)
            setattr(soma(0.5), "cao", 2)

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

        current_obj = getattr(soma(0.5), f"_ref_ica_{channel}")
        iRec = h.Vector().record(current_obj)
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

    v0 = -85.7  # Pre holding potential

    if ca_clamp is False:
        print("No calcium clamp, but calcium ion included, so NEURON initialises them!")
        print("cai, by default is: " + str(getattr(soma(0.5), "cai")))
        print("cao, by default is: " + str(getattr(soma(0.5), "cao")))

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
        ylim=[-200, 200],
        save_figure_to=f"{timestamp}_test_{channel}_NEURON.png",
        title_above_plot="NEURON",
        legend_position="outer right"
    )

    if ca_clamp is True:
        generate_plot(
            xvalues=[tRec.to_python()],
            yvalues=[caRec.to_python()],
            title="NEURON",
            labels=["caConc"],
            show_plot_already=True,
            xaxis="time (ms)",
            yaxis="conc",
            save_figure_to=f"{timestamp}_test_{channel.lower()}_ca_NEURON.png",
            title_above_plot="NEURON",
            legend_position="outer right"
        )
    if ca is True:
        generate_plot(
            xvalues=[tRec.to_python()],
            yvalues=[numpy.array(iRec.to_python()) * 10],  # convert to SI
            title="NEURON",
            labels=["ica"],
            show_plot_already=True,
            xaxis="time (ms)",
            yaxis="i",
            save_figure_to=f"{timestamp}_test_{channel.lower()}_ca_i_NEURON.png",
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
        save_figure_to=f"{timestamp}_test_{channel.lower()}_states_NEURON.png",
        title_above_plot="NEURON",
        legend_position="outer right"
    )

    return {"t": tRec.to_python(),
            "states": [rec.to_python() for rec in states_rec],
            "ica": list(numpy.array(iRec.to_python()) * 10)  # conver to SI
            }
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
    ca=False, ca_clamp=False,
    new_channel_density=None
):
    """Generate script for GHK channel NML file

    :param channel: TODO
    :returns: TODO

    """
    myrand = random.Random(123)
    shutil.rmtree("x86_64", ignore_errors=True)
    include_extra_files = []

    newdoc = read_neuroml2_file("testcell.nml")
    newnet = newdoc.add(
        neuroml.Network,
        id="testnet",
        type="networkWithTemperature",
        validate=False,
        temperature="34 degC",
    )
    newpop = newnet.add(neuroml.Population, id="testpop", component="testcell", size=1)

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

    if channel != "pas":
        # set up recording of state occupancies
        channel_doc = read_neuroml2_file(f"channels/{channel}.channel.nml")
        ion_channel_ghk = channel_doc.ion_channel[0]  # type: neuroml.IonChannelHH
        gates = get_channel_gates(ion_channel_ghk)

        # note, the ID here needs to be the ID of the channel density component
        for gate in gates:
            recorder_dict[f"{timestamp}_{gate}_nml.dat"] = []
            recorder_dict[f"{timestamp}_{gate}_nml.dat"].append(
                f"{newpop.id}[0]/biophys/membraneProperties/cal_soma/{channel}/{gate}/q"
            )
    if ca is True:
        recorder_dict[f"{timestamp}_ca_nml.dat"] = [f"{newpop.id}[0]/caConc"]
        recorder_dict[f"{timestamp}_ca_i_nml.dat"] = [f"{newpop.id}[0]/biophys/membraneProperties/cal_soma/iDensity"]

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

        recorded_ca_i = numpy.array(data.get(f"{newpop.id}[0]/biophys/membraneProperties/cal_soma/iDensity"))
        # match direction to NEURON
        generate_plot(
            xvalues=[recorded_time],
            yvalues=[recorded_ca_i * -1],
            title="NML",
            labels=["ica"],
            show_plot_already=True,
            xaxis="time (ms)",
            yaxis="i",
            save_figure_to=f"{timestamp}_test_{channel.lower()}_ca_i_NML.png",
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
        ylim=[-200, 200],
        save_figure_to=f"{timestamp}_test_{channel.lower()}_NML.png",
        title_above_plot="NML",
        legend_position="outer right"
    )

    # plot states, but remove Ca density etc.
    recorded_ca_i_key = None
    data_copy = copy.deepcopy(data)
    for key, value in data_copy.items():
        if "iDensity" in key:
            recorded_ca_i_key = key
            break
    if recorded_ca_i_key is not None:
        data_copy.pop(recorded_ca_i_key)

    colors = [get_next_hex_color(myrand) for i in range(len(data_copy.values()))]
    if channel != "pas":
        # states
        labels = [alab.split("/")[-2] for alab in data_copy.keys()]
        generate_plot(
            xvalues=[recorded_time] * len(data_copy.values()),
            yvalues=list(data_copy.values()),
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
    return recorded_time, data


if __name__ == "__main__":
    # cal
    nrn_data = test_channel_mod(channel="cal", ion="ca", erev=None,
                                gbar_var=None, gbar=None, amplitude=0.0005,
                                ca=True, ca_clamp=True)

    x1 = [nrn_data["t"]] * len(nrn_data["states"])
    y1 = nrn_data["states"]
    nrn_cai = nrn_data.get("ica", None)

    x2, data = test_channel_nml(
        channel="cal",
        ion="ca",
        erev=None,
        gbar=None,
        amplitude="0.0005 nA",
        record_data={},
        ca=True,
        ca_clamp=True
    )

    recorded_ca_i_key = None
    for key, value in data.items():
        if "iDensity" in key:
            recorded_ca_i_key = key
            break

    # pop outside the loop
    if recorded_ca_i_key is not None and nrn_cai is not None:
        recorded_ca_i = numpy.array(data.pop(key)) * -1
        generate_plot(
            xvalues=[nrn_data["t"], x2],
            yvalues=[nrn_cai, recorded_ca_i],
            title="CaI (both)",
            labels=["nrn", "nml"],
            show_plot_already=True,
            xaxis="time (ms)",
            yaxis="i",
            # save_figure_to=f"{timestamp}_test_{channel.lower()}_states_NML.png",
            title_above_plot="Combined currents",
            legend_position="outer right"
        )

    # generate combined plot of states
    myrand = random.Random(123)
    colors = [get_next_hex_color(myrand) for i in range(len(data.values()))]
    labels = [alab.split("/")[-2] + " nrn" for alab in data.keys()]
    labels += [alab.split("/")[-2] + " nml" for alab in data.keys()]
    generate_plot(
        xvalues=x1 + [x2] * len(data.values()),
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
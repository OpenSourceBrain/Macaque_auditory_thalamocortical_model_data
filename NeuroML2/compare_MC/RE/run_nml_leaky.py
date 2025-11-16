#!/usr/bin/env python3
"""
Run NeuroML leaky (pas-only) cell simulation (NEURON backend), recording V.

The morphology, passive properties, temperature, and stimulus match the
RE hh2 setups, but the active hh2 Na/K conductances are set to zero so
that only the passive leak contributes to the voltage.
"""
from __future__ import annotations

import os
import shutil

import neuroml
from neuroml.loaders import read_neuroml2_file
from pyneuroml.pynml import write_neuroml2_file
from pyneuroml.lems import generate_lems_file_for_neuroml
from pyneuroml.runners import run_lems_with_jneuroml_neuron


def run_nml_leaky():
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

    # Load hh2-only cell and zero out hh2 Na/K conductances to get pas-only
    netdoc = read_neuroml2_file("RE_hh2_cell.nml")
    cell = netdoc.cells[0]

    mp = cell.biophysical_properties.membrane_properties
    for cd in mp.channel_densities:
        if cd.id in ("hh2_k_soma", "hh2_na_soma"):
            cd.cond_density = "0 S_per_cm2"

    # Create a simple one-cell network using this passive-only cell
    net = netdoc.add(
        neuroml.Network,
        id="RE_leaky_net",
        type="networkWithTemperature",
        temperature="36 degC",
        validate=False,
    )
    pop = net.add(neuroml.Population, id="RE_leaky_pop", component=cell.id, size=1)

    # Stimulus: 200–700 ms, 300 pA
    pg = netdoc.add(
        neuroml.PulseGenerator(
            id="pg_leaky", delay="200ms", duration="500ms", amplitude="400pA"
        )
    )
    input_list = net.add(
        neuroml.InputList(
            id="input_leaky_list", component=pg.id, populations=pop.id
        )
    )
    input_list.add(
        neuroml.Input(
            id="0",
            target=f"../{pop.id}[0]",
            destination="synapses",
            segment_id="0",
            fraction_along="0.5",
        )
    )

    # Write network file
    write_neuroml2_file(netdoc, "RE_leaky_cell.net.nml")

    # Only voltage and spikes are needed; recorder dict can be empty
    recorder = {}

    generate_lems_file_for_neuroml(
        sim_id="RE_leaky_step_test",
        target=net.id,
        neuroml_file="RE_leaky_cell.net.nml",
        duration="1000ms",
        dt="0.025ms",
        lems_file_name="LEMS_RE_leaky_step_test.xml",
        nml_doc=netdoc,
        gen_spike_saves_for_all_somas=True,
        gen_saves_for_quantities=recorder,
        target_dir=".",
        copy_neuroml=False,
    )

    _ = run_lems_with_jneuroml_neuron(
        "LEMS_RE_leaky_step_test.xml", load_saved_data=True, nogui=True
    )
    print("[NeuroML] leaky (pas-only) simulation complete.")


if __name__ == "__main__":
    run_nml_leaky()


#!/usr/bin/env python3
"""
Create a summary readme file

File: create_summary_readme.py

Copyright 2025 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""


from pathlib import Path
from contextlib import chdir
import json
import numpy as np
from pyneuroml.plot import generate_plot


cwd = Path('.')
directories = [d for d in cwd.iterdir() if d.is_dir() and not d.name.startswith(".")]

md_text = "# Comparison: NetPyNE vs NeuroML\n\n"
md_text += "| Channel | mod source | NeuroML source |  NetPyNE plot | NeuroML plot | Combined plot|\n"
md_text += "|---------|------------|----------------|---------------|--------------|--------------|\n"

for d in directories:
    print(f"--> Processing {d.name}")
    channel = d.name
    mod_source = f"[{channel}.mod](../mod/{channel}.mod)"
    nml_source = f"[{channel}.channel.nml](../{channel}.channel.nml)"
    np_data = list(d.glob("netpyne*json"))[0]
    np_plot = np_data.name.replace(".json", ".png")
    nml_data = list(d.glob("nml*dat"))[0]
    nml_plot = f"nml_{channel}.png"
    combined_plot = f"{d.name}/Figure_1.png"

    md_text += f"| {channel} | {mod_source} | {nml_source} | ![{channel} NetPyNE]({np_plot}) | ![{channel} NML]({nml_plot}) | ![{channel} combined]({combined_plot})\n"

    combined_figure = Path(d) / Path("Figure_1.png")

    if not combined_figure.exists():
        print("--> All required figures not found, re-generating")
        with chdir(d):
            dat_data = np.loadtxt(nml_data.name)
            time_dat = dat_data[:, 0]
            voltage_dat = dat_data[:, 1] * 1000

            voltage_json = None
            time_json = None

            with open(np_data.name, 'r') as f:
                json_data = json.load(f)

                voltage_json = json_data['simData']['V_soma']['cell_0']

                dt = 1e-5
                time_json = np.arange(len(voltage_json)) * dt

            generate_plot([time_dat, time_json], [voltage_dat, voltage_json], title="Comparison of Voltage from nml and netpyne", labels=["NML", "NetPyNE"], colors=["b", "r"], linestyles=["-", "--"], xaxis="Time (s)", yaxis="Voltage (mV)", show_plot_already=False, title_above_plot=True, save_figure_to="Figure_1.png", close_plot=True, xlim=[min(time_dat[0], time_json[0]), max(time_dat[-1], time_json[-1])], font_size=12)

print("--> Writing README.md")
with open("README.md", 'w') as f:
    print(md_text, file=f)

#!/usr/bin/env python3
"""
Create a summary readme file

File: create_summary_readme.py

Copyright 2025 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""


from pathlib import Path


cwd = Path('.')
directories = [d for d in cwd.iterdir() if d.is_dir() and not d.name.startswith(".")]

md_text = "# Comparison: NetPyNE vs NeuroML\n\n"
md_text += "| Channel | mod source | NeuroML source |  NetPyNE plot | NeuroML plot | Combined plot|\n"
md_text += "|---------|------------|----------------|---------------|--------------|--------------|\n"

for d in directories:
    print(f"Looking in {d.name}")
    channel = d.name
    mod_source = f"[{channel}.mod](../mod/{channel}.mod)"
    nml_source = f"[{channel}.channel.nml](../{channel}.channel.nml)"
    np_plot = list(d.glob("netpyne*png"))[0]
    nml_plot = list(d.glob("nml*png"))[0]
    combined_plot = f"{d.name}/Figure_1.png"

    md_text += f"| {channel} | {mod_source} | {nml_source} | ![{channel} NetPyNE]({np_plot}) | ![{channel} NML]({nml_plot}) | ![{channel} combined]({combined_plot})\n"

with open("README.md", 'w') as f:
    print(md_text, file=f)

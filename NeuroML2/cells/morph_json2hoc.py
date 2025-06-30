import json
import sys

def json2hoc(acell):
### extract morphology data and then make manual adjustments
    with open(f"{acell}_reduced_cellParams.json") as file:
        data = json.load(file)

    topol_data = {}
    for sec_name, sec_info in data['secs'].items():
        if 'topol' in sec_info:
            topol_data[sec_name] = sec_info['topol']

    morpho_data = {}
    for sec_name, sec_info in data['secs'].items():
        if 'geom' in sec_info and 'pt3d' in sec_info['geom']:
            morpho_data[sec_name] = sec_info['geom']['pt3d']

    connections = []
    sections = {}

    for sec_name, topol_info in topol_data.items():
        parent_sec = topol_info.get('parentSec')
        if parent_sec:
            connections.append((sec_name.strip(), parent_sec))

    for sec_name, pt3d_info in morpho_data.items():
        sections[sec_name] = []
        for point in pt3d_info:
            sections[sec_name].append(point)

    hoc_code = ""

    hoc_code += "proc topol() { \n"
    for child, parent in connections:
        hoc_code += f"  connect {child}(0), {parent}(1)\n"
    hoc_code += "}\n\n"

    for sec_name, pt3d_points in sections.items():
        hoc_code += f"  {sec_name} {{\n"  
        hoc_code += "    pt3dclear()\n"
        for point in pt3d_points:
            x, y, z, diam = point
            hoc_code += f"    pt3dadd({x}, {y}, {z}, {diam})\n"  
        hoc_code += "  }\n"  

    with open(f"{acell}_reduced_cell.hoc", 'w') as file:
        file.write(hoc_code)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(1)
    
    acell = sys.argv[1]
    json2hoc(acell)
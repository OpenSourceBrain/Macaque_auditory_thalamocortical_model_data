import sys
import pyneuroml.pynml
from pyneuroml.plot.PlotMorphology import plot_2D

def plot_cell_morphology(acell):
    """Plot 2D morphology of a given cell (e.g., 'CT6')."""
    nml2_file = f"{acell}_reduced_cell.nml"
    
    print(f"Visualizing morphology for: {nml2_file}")
    
    # Convert to PNG
    pyneuroml.pynml.nml2_to_png(nml2_file)
    
    # Plot 2D morphology
    plot_2D(nml2_file)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python viz_morph.py <acell> (e.g., CT6)")
        sys.exit(1)
    
    acell = sys.argv[1]
    plot_cell_morphology(acell)
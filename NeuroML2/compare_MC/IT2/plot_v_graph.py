import matplotlib.pyplot as plt
import numpy as np
import sys

def plot_voltage(file_path):
    data = np.loadtxt(file_path)
    time = data[:, 0] * 1000     # COnvert s to ms
    voltage = data[:, 1] * 1000  # Convert V to mV
    
    plt.figure(figsize=(10, 6))
    plt.plot(time, voltage, 'b-', linewidth=2)
    plt.title("Membrane Potential")
    plt.xlabel("Time (ms)")
    plt.ylabel("Voltage (mV)")
    plt.grid(True)
    
    output_file = file_path.replace('.dat', '.png')
    plt.savefig(output_file)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python plot_voltage.py <data_file>")
        sys.exit(1)
    plot_voltage(sys.argv[1])
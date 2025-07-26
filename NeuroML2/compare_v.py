import numpy as np
import matplotlib.pyplot as plt
import json

dat_file = "cells/IT2/IT2_reduced_cell_step_test.IT2_reduced_cell_pop.v.dat"
json_file = "compare_MC/IT2/IT2_reduced_json_data.json"

dat_data = np.loadtxt(dat_file)
time_dat = dat_data[:, 0] 
voltage_dat = dat_data[:, 1] * 1000

with open(json_file, 'r') as f:
    json_data = json.load(f)

voltage_json = json_data['simData']['V_soma']['cell_0']

dt = 1e-5
time_json = np.arange(len(voltage_json)) * dt

plt.figure(figsize=(12, 6))

plt.plot(time_dat, voltage_dat, 'b-', label='nml Voltage', linewidth=2)

plt.plot(time_json, voltage_json, 'r--', label='netpyne Voltage', linewidth=1.5)

plt.xlabel('Time (s)', fontsize=12)
plt.ylabel('Voltage (mV)', fontsize=12)
plt.title('Comparison of Voltage from nml and netpyne', fontsize=16)
plt.legend(fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)

plt.xlim([min(time_dat[0], time_json[0]), max(time_dat[-1], time_json[-1])])
plt.tight_layout()

plt.show()
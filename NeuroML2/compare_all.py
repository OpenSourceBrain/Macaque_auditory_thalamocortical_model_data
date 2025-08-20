import numpy as np
import matplotlib.pyplot as plt
import json
import os

def compare_all():
    dat_file = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/compare_MC/RE/RE_reduced_cell_step_test.RE_reduced_cell_pop.v.dat"
    json_file = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/compare_MC/RE/RE_reduced_itre_data.json"
    m_itre_dat_file = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/compare_MC/RE/m_itre_state.dat"
    h_itre_dat_file = "/home/gluciferd/Macaque_auditory_thalamocortical_model_data/NeuroML2/compare_MC/RE/h_itre_state.dat"

    dat_data = np.loadtxt(dat_file)
    time_dat = dat_data[:, 0] 
    voltage_dat = dat_data[:, 1] * 1000  

    m_itre_dat_data = np.loadtxt(m_itre_dat_file)
    time_m_itre_dat = m_itre_dat_data[:, 0]
    m_itre_dat = m_itre_dat_data[:, 1]

    h_itre_dat_data = np.loadtxt(h_itre_dat_file)
    time_h_itre_dat = h_itre_dat_data[:, 0]
    h_itre_dat = h_itre_dat_data[:, 1]

    with open(json_file, 'r') as f:
        json_data = json.load(f)

    voltage_json = json_data['simData']['V_soma']['cell_0']
    h_itre_json = json_data['simData']['h_itre']['cell_0']
    m_itre_json = json_data['simData']['m_itre']['cell_0']

    dt = 1e-5
    time_json = np.arange(len(voltage_json)) * dt

    plt.figure(figsize=(15, 5))

    plt.subplot(1, 3, 1)
    plt.plot(time_dat, voltage_dat, 'b-', label='nml Voltage', linewidth=2)
    plt.plot(time_json, voltage_json, 'r--', label='netpyne Voltage', linewidth=1.5)
    plt.xlabel('Time (s)', fontsize=10)
    plt.ylabel('Voltage (mV)', fontsize=10)
    plt.title('Voltage Comparison', fontsize=12)
    plt.legend(fontsize=8)
    plt.grid(True, linestyle='--', alpha=0.7)

    plt.subplot(1, 3, 2)
    plt.plot(time_h_itre_dat, h_itre_dat, 'b-', label='nml h_itre', linewidth=2)
    plt.plot(time_json, h_itre_json, 'r--', label='netpyne h_itre', linewidth=1.5)
    plt.xlabel('Time (s)', fontsize=10)
    plt.ylabel('h_itre', fontsize=10)
    plt.title('h_itre Comparison', fontsize=12)
    plt.legend(fontsize=8)
    plt.grid(True, linestyle='--', alpha=0.7)

    plt.subplot(1, 3, 3)
    plt.plot(time_m_itre_dat, m_itre_dat, 'b-', label='nml m_itre', linewidth=2)
    plt.plot(time_json, m_itre_json, 'r--', label='netpyne m_itre', linewidth=1.5)
    plt.xlabel('Time (s)', fontsize=10)
    plt.ylabel('m_itre', fontsize=10)
    plt.title('m_itre Comparison', fontsize=12)
    plt.legend(fontsize=8)
    plt.grid(True, linestyle='--', alpha=0.7)

    plt.tight_layout()
    current_dir = os.getcwd()
    save_path = os.path.join(current_dir, "compare_all.png")
    plt.savefig(save_path, dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    compare_all()
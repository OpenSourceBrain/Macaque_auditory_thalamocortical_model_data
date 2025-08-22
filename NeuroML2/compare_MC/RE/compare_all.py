import numpy as np
import matplotlib.pyplot as plt
import json
import os
def compare_all():
    dat_file = "RE_reduced_cell_step_test.RE_reduced_cell_pop.v.dat"
    json_file = "RE_reduced_itre_data.json"
    m_itre_dat_file = "m_itre_state.dat"
    h_itre_dat_file = "h_itre_state.dat"
    ica_itre_dat_file = "itre_iDensity.dat"
    caConc_dat_file = "caConc.dat"
    
    dat_data = np.loadtxt(dat_file)
    time_dat = dat_data[:, 0] 
    voltage_dat = dat_data[:, 1] * 1000  
    m_itre_dat_data = np.loadtxt(m_itre_dat_file)
    time_m_itre_dat = m_itre_dat_data[:, 0]
    m_itre_dat = m_itre_dat_data[:, 1]
    h_itre_dat_data = np.loadtxt(h_itre_dat_file)
    time_h_itre_dat = h_itre_dat_data[:, 0]
    h_itre_dat = h_itre_dat_data[:, 1]
    ica_itre_dat_data = np.loadtxt(ica_itre_dat_file)
    time_ica_itre_dat = ica_itre_dat_data[:, 0]
    ica_itre_dat = ica_itre_dat_data[:, 1] * -0.1
    caConc_dat_data = np.loadtxt(caConc_dat_file)
    time_caConc_dat = caConc_dat_data[:, 0]
    caConc_dat = caConc_dat_data[:, 1]
    
    with open(json_file, 'r') as f:
        json_data = json.load(f)
    voltage_json = json_data['simData']['V_soma']['cell_0']
    h_itre_json = json_data['simData']['h_itre']['cell_0']
    m_itre_json = json_data['simData']['m_itre']['cell_0']
    ica_itre_json = json_data['simData']['ica_itre']['cell_0']
    caConc_json = json_data['simData']['caConc_itre']['cell_0']
    
    dt = 1e-5
    time_json = np.arange(len(voltage_json)) * dt
    
    fig, axes = plt.subplots(3, 2, figsize=(15, 15))
    axes[0, 0].plot(time_dat, voltage_dat, 'b-', label='nml Voltage', linewidth=2)
    axes[0, 0].plot(time_json, voltage_json, 'r--', label='netpyne Voltage', linewidth=1.5)
    axes[0, 0].set_xlabel('Time (s)', fontsize=10)
    axes[0, 0].set_ylabel('Voltage (mV)', fontsize=10)
    axes[0, 0].set_title('Voltage Comparison', fontsize=12)
    axes[0, 0].legend(fontsize=8)
    axes[0, 0].grid(True, linestyle='--', alpha=0.7)
    axes[0, 1].plot(time_h_itre_dat, h_itre_dat, 'b-', label='nml h_itre', linewidth=2)
    axes[0, 1].plot(time_json, h_itre_json, 'r--', label='netpyne h_itre', linewidth=1.5)
    axes[0, 1].set_xlabel('Time (s)', fontsize=10)
    axes[0, 1].set_ylabel('h_itre', fontsize=10)
    axes[0, 1].set_title('h_itre Comparison', fontsize=12)
    axes[0, 1].legend(fontsize=8)
    axes[0, 1].grid(True, linestyle='--', alpha=0.7)
    axes[1, 0].plot(time_m_itre_dat, m_itre_dat, 'b-', label='nml m_itre', linewidth=2)
    axes[1, 0].plot(time_json, m_itre_json, 'r--', label='netpyne m_itre', linewidth=1.5)
    axes[1, 0].set_xlabel('Time (s)', fontsize=10)
    axes[1, 0].set_ylabel('m_itre', fontsize=10)
    axes[1, 0].set_title('m_itre Comparison', fontsize=12)
    axes[1, 0].legend(fontsize=8)
    axes[1, 0].grid(True, linestyle='--', alpha=0.7)
    axes[1, 1].plot(time_ica_itre_dat, ica_itre_dat, 'b-', label='nml ica_itre', linewidth=2)
    axes[1, 1].plot(time_json, ica_itre_json, 'r--', label='netpyne ica_itre', linewidth=1.5)
    axes[1, 1].set_xlabel('Time (s)', fontsize=10)
    axes[1, 1].set_ylabel('ica_itre', fontsize=10)
    axes[1, 1].set_title('ica_itre Comparison', fontsize=12)
    axes[1, 1].legend(fontsize=8)
    axes[1, 1].grid(True, linestyle='--', alpha=0.7)
    axes[2, 0].plot(time_caConc_dat, caConc_dat, 'b-', label='nml caConc', linewidth=2)
    axes[2, 0].plot(time_json, caConc_json, 'r--', label='netpyne caConc', linewidth=1.5)
    axes[2, 0].set_xlabel('Time (s)', fontsize=10)
    axes[2, 0].set_ylabel('caConc', fontsize=10)
    axes[2, 0].set_title('caConc Comparison', fontsize=12)
    axes[2, 0].legend(fontsize=8)
    axes[2, 0].grid(True, linestyle='--', alpha=0.7)
    axes[2, 1].axis('off')
    plt.tight_layout()
    current_dir = os.getcwd()
    save_path = os.path.join(current_dir, "compare_all.png")
    plt.savefig(save_path, dpi=300, bbox_inches='tight')
    plt.show()
if __name__ == "__main__":
    compare_all()
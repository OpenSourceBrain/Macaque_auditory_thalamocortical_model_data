import numpy as np
import matplotlib.pyplot as plt
import json
import os

def compare_all():
    dat_file = "RE_reduced_cell_step_test.RE_reduced_cell_pop.v.dat"
    json_file = "RE_reduced_hh2_data.json"
    ina_hh2_dat_file = "hh2_na_iDensity.dat"
    ik_hh2_dat_file = "hh2_k_iDensity.dat"
    m_hh2_na_dat_file = "m_hh2_na_state.dat"
    h_hh2_na_dat_file = "h_hh2_na_state.dat"
    n_hh2_k_dat_file = "n_hh2_k_state.dat"
    
    dat_data = np.loadtxt(dat_file)
    time_dat = dat_data[:, 0] 
    voltage_dat = dat_data[:, 1] * 1000  

    ina_hh2_dat_data = np.loadtxt(ina_hh2_dat_file)
    time_ina_hh2_dat = ina_hh2_dat_data[:, 0]
    ina_hh2_dat = ina_hh2_dat_data[:, 1] * -0.1

    ik_hh2_dat_data = np.loadtxt(ik_hh2_dat_file)
    time_ik_hh2_dat = ik_hh2_dat_data[:, 0]
    ik_hh2_dat = ik_hh2_dat_data[:, 1] * -0.1

    m_hh2_na_dat_data = np.loadtxt(m_hh2_na_dat_file)
    time_m_hh2_na_dat = m_hh2_na_dat_data[:, 0]
    m_hh2_na_dat = m_hh2_na_dat_data[:, 1]

    h_hh2_na_dat_data = np.loadtxt(h_hh2_na_dat_file)
    time_h_hh2_na_dat = h_hh2_na_dat_data[:, 0]
    h_hh2_na_dat = h_hh2_na_dat_data[:, 1]

    n_hh2_k_dat_data = np.loadtxt(n_hh2_k_dat_file)
    time_n_hh2_k_dat = n_hh2_k_dat_data[:, 0]
    n_hh2_k_dat = n_hh2_k_dat_data[:, 1]
    
    with open(json_file, 'r') as f:
        json_data = json.load(f)
    voltage_json = json_data['simData']['V_soma']['cell_0']
    ina_hh2_json = json_data['simData']['ina']['cell_0']
    ik_hh2_json = json_data['simData']['ik']['cell_0']
    m_hh2_na_json = json_data['simData']['m_hh2_na']['cell_0']
    h_hh2_na_json = json_data['simData']['h_hh2_na']['cell_0']
    n_hh2_k_json = json_data['simData']['n_hh2_k']['cell_0']
    
    dt = 1e-6
    time_json = np.arange(len(voltage_json)) * dt
    
    fig, axes = plt.subplots(2, 3, figsize=(15, 10))
    
    axes[0, 0].plot(time_dat, voltage_dat, 'b-', label='nml Voltage', linewidth=2)
    axes[0, 0].plot(time_json, voltage_json, 'r--', label='netpyne Voltage', linewidth=1.5)
    axes[0, 0].set_xlabel('Time (s)')
    axes[0, 0].set_ylabel('Voltage (mV)')
    axes[0, 0].set_title('Voltage Comparison')
    axes[0, 0].legend()
    axes[0, 0].grid(True, linestyle='--', alpha=0.7)

    axes[0, 1].plot(time_ina_hh2_dat, ina_hh2_dat, 'b-', label='nml ina_hh2', linewidth=2)
    axes[0, 1].plot(time_json, ina_hh2_json, 'r--', label='netpyne ina_hh2', linewidth=1.5)
    axes[0, 1].set_xlabel('Time (s)')
    axes[0, 1].set_ylabel('ina_hh2')
    axes[0, 1].set_title('ina_hh2 Comparison')
    axes[0, 1].legend()
    axes[0, 1].grid(True, linestyle='--', alpha=0.7)

    axes[0, 2].plot(time_ik_hh2_dat, ik_hh2_dat, 'b-', label='nml ik_hh2', linewidth=2)
    axes[0, 2].plot(time_json, ik_hh2_json, 'r--', label='netpyne ik_hh2', linewidth=1.5)
    axes[0, 2].set_xlabel('Time (s)')
    axes[0, 2].set_ylabel('ik_hh2')
    axes[0, 2].set_title('ik_hh2 Comparison')
    axes[0, 2].legend()
    axes[0, 2].grid(True, linestyle='--', alpha=0.7)

    axes[1, 0].plot(time_m_hh2_na_dat, m_hh2_na_dat, 'b-', label='nml m_hh2_na', linewidth=2)
    axes[1, 0].plot(time_json, m_hh2_na_json, 'r--', label='netpyne m_hh2_na', linewidth=1.5)
    axes[1, 0].set_xlabel('Time (s)')
    axes[1, 0].set_ylabel('m_hh2_na')
    axes[1, 0].set_title('m_hh2_na Comparison')
    axes[1, 0].legend()
    axes[1, 0].grid(True, linestyle='--', alpha=0.7)

    axes[1, 1].plot(time_h_hh2_na_dat, h_hh2_na_dat, 'b-', label='nml h_hh2_na', linewidth=2)
    axes[1, 1].plot(time_json, h_hh2_na_json, 'r--', label='netpyne h_hh2_na', linewidth=1.5)
    axes[1, 1].set_xlabel('Time (s)')
    axes[1, 1].set_ylabel('h_hh2_na')
    axes[1, 1].set_title('h_hh2_na Comparison')
    axes[1, 1].legend()
    axes[1, 1].grid(True, linestyle='--', alpha=0.7)

    axes[1, 2].plot(time_n_hh2_k_dat, n_hh2_k_dat, 'b-', label='nml n_hh2_k', linewidth=2)
    axes[1, 2].plot(time_json, n_hh2_k_json, 'r--', label='netpyne n_hh2_k', linewidth=1.5)
    axes[1, 2].set_xlabel('Time (s)')
    axes[1, 2].set_ylabel('n_hh2_k')
    axes[1, 2].set_title('n_hh2_k Comparison')
    axes[1, 2].legend()
    axes[1, 2].grid(True, linestyle='--', alpha=0.7)

    plt.tight_layout()
    current_dir = os.getcwd()
    save_path = os.path.join(current_dir, "compare_hh2.png")
    plt.savefig(save_path, dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == "__main__":
    compare_all()
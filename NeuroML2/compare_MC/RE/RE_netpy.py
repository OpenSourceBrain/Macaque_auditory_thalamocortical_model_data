import os
# Force headless plotting for Matplotlib
os.environ["MPLBACKEND"] = "Agg"
import matplotlib
matplotlib.use("Agg")
# Ensure NEURON runs headless in non-GUI environments
os.environ["NEURON_NO_GUI"] = "1"
os.environ.pop("DISPLAY", None)
print(f"[RE_netpy] Headless env: DISPLAY={os.environ.get('DISPLAY')}, NEURON_NO_GUI={os.environ.get('NEURON_NO_GUI')}, MPLBACKEND={os.environ.get('MPLBACKEND')}")
from netpyne import specs, sim
import pprint

netParams = specs.NetParams() 
## RE cell properties
soma = {'geom': {}, 'ions': {}, 'mechs': {}, 'vinit': -70, 'threshold': 5.0} 
soma['geom'] = {'diam': 70, 'L': 64.86, 'Ra': 100, 'cm': 1, 'nseg': 1, 'pt3d': []}
soma['geom']['pt3d'].append((0, 0, 0, 70))
soma['geom']['pt3d'].append((0, 64.86, 0, 70))
soma['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
soma['ions']['k'] = {'e': -95.0, 'i': 54.4, 'o': 2.5}
soma['ions']['na'] = {'e': 50.0, 'i': 10.0, 'o': 140.0}
soma['mechs']['pas'] = {'g': 5e-5, 'e': -77}
soma['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 1, 'kd': 0.0, 'kt': 0.0, 'taur': 5}
soma['mechs']['kl'] = {'gmax': 3e-06}
soma['mechs']['itre'] = {"gmax": 0.002,"shift": 2.0}
soma['mechs']['hh2ad'] = {"gkbar": 0.01,"gnabar": 0.09,"vtraub": -50.0}


RE_HH_reduced_dict = {'secs': {'soma': soma}}
netParams.cellParams['RE_HH_reduced'] = RE_HH_reduced_dict  # add rule dict to list of cell property rules
netParams.cellParams['RE_HH_reduced']['globals'] = {'celsius': 34.0}

pprint.pprint(netParams.cellParams['RE_HH_reduced'])

netParams.popParams['RE'] = {'cellType': 'RE_HH_reduced', 'numCells': 1}

netParams.stimSourceParams['Input'] = {'type': 'IClamp', 'dur': 500, 'del': 200, 'amp': 0.03}
netParams.stimTargetParams['Input->RE'] = {'source': 'Input', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'RE_HH_reduced'}}
netParams.defaultThreshold = 5.0
# Simulation options
simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

simConfig.recordCells = ['all']
simConfig.hParams['celsius'] = 34
simConfig.duration = 1000         # Duration of the simulation, in ms
simConfig.dt = 0.025       
          # Internal integration timestep to use
simConfig.verbose = True           # Show detailed messages


simConfig.recordTraces = {
                          # Membrane
                          'V_soma':{'sec':'soma','loc':0.5,'var':'v'},
                          'cai':{'sec':'soma','loc':0.5,'var':'cai'},
                          # HH Na/K (Traub hh2ad)
                          'm_hh2_na':{'sec': 'soma', 'loc': 0.5, 'mech': 'hh2ad', 'var': 'm'},
                          'h_hh2_na':{'sec': 'soma', 'loc': 0.5, 'mech': 'hh2ad', 'var': 'h'},
                          'n_hh2_k':{'sec': 'soma', 'loc': 0.5, 'mech': 'hh2ad', 'var': 'n'},
                          # T type Ca channel (itre) from IT2.mod: states m,h; mechanism current 'i'
                          'm_itre':{'sec': 'soma', 'loc': 0.5, 'mech': 'itre', 'var': 'm'},
                          'h_itre':{'sec': 'soma', 'loc': 0.5, 'mech': 'itre', 'var': 'h'},
                          'i_itre':{'sec': 'soma', 'loc': 0.5, 'mech': 'itre', 'var': 'i'},
                          # Passive leak K channel current uses variable 'i' in kl.mod
                          'i_kl':{'sec': 'soma', 'loc': 0.5, 'mech': 'kl', 'var': 'i'},
                          # Total ionic currents for reference
                          'ina':{'sec': 'soma', 'loc': 0.5, 'var': 'ina'},
                          'ik':{'sec': 'soma', 'loc': 0.5, 'var': 'ik'},
                          'ica':{'sec': 'soma', 'loc': 0.5, 'var': 'ica'}
                         }  # Dict with traces to record


simConfig.recordStep = 0.025            # Match integration step for high‑res alignment
simConfig.filename = 'RE_full_data'         # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file
simConfig.saveDataInclude = ['simData']
# 以 NetPyNE 默认方式保存 JSON（兼容不同版本）
simConfig.saveJson = True
# Disable built-in plotting during headless runs to avoid DISPLAY issues
simConfig.analysis = {}

# Create network and run simulation
sim.createSimulateAnalyze(netParams = netParams, simConfig = simConfig)

#import pylab; pylab.show()  # this line is only necessary in certain systems where figures appear empty

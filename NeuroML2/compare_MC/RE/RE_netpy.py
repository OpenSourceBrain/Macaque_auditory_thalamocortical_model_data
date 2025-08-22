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
# soma['mechs']['kl'] = {'gmax': 3e-06}
soma['mechs']['itre'] = {"gmax": 0.002,"shift": 2.0}
# soma['mechs']['hh2ad'] = {"gkbar": 0.01,"gnabar": 0.09,"vtraub": -50.0}


RE_HH_reduced_dict = {'secs': {'soma': soma}}
netParams.cellParams['RE_HH_reduced'] = RE_HH_reduced_dict  # add rule dict to list of cell property rules
netParams.cellParams['RE_HH_reduced']['globals'] = {'celsius': 34.0}

pprint.pprint(netParams.cellParams['RE_HH_reduced'])

netParams.popParams['RE'] = {'cellType': 'RE_HH_reduced', 'numCells': 1}

netParams.stimSourceParams['Input'] = {'type': 'IClamp', 'dur': 400, 'del': 500, 'amp': 0.02}
netParams.stimTargetParams['Input->RE'] = {'source': 'Input', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'RE_HH_reduced'}}
netParams.defaultThreshold = 5.0
# Simulation options
simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

simConfig.recordCells = ['all']
simConfig.hParams['celsius'] = 34
simConfig.duration = 2000           # Duration of the simulation, in ms
simConfig.dt = 0.01       
          # Internal integration timestep to use
simConfig.verbose = True           # Show detailed messages


simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}, 
                          'm_itre':{'sec': 'soma', 'loc': 0.5, 'mech': 'itre', 'var': 'm'},
                          'h_itre':{'sec': 'soma', 'loc': 0.5, 'mech': 'itre', 'var': 'h'},
                          'ica_itre':{'sec': 'soma', 'loc': 0.5, 'var': 'ica'},
                          'carev_itre':{'sec': 'soma', 'loc': 0.5, 'mech': 'itre', 'var': 'carev'},
                          'caConc_itre':{'sec': 'soma', 'loc': 0.5, 'var': 'cai'}}  # Dict with traces to record


simConfig.recordStep = 0.01            # Step size in ms to save data (eg. V traces, LFP, etc)
simConfig.filename = 'RE_reduced_itre'         # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file
simConfig.saveDataInclude = ['simData']
simConfig.saveJson = True 
simConfig.analysis['plotTraces'] = {'include': [0], 'saveFig': True}  # Plot recorded traces for this list of cells
simConfig.analysis['plotRaster'] = {'saveFig': True}                  # Plot a raster

# Create network and run simulation
sim.createSimulateAnalyze(netParams = netParams, simConfig = simConfig)

#import pylab; pylab.show()  # this line is only necessary in certain systems where figures appear empty
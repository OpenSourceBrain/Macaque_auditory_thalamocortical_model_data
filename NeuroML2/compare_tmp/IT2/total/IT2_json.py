from netpyne import specs, sim
import pprint

netParams = specs.NetParams()
simConfig = specs.SimConfig()


netParams.loadCellParamsRule(label='IT2_HH_reduced', fileName='IT2_reduced_cellParams.json')
pprint.pprint(netParams.cellParams['IT2_HH_reduced'])


netParams.popParams['IT2'] = {'cellType': 'IT2_HH_reduced', 'numCells': 1}

netParams.stimSourceParams['Input'] = {'type': 'IClamp', 'dur': 1500, 'del': 200, 'amp': 0.3}
netParams.stimTargetParams['Input->IT2'] = {'source': 'Input', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'IT2_HH_reduced'}}

# Simulation options
simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

simConfig.recordCells = ['all']

simConfig.duration = 2000           # Duration of the simulation, in ms
simConfig.dt = 0.01                 # Internal integration timestep to use
simConfig.verbose = False           # Show detailed messages
simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}}  # Dict with traces to record
simConfig.recordStep = 1            # Step size in ms to save data (eg. V traces, LFP, etc)
simConfig.filename = 'IT2_reduced_json'         # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file
simConfig.saveDataInclude = ['simData']  
simConfig.saveJson = True 
simConfig.analysis['plotTraces'] = {'include': [0], 'saveFig': True}  # Plot recorded traces for this list of cells
simConfig.analysis['plotRaster'] = {'saveFig': True}                  # Plot a raster

# Create network and run simulation
sim.createSimulateAnalyze(netParams = netParams, simConfig = simConfig)

#import pylab; pylab.show()  # this line is only necessary in certain systems where figures appear empty
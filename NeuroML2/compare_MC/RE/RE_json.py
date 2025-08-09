from netpyne import specs, sim
import pprint

netParams = specs.NetParams()
simConfig = specs.SimConfig()


netParams.loadCellParamsRule(label='RE_HH_reduced', fileName='RE_reduced_cellParams.json')
pprint.pprint(netParams.cellParams['RE_HH_reduced'])


netParams.popParams['RE'] = {'cellType': 'RE_HH_reduced', 'numCells': 1}

netParams.stimSourceParams['Input'] = {'type': 'IClamp', 'dur': 1600, 'del': 200, 'amp': 0.001}
netParams.stimTargetParams['Input->RE'] = {'source': 'Input', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'RE_HH_reduced'}}

# Simulation options
simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

simConfig.recordCells = ['all']
simConfig.hParams['celsius'] = 34
simConfig.duration = 2000           # Duration of the simulation, in ms
simConfig.dt = 0.01                 # Internal integration timestep to use
simConfig.verbose = False           # Show detailed messages
simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}}  # Dict with traces to record
simConfig.recordStep = 0.01            # Step size in ms to save data (eg. V traces, LFP, etc)
simConfig.filename = 'RE_reduced_json'         # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file
simConfig.saveDataInclude = ['simData']  
simConfig.saveJson = True 
simConfig.analysis['plotTraces'] = {'include': [0], 'saveFig': True}  # Plot recorded traces for this list of cells
simConfig.analysis['plotRaster'] = {'saveFig': True}                  # Plot a raster

# Create network and run simulation
sim.createSimulateAnalyze(netParams = netParams, simConfig = simConfig)

#import pylab; pylab.show()  # this line is only necessary in certain systems where figures appear empty
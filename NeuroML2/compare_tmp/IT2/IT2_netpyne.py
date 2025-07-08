from netpyne import specs, sim
import pprint

netParams = specs.NetParams() 
## IT2 cell properties
soma = {'geom': {}, 'ions': {}, 'mechs': {}, 'vinit': -85.7}  # soma properties
soma['geom'] = {'diam': 28.2149102762, 'L': 48.4123467666, 'Ra': 70.0015514222, 'cm': 2.4998269977, 'nseg': 1, 'pt3d': []}
soma['geom']['pt3d'].append((0, 0, 0, 28.2149102762))
soma['geom']['pt3d'].append((0, 48.4123467666, 0, 28.2149102762))
soma['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
soma['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
soma['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
soma['mechs']['pas'] = {'g': 0.0001, 'e': -86}
soma['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05}
soma['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
soma['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}


Adend1 = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
Adend1['geom'] = {'diam': 1.5831889597, 'L': 10.529217744466665, 'Ra': 70.0015514222, 'cm': 2.74242941886, 'nseg': 1, 'pt3d': []}
Adend1['geom']['pt3d'].append((0, 48.4123467666, 0, 1.5831889597))
Adend1['geom']['pt3d'].append((0, 58.941564511066666, 0, 1.5831889597))
Adend1['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Adend1['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Adend1['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Adend1['mechs']['pas'] = {'g': 7.199592136286027e-05, 'e': -87.1335623948}
Adend1['topol'] = {'parentSec': 'soma', 'parentX': 1.0, 'childX': 0}
Adend1['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05}
Adend1['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
Adend1['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}


Adend2 = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7} 
Adend2['geom'] = {'diam': 1.5831889597, 'L': 10.529217744466665, 'Ra': 70.0015514222, 'cm': 2.74242941886, 'nseg': 1, 'pt3d': []}
Adend2['geom']['pt3d'].append((0, 58.941564511066666, 0, 1.5831889597))
Adend2['geom']['pt3d'].append((0, 69.47078225553334, 0, 1.5831889597))
Adend2['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Adend2['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Adend2['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Adend2['mechs']['pas'] = {'g': 7.199592136286027e-05, 'e': -87.1335623948}
Adend2['topol'] = {'parentSec': 'soma', 'parentX': 1.0, 'childX': 0}
Adend2['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05}
Adend2['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
Adend2['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}



Adend3 = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
Adend3['geom'] = {'diam': 1.5831889597, 'L': 10.529217744466665, 'Ra': 70.0015514222, 'cm': 2.74242941886, 'nseg': 1, 'pt3d': []}
Adend3['geom']['pt3d'].append((0, 69.47078225553334, 0, 1.5831889597))
Adend3['geom']['pt3d'].append((0, 80.0, 0, 1.5831889597))
Adend3['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Adend3['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Adend3['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Adend3['mechs']['pas'] = {'g': 7.199592136286027e-05, 'e': -87.1335623948}
Adend3['topol'] = {'parentSec': 'soma', 'parentX': 1.0, 'childX': 0}
Adend3['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05}
Adend3['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
Adend3['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}


Bdend = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
Bdend['geom'] = {'diam': 2.2799248874, 'L': 96.75, 'Ra': 70.0015514222, 'cm': 2.74086279376, 'nseg': 1, 'pt3d': []}
Bdend['geom']['pt3d'].append((0, 48.4123467666, 0, 2.2799248874))
Bdend['geom']['pt3d'].append((68.40225, -116.8145967666, 0, 2.2799248874))
Bdend['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Bdend['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Bdend['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Bdend['mechs']['pas'] = {'g': 0.00014147647761414165, 'e': -87.1335623948}
Bdend['topol'] = {'parentSec': 'soma', 'parentX': 0.5, 'childX': 0}
Bdend['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05}
Bdend['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
Bdend['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}


axon = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
axon['geom'] = {'diam': 1.40966286462, 'L': 594.292937602, 'Ra': 70.0015514222, 'cm': 2.4630760526, 'nseg': 1, 'pt3d': []}
axon['geom']['pt3d'].append((0, 0, 0, 1.40966286462))
axon['geom']['pt3d'].append((0, -594.292937602, 0, 1.40966286462))
axon['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
axon['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
axon['mechs']['pas'] = {'g': 0.00035435694659685776, 'e': -87.1335623948}
axon['topol'] = {'parentSec': 'soma', 'parentX': 0, 'childX': 0}



IT2_HH_reduced_dict = {'secs': {'soma': soma, 'Adend1': Adend1, 'Adend2': Adend2, 'Adend3': Adend3, 'Bdend': Bdend, 'axon': axon}}
netParams.cellParams['IT2_HH_reduced'] = IT2_HH_reduced_dict  # add rule dict to list of cell property rules
netParams.cellParams['IT2_HH_reduced']['global'] = {'celsius': 34.0, 'erev_ih': -37.0}

pprint.pprint(netParams.cellParams['IT2_HH_reduced'])

netParams.popParams['IT2'] = {'cellType': 'IT2_HH_reduced', 'numCells': 1}

netParams.stimSourceParams['Input1'] = {'type': 'IClamp', 'dur': 200, 'del': 100, 'amp': 0.3}
netParams.stimTargetParams['Input1->IT2'] = {'source': 'Input1', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'IT2_HH_reduced'}}

netParams.stimSourceParams['Input2'] = {'type': 'IClamp', 'dur': 200, 'del': 500, 'amp': 0.3}
netParams.stimTargetParams['Input2->IT2'] = {'source': 'Input2', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'IT2_HH_reduced'}}

netParams.stimSourceParams['Input3'] = {'type': 'IClamp', 'dur': 200, 'del': 900, 'amp': 0.3}
netParams.stimTargetParams['Input3->IT2'] = {'source': 'Input3', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'IT2_HH_reduced'}}

netParams.stimSourceParams['Input4'] = {'type': 'IClamp', 'dur': 200, 'del': 1300, 'amp': 0.3}
netParams.stimTargetParams['Input4->IT2'] = {'source': 'Input4', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'IT2_HH_reduced'}}

# Simulation options
simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

simConfig.recordCells = ['all']

simConfig.duration = 2000           # Duration of the simulation, in ms
simConfig.dt = 0.025                # Internal integration timestep to use
simConfig.hParams['celsius'] = 34
simConfig.verbose = False           # Show detailed messages
simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}}  # Dict with traces to record
simConfig.recordStep = 1            # Step size in ms to save data (eg. V traces, LFP, etc)
simConfig.filename = 'IT2_reduced'         # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file
simConfig.saveDataInclude = ['simData']  
simConfig.saveJson = True 
simConfig.analysis['plotTraces'] = {'include': [0], 'saveFig': True}  # Plot recorded traces for this list of cells


# Create network and run simulation
sim.createSimulateAnalyze(netParams = netParams, simConfig = simConfig)

#import pylab; pylab.show()  # this line is only necessary in certain systems where figures appear empty
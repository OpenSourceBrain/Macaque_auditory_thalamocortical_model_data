from netpyne import specs, sim
import pprint

netParams = specs.NetParams() 
## IT2 cell properties
soma = {'geom': {}, 'ions': {}, 'mechs': {}, 'vinit': -85.7, 'threshold': 5.0}  # soma properties
soma['geom'] = {'diam': 28.2149102762, 'L': 48.4123467666, 'Ra': 70.0015514222, 'cm': 2.4998269977, 'nseg': 1, 'pt3d': []}
soma['geom']['pt3d'].append((0, 0, 0, 28.2149102762))
soma['geom']['pt3d'].append((0, 48.4123467666, 0, 28.2149102762))
soma['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
soma['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
soma['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
soma['mechs']['pas'] = {'g': 0.0001, 'e': -86}
# soma['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05, 'e': -37.0}
soma['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
# soma['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}
# soma['mechs']['can'] = {'gcanbar': 8.13137955053e-07}
# soma['mechs']['cat'] = {'gcatbar': 9.29455717585e-07}
soma['mechs']['kap'] = {'gbar': 0.0240195239098, 'sh': 0.0, 'tq': -49.7149526489, 'vhalfl': -36.7754836348, 'vhalfn': 32.179925527}




Adend1 = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
Adend1['geom'] = {'diam': 1.5831889597, 'L': 10.529217744466665, 'Ra': 70.0015514222, 'cm': 2.74242941886, 'nseg': 1, 'pt3d': []}
Adend1['geom']['pt3d'].append((0, 48.4123467666, 0, 1.5831889597))
Adend1['geom']['pt3d'].append((0, 58.941564511066666, 0, 1.5831889597))
Adend1['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Adend1['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Adend1['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Adend1['mechs']['pas'] = {'g': 7.199592136286027e-05, 'e': -87.1335623948}
Adend1['topol'] = {'parentSec': 'soma', 'parentX': 1.0, 'childX': 0}
# Adend1['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05, 'e': -37.0}
Adend1['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
# Adend1['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}
# Adend1['mechs']['can'] = {'gcanbar': 8.13137955053e-07}
# Adend1['mechs']['cat'] = {'gcatbar': 9.29455717585e-07}
#Adend1['mechs']['kap'] = {'gbar': 0.0240195239098, 'sh': 0.0, 'tq': -49.7149526489, 'vhalfl': -36.7754836348, 'vhalfn': 32.179925527}





Adend2 = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7} 
Adend2['geom'] = {'diam': 1.5831889597, 'L': 10.529217744466665, 'Ra': 70.0015514222, 'cm': 2.74242941886, 'nseg': 1, 'pt3d': []}
Adend2['geom']['pt3d'].append((0, 58.941564511066666, 0, 1.5831889597))
Adend2['geom']['pt3d'].append((0, 69.47078225553334, 0, 1.5831889597))
Adend2['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Adend2['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Adend2['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Adend2['mechs']['pas'] = {'g': 7.199592136286027e-05, 'e': -87.1335623948}
Adend2['topol'] = {'parentSec': 'Adend1', 'parentX': 1.0, 'childX': 0}
# Adend2['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05, 'e': -37.0}
Adend2['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
# Adend2['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}
# Adend2['mechs']['can'] = {'gcanbar': 8.13137955053e-07}
# Adend2['mechs']['cat'] = {'gcatbar': 9.29455717585e-07}
#Adend2['mechs']['kap'] = {'gbar': 0.0240195239098, 'sh': 0.0, 'tq': -49.7149526489, 'vhalfl': -36.7754836348, 'vhalfn': 32.179925527}







Adend3 = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
Adend3['geom'] = {'diam': 1.5831889597, 'L': 10.529217744466665, 'Ra': 70.0015514222, 'cm': 2.74242941886, 'nseg': 1, 'pt3d': []}
Adend3['geom']['pt3d'].append((0, 69.47078225553334, 0, 1.5831889597))
Adend3['geom']['pt3d'].append((0, 80.0, 0, 1.5831889597))
Adend3['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Adend3['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Adend3['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Adend3['mechs']['pas'] = {'g': 7.199592136286027e-05, 'e': -87.1335623948}
Adend3['topol'] = {'parentSec': 'Adend2', 'parentX': 1.0, 'childX': 0}
# Adend3['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05, 'e': -37.0}
Adend3['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
# Adend3['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}
# Adend3['mechs']['can'] = {'gcanbar': 8.13137955053e-07}
# Adend3['mechs']['cat'] = {'gcatbar': 9.29455717585e-07}
#Adend3['mechs']['kap'] = {'gbar': 0.0240195239098, 'sh': 0.0, 'tq': -49.7149526489, 'vhalfl': -36.7754836348, 'vhalfn': 32.179925527}




Bdend = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
Bdend['geom'] = {'diam': 2.2799248874, 'L': 96.75, 'Ra': 70.0015514222, 'cm': 2.74086279376, 'nseg': 1, 'pt3d': []}
Bdend['geom']['pt3d'].append((0, 48.4123467666, 0, 2.2799248874))
Bdend['geom']['pt3d'].append((68.40225, -116.8145967666, 0, 2.2799248874))
Bdend['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
Bdend['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
Bdend['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
Bdend['mechs']['pas'] = {'g': 0.00014147647761414165, 'e': -87.1335623948}
Bdend['topol'] = {'parentSec': 'soma', 'parentX': 0.5, 'childX': 0}
# Bdend['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05, 'e': -37.0}
Bdend['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
# Bdend['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}
# Bdend['mechs']['can'] = {'gcanbar': 8.13137955053e-07}
# Bdend['mechs']['cat'] = {'gcatbar': 9.29455717585e-07}
#Bdend['mechs']['kap'] = {'gbar': 0.0240195239098, 'sh': 0.0, 'tq': -49.7149526489, 'vhalfl': -36.7754836348, 'vhalfn': 32.179925527}




axon = {'geom': {},'ions': {}, 'topol': {}, 'mechs': {}, 'vinit': -85.7}  
axon['geom'] = {'diam': 1.40966286462, 'L': 594.292937602, 'Ra': 70.0015514222, 'cm': 2.4630760526, 'nseg': 1, 'pt3d': []}
axon['geom']['pt3d'].append((0, 0, 0, 1.40966286462))
axon['geom']['pt3d'].append((0, -594.292937602, 0, 1.40966286462))
axon['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
axon['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}
axon['mechs']['pas'] = {'g': 0.00035435694659685776, 'e': -87.1335623948}
axon['topol'] = {'parentSec': 'soma', 'parentX': 0, 'childX': 0}
#axon['mechs']['kap'] = {'gbar': 0.120097619549, 'sh': 0.0, 'tq': -49.7149526489, 'vhalfl': -36.7754836348, 'vhalfn': 32.179925527}


IT2_HH_reduced_dict = {'secs': {'soma': soma, 'Adend1': Adend1, 'Adend2': Adend2, 'Adend3': Adend3, 'Bdend': Bdend, 'axon': axon}}
netParams.cellParams['IT2_HH_reduced'] = IT2_HH_reduced_dict  # add rule dict to list of cell property rules
netParams.cellParams['IT2_HH_reduced']['global'] = {'celsius': 34.0, 'erev_ih': -37.0}

pprint.pprint(netParams.cellParams['IT2_HH_reduced'])

netParams.popParams['IT2'] = {'cellType': 'IT2_HH_reduced', 'numCells': 1}

netParams.stimSourceParams['Input1'] = {'type': 'IClamp', 'dur': 1000, 'del': 200, 'amp': 0.3}
netParams.stimTargetParams['Input1->IT2'] = {'source': 'Input1', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'IT2_HH_reduced'}}



# Simulation options
simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

simConfig.recordCells = ['all']

simConfig.duration = 1500         # Duration of the simulation, in ms
simConfig.dt = 0.01                # Internal integration timestep to use
simConfig.hParams['celsius'] = 34
simConfig.verbose = False           # Show detailed messages
simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}}  # Dict with traces to record
simConfig.recordStep = 0.01            # Step size in ms to save data (eg. V traces, LFP, etc)
simConfig.filename = 'IT2_reduced_pas'         # Set file output name
simConfig.savePickle = False        # Save params, network and sim output to pickle file
simConfig.saveDataInclude = ['simData']  
simConfig.saveJson = True 
simConfig.analysis['plotTraces'] = {'include': [0], 'saveFig': True}  # Plot recorded traces for this list of cells
simConfig.analysis['plotRaster'] = {'saveFig': True}                  # Plot a raster


# Create network and run simulation
sim.createSimulateAnalyze(netParams = netParams, simConfig = simConfig)

#import pylab; pylab.show()  # this line is only necessary in certain systems where figures appear empty
#!/usr/bin/env python3
"""
Compare NML and NetPyNE cell behaviour

File: compare_channels.py

Copyright 2025 Ankur Sinha
Author: Ankur Sinha <sanjay DOT ankur AT gmail DOT com>
"""

from netpyne import specs, sim
import pprint


def netpyne_run(ion = None, mech = None):
    """Create and run netpyne simulation """
    netParams = specs.NetParams()
    ## IT2 cell properties
    soma = {'geom': {}, 'ions': {}, 'mechs': {}, 'vinit': -85.7, 'threshold': 5.0}
    soma['geom'] = {'diam': 28.2149102762, 'L': 48.4123467666, 'Ra': 70.0015514222, 'cm': 2.4998269977, 'nseg': 1, 'pt3d': []}
    soma['geom']['pt3d'].append((0, 0, 0, 28.2149102762))
    soma['geom']['pt3d'].append((0, 48.4123467666, 0, 28.2149102762))
    soma['mechs']['pas'] = {'g': 0.0001, 'e': -86}

    if ion:
        soma['ions'].update(ion)
    if mech:
        soma['mechs'].update(mech)
        mech_used = list(mech.keys())[0]
    else:
        mech_used = "pas"

    IT2_HH_reduced_dict = {'secs': {'soma': soma }}
    netParams.cellParams['IT2_HH_reduced'] = IT2_HH_reduced_dict  # add rule dict to list of cell property rules
    netParams.cellParams['IT2_HH_reduced']['globals'] = {'celsius': 34.0, 'erev_ih': -37.0}

    pprint.pprint(netParams.cellParams['IT2_HH_reduced'])

    netParams.popParams['IT2'] = {'cellType': 'IT2_HH_reduced', 'numCells': 1}

    netParams.stimSourceParams['Input'] = {'type': 'IClamp', 'dur': 1000, 'del': 200, 'amp': 0.5}
    netParams.stimTargetParams['Input->IT2'] = {'source': 'Input', 'sec': 'soma', 'loc': 0.5, 'conds': {'cellType': 'IT2_HH_reduced'}}
    netParams.defaultThreshold = 5.0
    # Simulation options
    simConfig = specs.SimConfig()       # object of class SimConfig to store simulation configuration

    simConfig.recordCells = ['all']
    simConfig.hParams['celsius'] = 34
    simConfig.duration = 2000           # Duration of the simulation, in ms
    simConfig.dt = 0.01
              # Internal integration timestep to use
    simConfig.verbose = False           # Show detailed messages
    simConfig.recordTraces = {'V_soma':{'sec':'soma','loc':0.5,'var':'v'}}  # Dict with traces to record
    simConfig.recordStep = 0.01            # Step size in ms to save data (eg. V traces, LFP, etc)
    simConfig.filename = 'IT2_reduced_all'         # Set file output name
    simConfig.savePickle = False        # Save params, network and sim output to pickle file
    simConfig.saveDataInclude = ['simData']
    simConfig.saveJson = True
    simConfig.analysis['plotTraces'] = {'include': [0], 'saveFig': f"netpyne_{mech_used}.png"}  # Plot recorded traces for this list of cells

    # Create network and run simulation
    sim.createSimulateAnalyze(netParams = netParams, simConfig = simConfig)

    #import pylab; pylab.show()  # this line is only necessary in certain systems where figures appear empty


def run_analysis():
    """Run the analyses"""
    netpyne_info = {'ions': {}, 'mechs': {}}
    netpyne_info['ions']['ca'] = {'e': 132.4579341637009, 'i': 5e-05, 'o': 2.0}
    netpyne_info['ions']['k'] = {'e': -104.0, 'i': 54.4, 'o': 2.5}
    netpyne_info['ions']['na'] = {'e': 42.0, 'i': 10.0, 'o': 140.0}

    netpyne_info['mechs']['ih'] = {'ascale': 0.00320887293027, 'ashift': 119.696272155, 'aslope': 7.09800576233, 'bscale': 0.285307415701, 'bslope': 23.2995848558, 'gbar': 3.3176340367e-05,}
    netpyne_info['mechs']['cadad'] = {'cainf': 0.00024, 'depth': 0.119408607923, 'kd': 0.0, 'kt': 0.0, 'taur': 99.1146852282}
    netpyne_info['mechs']['cal'] = {'gcalbar': 2.39132864454e-06}
    netpyne_info['mechs']['can'] = {'gcanbar': 8.13137955053e-07}
    netpyne_info['mechs']['cat'] = {'gcatbar': 9.29455717585e-07}
    netpyne_info['mechs']['kap'] = {'gbar': 0.0240195239098, 'sh': 0.0, 'tq': -49.7149526489, 'vhalfl': -36.7754836348, 'vhalfn': 32.179925527}
    netpyne_info['mechs']['kBK'] = {"caPh": 0.002,"caPk": 1.0,"caPmax": 1.0,"caPmin": 0.0,"caVhh": 0.002,"caVhmax": 155.67,"caVhmin": 43.919142291200004,"gpeak": 4.45651933019e-05,"k": 17.0,"tau": 1.0}
    netpyne_info['mechs']['kdr'] = {"gbar": 0.017,"sh": 0.0,"vhalfn": 8}
    netpyne_info['mechs']['nax'] = {"gbar": 0.043,"sh": 0.0}

    # for passive
    netpyne_run()
    # for each mech
    for k, v in netpyne_info['mechs'].items():
        for i, v1 in netpyne_info['ions'].items():
            if k.startswith(i):
                netpyne_run(ion={i: v1}, mech={k: v})


if __name__ == "__main__":
    run_analysis()

from netpyne import specs, sim
import pprint

netParams = specs.NetParams()
simConfig = specs.SimConfig()


netParams.loadCellParamsRule(label='IT', fileName='../model/cells/IT2_reduced_cellParams.json')

netParams.cellParams['IT']['secs']['soma']['var'] = {'v': -85.7}


pprint.pprint(netParams.cellParams['IT'])


netParams.popParams['IT2'] = {'cellModel': 'HH_reduced', 'cellType': 'IT', 'numCells': 1}

netParams.stimSourceParams['input'] = {'type': 'IClamp', 'dur': 2000, 'del': 300, 'amp': 1000}
netParams.stimTargetParams['input->soma'] = {'source': 'input', 'sec': 'soma', 'loc': 0.5, 'conds': {'pop': 'IT2'}}

simConfig.duration = 3000
simConfig.dt = 0.025
simConfig.recordStep = 0.1
simConfig.filename = 'IT2_sim'


simConfig.recordCells = ['IT2']
simConfig.recordTraces = {
    "V_soma": {
        "sec": "soma",
        "loc": 0.5,
        "var": "v",
    },
}

simConfig.analysis = {
    "plotTraces": {
        "include": ['IT2'],
        "saveFig": True,
    },
}

sim.createSimulateAnalyze(netParams=netParams, simConfig=simConfig)

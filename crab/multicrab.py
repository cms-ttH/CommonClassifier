import argparse
from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import getUsernameFromSiteDB, config

class Sample:
    def __init__(self, *args, **kwargs):
        self.name = kwargs.get("name")
        self.filename = kwargs.get("filename")

def submit(config):
    res = crabCommand('submit', config = config)
    return res

samples = [
    Sample(
        name = "tth",
        filename="samples/eth/tth.txt"
    ),
    Sample(
        name = "ttjets",
        filename="samples/eth/ttjets.txt"
    )
]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Submits crab jobs')
    parser.add_argument('--out', action="store", required=True, help="output site, e.g. T2_CH_CSCS", type=str)
    parser.add_argument('--tag', action="store", required=True, help="unique tag for processing", type=str)
    parser.add_argument('--user', action="store", help="username on grid", type=str, default=getUsernameFromSiteDB())
    args = parser.parse_args()
    
    for sample in samples:
        cfg = config()
        
        cfg.section_("General")
        cfg.General.requestName = 'MEM_{0}_{1}'.format(sample.name, args.tag)
        cfg.General.workArea = 'crab_projects'
        cfg.General.transferLogs = True
        
        cfg.section_("JobType")
        cfg.JobType.pluginName = 'Analysis'
        cfg.JobType.psetName = 'PSet.py'
        cfg.JobType.scriptExe = 'wrapper.sh'
        cfg.JobType.sendPythonFolder = True
        cfg.JobType.maxMemoryMB = 2000
        cfg.JobType.inputFiles = [
            cfg.JobType.scriptExe,
            'mem.py',
            'cc_looper.py'
        ]
        cfg.JobType.maxJobRuntimeMin = 240
        
        cfg.section_("Data")
        cfg.Data.inputDBS = 'global'
        cfg.Data.splitting = 'FileBased'
        cfg.Data.unitsPerJob = 1
        cfg.Data.totalUnits = 10
        cfg.Data.userInputFiles = map(lambda x: x.strip(), open(sample.filename).readlines())
        cfg.Data.allowNonValidInputDataset = True # to run on datasets in PRODUCTION
        cfg.Data.outLFNDirBase = '/store/user/{0}/mem/'.format(args.user)
        cfg.Data.publication = False
        #cfg.Data.outputDatasetTag = 'mem_test_v1'
        #cfg.Data.outputPrimaryDataset = "Crab_mem_test"
        
        cfg.section_("Site")
        cfg.Site.storageSite = args.out
        
        cfg.Data.ignoreLocality = True
                
        submit(cfg)

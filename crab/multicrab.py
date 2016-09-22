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
        name = "ttH_hbb",
        filename="samples/eth/ttH_hbb.txt",
    ),
    Sample(
        name = "ttH_nonhbb",
        filename="samples/eth/ttH_nonhbb.txt",
    ),
    Sample(
        name = "ttjetsUnsplit",
        filename="samples/eth/ttjetsUnsplit.txt"
    ),
    Sample(
        name = "ttjets_sl_t",
        filename="samples/eth/ttjets_sl_t.txt"
    ),
    Sample(
        name = "ttjets_sl_tbar",
        filename="samples/eth/ttjets_sl_tbar.txt"
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
        cfg.General.requestName = 'MEM_{0}_{1}'.format(args.tag, sample.name)
        cfg.General.workArea = 'crab_projects'
        cfg.General.transferLogs = True
        
        cfg.section_("JobType")
        cfg.JobType.pluginName = 'Analysis'
        cfg.JobType.psetName = 'PSet.py'
        cfg.JobType.scriptExe = 'wrapper.sh'
        cfg.JobType.sendPythonFolder = True
        cfg.JobType.maxMemoryMB = 1000
        cfg.JobType.inputFiles = [
            cfg.JobType.scriptExe,
            'mem.py',
            'cc_looper.py'
        ]
        #1 event is roughly 60 seconds (1 minute), one also needs a O(~30%) time buffer to catch overflows, so
        # for 500 events 1.3 * 500 * 1 = 650
        cfg.JobType.maxJobRuntimeMin = 650
        
        cfg.section_("Data")
        cfg.Data.inputDBS = 'global'
        cfg.Data.splitting = 'FileBased'
        cfg.Data.unitsPerJob = 1
        cfg.Data.totalUnits = -1
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

import argparse, os, glob
from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import getUsernameFromSiteDB, config

class Sample:
    def __init__(self, *args, **kwargs):
        self.name = kwargs.get("name")
        self.filename = kwargs.get("filename")

def submit(config):
    res = crabCommand('submit', config = config)
    return res

def make_samples(files):
    samples = []
    for fi in files:
        path_fi = fi
        lines = open(path_fi).readlines()
        sampname = os.path.basename(fi).replace(".txt", "").replace(".", "_")
        samp = Sample(
            name = sampname,
            filename = path_fi
        )
        samples += [samp]
    return samples

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Submits crab jobs')
    parser.add_argument('--samples', action="store", nargs="+", help="sample files", type=str)
    parser.add_argument('--out', action="store", required=True, help="output site, e.g. T2_CH_CSCS", type=str)
    parser.add_argument('--tag', action="store", required=True, help="unique tag for processing", type=str)
    parser.add_argument('--user', action="store", help="username on grid", type=str, default=getUsernameFromSiteDB())
    #1 MEM event is roughly 60 seconds (1 minute), one also needs a O(~50%) time buffer to catch overflows, so
    parser.add_argument('--runtime', action="store", help="job runtime in minutes", type=int, default=700)
    args = parser.parse_args()
   
    samples = make_samples(args.samples)
   
    jobs_file = open("jobs_{0}.txt".format(args.tag), "w")
    for sample in samples:
        cfg = config()
        
        cfg.section_("General")
        cfg.General.requestName = 'MEM_{0}_{1}'.format(args.tag, sample.name)
        cfg.General.workArea = 'crab_projects/{0}'.format(args.tag)
        if not os.path.exists(cfg.General.workArea):
            os.makedirs(cfg.General.workArea)

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
        cfg.JobType.maxJobRuntimeMin = args.runtime #5 hours
        
        cfg.section_("Data")
        cfg.Data.inputDBS = 'global'
        cfg.Data.splitting = 'FileBased'
        cfg.Data.unitsPerJob = 1
        cfg.Data.totalUnits = -1
        cfg.Data.userInputFiles = map(lambda x: x.strip(), open(sample.filename).readlines())
        cfg.Data.allowNonValidInputDataset = True # to run on datasets in PRODUCTION
        cfg.Data.outLFNDirBase = '/store/user/{0}/mem/{1}'.format(args.user, args.tag)
        cfg.Data.publication = False
        #cfg.Data.outputDatasetTag = 'mem_test_v1'
        #cfg.Data.outputPrimaryDataset = "Crab_mem_test"
        
        cfg.section_("Site")
        cfg.Site.storageSite = args.out
        
        cfg.Data.ignoreLocality = True

        outpath = "{0}/crab_{1}".format(cfg.General.workArea, cfg.General.requestName)
        print outpath
        jobs_file.write(outpath + "\n") 
        try:
            submit(cfg)
        except Exception as e:
            print e
            print "skipping"

    jobs_file.close()

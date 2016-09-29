import argparse, os
from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import getUsernameFromSiteDB, config

class Sample:
    def __init__(self, *args, **kwargs):
        self.name = kwargs.get("name")
        self.filename = kwargs.get("filename")

def submit(config):
    res = crabCommand('submit', config = config)
    return res

def make_samples(target_dir):
    files = os.listdir(target_dir)
    files = filter(lambda x: x.endswith(".txt"), files)
    samples = []
    skipped = []
    for fi in files:
        path_fi = os.path.join(target_dir, fi)
        lines = open(path_fi).readlines()
        #why skip stuff
        #if len(lines) < 50:
            #skipped += [path_fi]
            #print "skipped? ", path_fi
            #continue
        samp = Sample(
            name = fi.split(".")[0],
            filename = path_fi
        )
        samples += [samp]
    return samples, skipped

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Submits crab jobs')
    parser.add_argument('--indir', action="store", help="path to samples", type=str, default="samples//kitMatthias")
    parser.add_argument('--out', action="store", required=True, help="output site, e.g. T2_CH_CSCS", type=str)
    parser.add_argument('--tag', action="store", required=True, help="unique tag for processing", type=str)
    parser.add_argument('--user', action="store", help="username on grid", type=str, default=getUsernameFromSiteDB())
    args = parser.parse_args()
   
    samples, skipped = make_samples(args.indir)
    
    for sample in samples:
        cfg = config()
        
        cfg.section_("General")
        cfg.General.requestName = 'MEMKITV4_{0}_{1}'.format(args.tag, sample.name)
        cfg.General.workArea = 'crab_projectsV4'
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
        cfg.Data.outLFNDirBase = '/store/user/{0}/MEMOutputV3/'.format(args.user)
        cfg.Data.publication = False
        #cfg.Data.outputDatasetTag = 'mem_test_v1'
        #cfg.Data.outputPrimaryDataset = "Crab_mem_test"
        
        cfg.section_("Site")
        cfg.Site.storageSite = args.out
        
        cfg.section_("User")
        cfg.User.voGroup = "dcms"
        
        cfg.Data.ignoreLocality = True
        
        try:
            submit(cfg)
        except Exception as e:
            print e
            print "skipping"
                
                
    print "skipped samples"
    for skip in skipped:
        print skip

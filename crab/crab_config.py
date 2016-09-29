from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'memTestKIT'
config.General.workArea = 'crab_projectsTest'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'wrapper.sh'
config.JobType.sendPythonFolder = True
config.JobType.maxMemoryMB = 1000
config.JobType.inputFiles = [
    config.JobType.scriptExe,
    'mem.py',
    'cc_looper.py'
]
config.JobType.maxJobRuntimeMin = 240

config.section_("Data")
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = -1
config.Data.userInputFiles = [
    "root://xrootd-cms.infn.it///store/user/kelmorab/MEMInputTrees_ICHEP_V3/ttHbb_nominal.root___0___10",
]

config.Data.allowNonValidInputDataset = True # to run on datasets in PRODUCTION
config.Data.outLFNDirBase = '/store/user/kelmorab/mem/'
config.Data.publication = False
#config.Data.outputDatasetTag = 'mem_test_v1'
#config.Data.outputPrimaryDataset = "Crab_mem_test"

config.section_("Site")
config.Site.storageSite = "T2_DE_DESY"

config.Data.ignoreLocality = True

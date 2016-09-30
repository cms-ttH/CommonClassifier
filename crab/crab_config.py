from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'MEM_test_Sep30_v3'
config.General.workArea = 'crab_projects'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'wrapper.sh'
config.JobType.sendPythonFolder = True
config.JobType.maxMemoryMB = 2000
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
    "/store/group/phys_higgs/hbb/mem/Sep26/Sep14_leptonic_nome__ttHTobb_M125_13TeV_powheg_pythia8.root___0___10",
    "/store/group/phys_higgs/hbb/mem/Sep26/Sep14_leptonic_nome__ttHTobb_M125_13TeV_powheg_pythia8.root___11___20",
]

config.Data.allowNonValidInputDataset = True # to run on datasets in PRODUCTION
config.Data.outLFNDirBase = '/store/user/jpata/mem/'
config.Data.publication = False
config.Data.outputDatasetTag = 'mem_test_v1'
config.Data.outputPrimaryDataset = "Crab_mem_test"

config.section_("Site")
config.Site.storageSite = "T2_CH_CSCS"

config.Data.ignoreLocality = True

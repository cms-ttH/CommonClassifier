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
      #Sample( name="ttHbb_nominal",filename="samples/kit/ttHbb_nominal.txt",),
      #Sample( name="ttHnonbb_nominal",filename="samples/kit/ttHnonbb_nominal.txt",),
      #Sample( name="Tranche3_ttHbb_nominal",filename="samples/kit/Tranche3_ttHbb_nominal.txt",),
      #Sample( name="Tranche3_ttHnonbb_nominal",filename="samples/kit/Tranche3_ttHnonbb_nominal.txt",),
      #Sample( name="ttbar_incl_All_nominal",filename="samples/kit/ttbar_incl_All_nominal.txt",),
      #Sample( name="ttbar_SL_nominal",filename="samples/kit/ttbar_SL_nominal.txt",),
      #Sample( name="scaleDown_ttbar_SL_nominal",filename="samples/kit/scaleDown_ttbar_SL_nominal.txt",),
      #Sample( name="scaleDown_ttbar_incl_nominal",filename="samples/kit/scaleDown_ttbar_incl_nominal.txt",),
      #Sample( name="scaleUp_ttbar_SL_nominal",filename="samples/kit/scaleUp_ttbar_SL_nominal.txt",),
      #Sample( name="scaleUp_ttbar_incl_nominal",filename="samples/kit/scaleUp_ttbar_incl_nominal.txt",),
      #Sample( name="stbar_s-channel_nominal",filename="samples/kit/stbar_s-channel_nominal.txt",),
      #Sample( name="WW_nominal",filename="samples/kit/WW_nominal.txt",),
      #Sample( name="WZ_nominal",filename="samples/kit/WZ_nominal.txt",),
      #Sample( name="ZZ_nominal",filename="samples/kit/ZZ_nominal.txt",),
      #Sample( name="el_data_nominal",filename="samples/kit/el_data_nominal.txt",),
      #Sample( name="mu_data_nominal",filename="samples/kit/mu_data_nominal.txt",),
      #Sample( name="WJets-HT-800-1200_nominal",filename="samples/kit/WJets-HT-800-1200_nominal.txt",),
      #Sample( name="WJets-HT-600-800_nominal",filename="samples/kit/WJets-HT-600-800_nominal.txt",),
      #Sample( name="WJets-HT-400-600_nominal",filename="samples/kit/WJets-HT-400-600_nominal.txt",),
      #Sample( name="WJets-HT-2500-Inf_nominal",filename="samples/kit/WJets-HT-2500-Inf_nominal.txt",),
      #Sample( name="WJets-HT-1200-2500_nominal",filename="samples/kit/WJets-HT-1200-2500_nominal.txt",),
      #Sample( name="WJets-HT-100-200_nominal",filename="samples/kit/WJets-HT-100-200_nominal.txt",),
      #Sample( name="ttHbb_JESUP",filename="samples/kit/ttHbb_JESUP.txt",),
      #Sample( name="ttHnonbb_JESUP",filename="samples/kit/ttHnonbb_JESUP.txt",),
      #Sample( name="Tranche3_ttHbb_JESUP",filename="samples/kit/Tranche3_ttHbb_JESUP.txt",),
      #Sample( name="Tranche3_ttHnonbb_JESUP",filename="samples/kit/Tranche3_ttHnonbb_JESUP.txt",),
      #Sample( name="ttbar_incl_All_JESUP",filename="samples/kit/ttbar_incl_All_JESUP.txt",),
      #Sample( name="ttbar_SL_JESUP",filename="samples/kit/ttbar_SL_JESUP.txt",),
      #Sample( name="scaleDown_ttbar_SL_JESUP",filename="samples/kit/scaleDown_ttbar_SL_JESUP.txt",),
      #Sample( name="scaleDown_ttbar_incl_JESUP",filename="samples/kit/scaleDown_ttbar_incl_JESUP.txt",),
      #Sample( name="scaleUp_ttbar_SL_JESUP",filename="samples/kit/scaleUp_ttbar_SL_JESUP.txt",),
      #Sample( name="scaleUp_ttbar_incl_JESUP",filename="samples/kit/scaleUp_ttbar_incl_JESUP.txt",),
      #Sample( name="stbar_s-channel_JESUP",filename="samples/kit/stbar_s-channel_JESUP.txt",),
      #Sample( name="WW_JESUP",filename="samples/kit/WW_JESUP.txt",),
      #Sample( name="WZ_JESUP",filename="samples/kit/WZ_JESUP.txt",),
      #Sample( name="ZZ_JESUP",filename="samples/kit/ZZ_JESUP.txt",),
      #Sample( name="WJets-HT-800-1200_JESUP",filename="samples/kit/WJets-HT-800-1200_JESUP.txt",),
      #Sample( name="WJets-HT-600-800_JESUP",filename="samples/kit/WJets-HT-600-800_JESUP.txt",),
      #Sample( name="WJets-HT-400-600_JESUP",filename="samples/kit/WJets-HT-400-600_JESUP.txt",),
      #Sample( name="WJets-HT-2500-Inf_JESUP",filename="samples/kit/WJets-HT-2500-Inf_JESUP.txt",),
      #Sample( name="WJets-HT-1200-2500_JESUP",filename="samples/kit/WJets-HT-1200-2500_JESUP.txt",),
      #Sample( name="WJets-HT-100-200_JESUP",filename="samples/kit/WJets-HT-100-200_JESUP.txt",),
      #Sample( name="ttHbb_JESDOWN",filename="samples/kit/ttHbb_JESDOWN.txt",),
      #Sample( name="ttHnonbb_JESDOWN",filename="samples/kit/ttHnonbb_JESDOWN.txt",),
      #Sample( name="Tranche3_ttHbb_JESDOWN",filename="samples/kit/Tranche3_ttHbb_JESDOWN.txt",),
      #Sample( name="Tranche3_ttHnonbb_JESDOWN",filename="samples/kit/Tranche3_ttHnonbb_JESDOWN.txt",),
      #Sample( name="ttbar_incl_All_JESDOWN",filename="samples/kit/ttbar_incl_All_JESDOWN.txt",),
      #Sample( name="ttbar_SL_JESDOWN",filename="samples/kit/ttbar_SL_JESDOWN.txt",),
      #Sample( name="scaleDown_ttbar_SL_JESDOWN",filename="samples/kit/scaleDown_ttbar_SL_JESDOWN.txt",),
      #Sample( name="scaleDown_ttbar_incl_JESDOWN",filename="samples/kit/scaleDown_ttbar_incl_JESDOWN.txt",),
      #Sample( name="scaleUp_ttbar_SL_JESDOWN",filename="samples/kit/scaleUp_ttbar_SL_JESDOWN.txt",),
      #Sample( name="scaleUp_ttbar_incl_JESDOWN",filename="samples/kit/scaleUp_ttbar_incl_JESDOWN.txt",),
      #Sample( name="stbar_s-channel_JESDOWN",filename="samples/kit/stbar_s-channel_JESDOWN.txt",),
      #Sample( name="WW_JESDOWN",filename="samples/kit/WW_JESDOWN.txt",),
      #Sample( name="WZ_JESDOWN",filename="samples/kit/WZ_JESDOWN.txt",),
      #Sample( name="ZZ_JESDOWN",filename="samples/kit/ZZ_JESDOWN.txt",),
      #Sample( name="WJets-HT-800-1200_JESDOWN",filename="samples/kit/WJets-HT-800-1200_JESDOWN.txt",),
      #Sample( name="WJets-HT-600-800_JESDOWN",filename="samples/kit/WJets-HT-600-800_JESDOWN.txt",),
      #Sample( name="WJets-HT-400-600_JESDOWN",filename="samples/kit/WJets-HT-400-600_JESDOWN.txt",),
      #Sample( name="WJets-HT-2500-Inf_JESDOWN",filename="samples/kit/WJets-HT-2500-Inf_JESDOWN.txt",),
      #Sample( name="WJets-HT-1200-2500_JESDOWN",filename="samples/kit/WJets-HT-1200-2500_JESDOWN.txt",),
      #Sample( name="WJets-HT-100-200_JESDOWN",filename="samples/kit/WJets-HT-100-200_JESDOWN.txt",),
      #Sample( name="ttHbb_JERUP",filename="samples/kit/ttHbb_JERUP.txt",),
      #Sample( name="ttHnonbb_JERUP",filename="samples/kit/ttHnonbb_JERUP.txt",),
      #Sample( name="Tranche3_ttHbb_JERUP",filename="samples/kit/Tranche3_ttHbb_JERUP.txt",),
      #Sample( name="Tranche3_ttHnonbb_JERUP",filename="samples/kit/Tranche3_ttHnonbb_JERUP.txt",),
      #Sample( name="ttbar_incl_All_JERUP",filename="samples/kit/ttbar_incl_All_JERUP.txt",),
      #Sample( name="ttbar_SL_JERUP",filename="samples/kit/ttbar_SL_JERUP.txt",),
      #Sample( name="scaleDown_ttbar_SL_JERUP",filename="samples/kit/scaleDown_ttbar_SL_JERUP.txt",),
      #Sample( name="scaleDown_ttbar_incl_JERUP",filename="samples/kit/scaleDown_ttbar_incl_JERUP.txt",),
      #Sample( name="scaleUp_ttbar_SL_JERUP",filename="samples/kit/scaleUp_ttbar_SL_JERUP.txt",),
      #Sample( name="WW_JERUP",filename="samples/kit/WW_JERUP.txt",),
      #Sample( name="scaleUp_ttbar_incl_JERUP",filename="samples/kit/scaleUp_ttbar_incl_JERUP.txt",),
      #Sample( name="stbar_s-channel_JERUP",filename="samples/kit/stbar_s-channel_JERUP.txt",),
      #Sample( name="WZ_JERUP",filename="samples/kit/WZ_JERUP.txt",),
      #Sample( name="ZZ_JERUP",filename="samples/kit/ZZ_JERUP.txt",),
      
      #Sample( name="WJets-HT-800-1200_JERUP",filename="samples/kit/WJets-HT-800-1200_JERUP.txt",),
      #Sample( name="WJets-HT-600-800_JERUP",filename="samples/kit/WJets-HT-600-800_JERUP.txt",),
      Sample( name="WJets-HT-400-600_JERUP",filename="samples/kit/WJets-HT-400-600_JERUP.txt",),
      Sample( name="WJets-HT-2500-Inf_JERUP",filename="samples/kit/WJets-HT-2500-Inf_JERUP.txt",),
      Sample( name="WJets-HT-1200-2500_JERUP",filename="samples/kit/WJets-HT-1200-2500_JERUP.txt",),
      Sample( name="WJets-HT-100-200_JERUP",filename="samples/kit/WJets-HT-100-200_JERUP.txt",),
      Sample( name="ttHbb_JERDOWN",filename="samples/kit/ttHbb_JERDOWN.txt",),
      Sample( name="ttHnonbb_JERDOWN",filename="samples/kit/ttHnonbb_JERDOWN.txt",),
      Sample( name="Tranche3_ttHbb_JERDOWN",filename="samples/kit/Tranche3_ttHbb_JERDOWN.txt",),
      Sample( name="Tranche3_ttHnonbb_JERDOWN",filename="samples/kit/Tranche3_ttHnonbb_JERDOWN.txt",),
      Sample( name="ttbar_incl_All_JERDOWN",filename="samples/kit/ttbar_incl_All_JERDOWN.txt",),
      #Sample( name="ttbar_SL_JERDOWN",filename="samples/kit/ttbar_SL_JERDOWN.txt",),
      #Sample( name="scaleDown_ttbar_SL_JERDOWN",filename="samples/kit/scaleDown_ttbar_SL_JERDOWN.txt",),
      #Sample( name="scaleDown_ttbar_incl_JERDOWN",filename="samples/kit/scaleDown_ttbar_incl_JERDOWN.txt",),
      #Sample( name="scaleUp_ttbar_SL_JERDOWN",filename="samples/kit/scaleUp_ttbar_SL_JERDOWN.txt",),
      #Sample( name="scaleUp_ttbar_incl_JERDOWN",filename="samples/kit/scaleUp_ttbar_incl_JERDOWN.txt",),
      Sample( name="stbar_s-channel_JERDOWN",filename="samples/kit/stbar_s-channel_JERDOWN.txt",),
      Sample( name="WW_JERDOWN",filename="samples/kit/WW_JERDOWN.txt",),
      Sample( name="WZ_JERDOWN",filename="samples/kit/WZ_JERDOWN.txt",),
      Sample( name="ZZ_JERDOWN",filename="samples/kit/ZZ_JERDOWN.txt",),
      Sample( name="WJets-HT-800-1200_JERDOWN",filename="samples/kit/WJets-HT-800-1200_JERDOWN.txt",),
      Sample( name="WJets-HT-600-800_JERDOWN",filename="samples/kit/WJets-HT-600-800_JERDOWN.txt",),
      Sample( name="WJets-HT-400-600_JERDOWN",filename="samples/kit/WJets-HT-400-600_JERDOWN.txt",),
      Sample( name="WJets-HT-2500-Inf_JERDOWN",filename="samples/kit/WJets-HT-2500-Inf_JERDOWN.txt",),
      Sample( name="WJets-HT-1200-2500_JERDOWN",filename="samples/kit/WJets-HT-1200-2500_JERDOWN.txt",),
      Sample( name="WJets-HT-100-200_JERDOWN",filename="samples/kit/WJets-HT-100-200_JERDOWN.txt",),
      Sample( name="st_tchan_nominal",filename="samples/kit/st_tchan_nominal.txt",),
      Sample( name="stbar_tchan_nominal",filename="samples/kit/stbar_tchan_nominal.txt",),
      Sample( name="st_tWchan_nominal",filename="samples/kit/st_tWchan_nominal.txt",),
      Sample( name="stbar_tWchan_nominal",filename="samples/kit/stbar_tWchan_nominal.txt",),
      Sample( name="st_tchan_JESUP",filename="samples/kit/st_tchan_JESUP.txt",),
      Sample( name="stbar_tchan_JESUP",filename="samples/kit/stbar_tchan_JESUP.txt",),
      Sample( name="st_tWchan_JESUP",filename="samples/kit/st_tWchan_JESUP.txt",),
      Sample( name="stbar_tWchan_JESUP",filename="samples/kit/stbar_tWchan_JESUP.txt",),
      Sample( name="st_tchan_JESDOWN",filename="samples/kit/st_tchan_JESDOWN.txt",),
      Sample( name="stbar_tchan_JESDOWN",filename="samples/kit/stbar_tchan_JESDOWN.txt",),
      Sample( name="st_tWchan_JESDOWN",filename="samples/kit/st_tWchan_JESDOWN.txt",),
      Sample( name="stbar_tWchan_JESDOWN",filename="samples/kit/stbar_tWchan_JESDOWN.txt",),
      Sample( name="st_tchan_JERUP",filename="samples/kit/st_tchan_JERUP.txt",),
      Sample( name="stbar_tchan_JERUP",filename="samples/kit/stbar_tchan_JERUP.txt",),
      Sample( name="st_tWchan_JERUP",filename="samples/kit/st_tWchan_JERUP.txt",),
      Sample( name="stbar_tWchan_JERUP",filename="samples/kit/stbar_tWchan_JERUP.txt",),
      Sample( name="st_tchan_JERDOWN",filename="samples/kit/st_tchan_JERDOWN.txt",),
      Sample( name="stbar_tchan_JERDOWN",filename="samples/kit/stbar_tchan_JERDOWN.txt",),
      Sample( name="st_tWchan_JERDOWN",filename="samples/kit/st_tWchan_JERDOWN.txt",),
      Sample( name="stbar_tWchan_JERDOWN",filename="samples/kit/stbar_tWchan_JERDOWN.txt",),
Sample( name="ttW_JetToLNu_nominal",filename="samples/kit/ttW_JetToLNu_nominal.txt",),
Sample( name="ttW_JetToQQ_nominal",filename="samples/kit/ttW_JetToQQ_nominal.txt",),
Sample( name="ttZ_ToQQ_nominal",filename="samples/kit/ttZ_ToQQ_nominal.txt",),
Sample( name="Zjets_m50toInf_nominal",filename="samples/kit/Zjets_m50toInf_nominal.txt",),
Sample( name="ttW_JetToLNu_JESUP",filename="samples/kit/ttW_JetToLNu_JESUP.txt",),
Sample( name="ttW_JetToQQ_JESUP",filename="samples/kit/ttW_JetToQQ_JESUP.txt",),
Sample( name="ttZ_ToQQ_JESUP",filename="samples/kit/ttZ_ToQQ_JESUP.txt",),
Sample( name="Zjets_m50toInf_JESUP",filename="samples/kit/Zjets_m50toInf_JESUP.txt",),
Sample( name="ttW_JetToLNu_JESDOWN",filename="samples/kit/ttW_JetToLNu_JESDOWN.txt",),
Sample( name="ttW_JetToQQ_JESDOWN",filename="samples/kit/ttW_JetToQQ_JESDOWN.txt",),
Sample( name="ttZ_ToQQ_JESDOWN",filename="samples/kit/ttZ_ToQQ_JESDOWN.txt",),
Sample( name="Zjets_m50toInf_JESDOWN",filename="samples/kit/Zjets_m50toInf_JESDOWN.txt",),
Sample( name="ttW_JetToLNu_JERUP",filename="samples/kit/ttW_JetToLNu_JERUP.txt",),
Sample( name="ttW_JetToQQ_JERUP",filename="samples/kit/ttW_JetToQQ_JERUP.txt",),
Sample( name="ttZ_ToQQ_JERUP",filename="samples/kit/ttZ_ToQQ_JERUP.txt",),
Sample( name="Zjets_m50toInf_JERUP",filename="samples/kit/Zjets_m50toInf_JERUP.txt",),
Sample( name="ttW_JetToLNu_JERDOWN",filename="samples/kit/ttW_JetToLNu_JERDOWN.txt",),
Sample( name="ttW_JetToQQ_JERDOWN",filename="samples/kit/ttW_JetToQQ_JERDOWN.txt",),
Sample( name="ttZ_ToQQ_JERDOWN",filename="samples/kit/ttZ_ToQQ_JERDOWN.txt",),
Sample( name="Zjets_m50toInf_JERDOWN",filename="samples/kit/Zjets_m50toInf_JERDOWN.txt",),

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

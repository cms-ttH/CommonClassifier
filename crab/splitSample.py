import ROOT, os

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]

def genSplitting(infile, perjob, outfile):
    fi = ROOT.TFile.Open(infile)
    tree = fi.Get("tree")
    nevents = tree.GetEntries()
    of = open(outfile, "w")
    for chunk in chunks(range(nevents), perjob):
        of.write("{0}___{1}___{2}\n".format(infile, chunk[0], chunk[-1]))
    of.close()
    fi.Close()
    return nevents

def create_splitting(pref, samples, target_dir):
    samples_events = []
    for name, samp in samples:
        samples_events += [(
            name,
            pref + samp,
            genSplitting(pref + samp, 500, target_dir + "/{0}.txt".format(name))
        )]
    
    sample_file = open(target_dir + "/samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

if __name__ == "__main__":
    pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/ETH_Oct2/"
    samples = [
        ("data_ee", "Sep14_leptonic_nome__DoubleEG.root"),
        ("data_mm", "Sep14_leptonic_nome__DoubleMuon.root"),
        ("data_em", "Sep14_leptonic_nome__MuonEG.root"),
        ("data_e", "Sep14_leptonic_nome__SingleElectron.root"),
        ("data_m", "Sep14_leptonic_nome__SingleMuon.root"),
        
        ("st_s", "Sep29_v1__ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root"),
        ("stbar_t", "Sep29_v1__ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
        ("st_t", "Sep29_v1__ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
        ("stbar_tw", "Sep29_v1__ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
        ("st_tw", "Sep29_v1__ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
        ("ttjets_sl_t", "Sep29_v1__TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"),
        ("ttjets_sl_tbar", "Sep29_v1__TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"),
        ("ttw_wqq", "Sep29_v1__TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root"),
        ("ttz_zqq", "Sep29_v1__TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"),
        ("ttjetsUnsplit_scaledown", "Sep29_v1__TT_TuneCUETP8M1_13TeV-powheg-scaledown-pythia8.root"),
        ("ttjetsUnsplit", "Sep29_v1__TT_TuneCUETP8M1_13TeV-powheg-scaleup-pythia8.root"),
        ("ww", "Sep29_v1__WW_TuneCUETP8M1_13TeV-pythia8.root"),
        ("zz", "Sep29_v1__WZ_TuneCUETP8M1_13TeV-pythia8.root"),
        ("zz", "Sep29_v1__ZZ_TuneCUETP8M1_13TeV-pythia8.root"),
        ("ttH_nonhbb", "Sep29_v1__ttHToNonbb_M125_13TeV_powheg_pythia8.root"),
        ("ttH_nonhbb_tranche3", "Sep29_v1__ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8.root"),
        ("ttH_hbb", "Sep29_v1__ttHTobb_M125_13TeV_powheg_pythia8.root"),
        ("ttH_hbb_tranche3", "Sep29_v1__ttHTobb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8.root"),
    ]
    create_splitting(pref, samples, "samples/eth")
   
    #pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/DESY/"
    #samples = [(s.split(".")[0], s) for s in os.listdir("/afs/cern.ch/work/g/gvonsem/public/MEMttH/28Sep2016/")]
    #print samples
    #create_splitting(pref, samples, "samples/desy")
   


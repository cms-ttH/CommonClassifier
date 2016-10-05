import ROOT, os, math

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]

def roundup(x):
    return int(math.ceil(x / 100.0)) * 100

def genSplitting(infile, perjob, outfile):
    fi = ROOT.TFile.Open(infile)
    tree = fi.Get("tree")

    #all events
    nevents = tree.GetEntries()

    if hasattr(tree, "hypo"):
        #events where we askes the MEM to be calculated
        nevents_hypo = tree.GetEntries("hypo >= -1")
        ratio_mem = float(nevents)/float(nevents_hypo)
        perjob = roundup(int(perjob*ratio_mem))
    else:
        nevents_hypo = nevents
        ratio_mem = 1

    if nevents > 0:
        print infile, nevents, nevents_hypo, ratio_mem, perjob

        of = open(outfile, "w")
        for chunk in chunks(range(nevents), perjob):
            of.write("{0}___{1}___{2}\n".format(infile, chunk[0], chunk[-1]))
        of.close()
        fi.Close()
    return nevents

def create_splitting(pref, samples, target_dir, perjob=200):
    samples_events = []
    for name, samp in samples:
        samples_events += [(
            name,
            pref + samp,
            genSplitting(pref + samp, perjob, target_dir + "/{0}.txt".format(name))
        )]
    
    sample_file = open(target_dir + "/samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

if __name__ == "__main__":
    #pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/ETH_Oct2/"
    #samples = [
    #    ("data_ee", "Sep14_leptonic_nome__DoubleEG.root"),
    #    ("data_mm", "Sep14_leptonic_nome__DoubleMuon.root"),
    #    ("data_em", "Sep14_leptonic_nome__MuonEG.root"),
    #    ("data_e", "Sep14_leptonic_nome__SingleElectron.root"),
    #    ("data_m", "Sep14_leptonic_nome__SingleMuon.root"),
    #    
    #    ("st_s", "Sep29_v1__ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1.root"),
    #    ("stbar_t", "Sep29_v1__ST_t-channel_antitop_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
    #    ("st_t", "Sep29_v1__ST_t-channel_top_4f_leptonDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
    #    ("stbar_tw", "Sep29_v1__ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
    #    ("st_tw", "Sep29_v1__ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root"),
    #    ("ttjets_sl_t", "Sep29_v1__TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"),
    #    ("ttjets_sl_tbar", "Sep29_v1__TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"),
    #    ("ttw_wqq", "Sep29_v1__TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root"),
    #    ("ttz_zqq", "Sep29_v1__TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root"),
    #    ("ttjetsUnsplit_scaledown", "Sep29_v1__TT_TuneCUETP8M1_13TeV-powheg-scaledown-pythia8.root"),
    #    ("ww", "Sep29_v1__WW_TuneCUETP8M1_13TeV-pythia8.root"),
    #    ("zz", "Sep29_v1__WZ_TuneCUETP8M1_13TeV-pythia8.root"),
    #    ("zz", "Sep29_v1__ZZ_TuneCUETP8M1_13TeV-pythia8.root"),
    #    
    #    ("ttH_nonhbb_tranche3", "Sep29_v1__ttHToNonbb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8.root"),
    #    ("ttH_hbb_tranche3", "Sep29_v1__ttHTobb_M125_TuneCUETP8M2_ttHtranche3_13TeV-powheg-pythia8.root"),
    #    
    #    ("ttH_nonhbb", "Sep14_leptonic_nome__ttHToNonbb_M125_13TeV_powheg_pythia8.root"),
    #    ("ttH_hbb", "Sep14_leptonic_nome__ttHTobb_M125_13TeV_powheg_pythia8.root"),
    #    ("ttjetsUnsplit", "Sep14_leptonic_nome__TT_TuneCUETP8M1_13TeV-powheg-pythia8.root"),
    #]
    #create_splitting(pref, samples, "samples/eth")

    #pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/DESY/"
    #samples = [(s.split(".")[0], s) for s in os.listdir("/afs/cern.ch/work/g/gvonsem/public/MEMttH/28Sep2016/")]
    #create_splitting(pref, samples, "samples/desy")

    # KIT jobs have all >=4j >=2t events, which is 4x >=4j >=3.
    # For jobs that last 5h = 300min, 1 minute/MEM, it would be 300 MEM events, which is ~1200 any events
    # so specifying 1000events and 5h should be on the safe side
    pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/MEMInputTrees_ICHEP_V3newttsl/" 
    samples = [(s.split(".")[0].strip(), s.strip()) for s in open("/mnt/t3nfs01/data01/shome/jpata/karim_samples/sample_list.txt").readlines()]
    create_splitting(pref, samples, "samples/kit", 1000)
   


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
            genSplitting(pref + samp, 300, target_dir + "/{0}.txt".format(name))
        )]
    
    sample_file = open(target_dir + "/samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

if __name__ == "__main__":
    #pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/Sep26/"
    #samples = [
    #    ("data_ee", "Sep14_leptonic_nome__DoubleEG.root"),
    #    ("data_mm", "Sep14_leptonic_nome__DoubleMuon.root"),
    #    ("data_em", "Sep14_leptonic_nome__MuonEG.root"),
    #    ("data_e", "Sep14_leptonic_nome__SingleElectron.root"),
    #    ("data_m", "Sep14_leptonic_nome__SingleMuon.root"),
    #    ("ttjets_sl_t", "Sep14_leptonic_nome__TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"),
    #    ("ttjets_sl_tbar", "Sep14_leptonic_nome__TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"),
    #    ("ttjetsUnsplit", "Sep14_leptonic_nome__TT_TuneCUETP8M1_13TeV-powheg-pythia8.root"),
    #    ("ttH_nonhbb", "Sep14_leptonic_nome__ttHToNonbb_M125_13TeV_powheg_pythia8.root"),
    #    ("ttH_hbb", "Sep14_leptonic_nome__ttHTobb_M125_13TeV_powheg_pythia8.root"),
    #]
    #create_splitting(pref, samples, "samples/eth")
   
    pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/DESY/"
    samples = [(s.split(".")[0], s) for s in os.listdir("/afs/cern.ch/work/g/gvonsem/public/MEMttH/28Sep2016/")]
    print samples

    create_splitting(pref, samples, "samples/desy")
   


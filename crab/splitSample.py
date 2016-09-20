import ROOT

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


if __name__ == "__main__":
    pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem"
    genSplitting(pref + "/Sep14_leptonic_nome_v1__ttHTobb_M125_13TeV_powheg_pythia8.root", 500, "tth.txt")
    genSplitting(pref + "/Sep14_leptonic_nome_v1__TT_TuneCUETP8M1_13TeV-powheg-pythia8.root", 500, "ttjets.txt")

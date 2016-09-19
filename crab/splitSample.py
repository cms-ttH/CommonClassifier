import ROOT

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]

def genSplitting(infile, perjob):
    fi = ROOT.TFile.Open(infile)
    tree = fi.Get("tree")
    nevents = tree.GetEntries()
    for chunk in chunks(range(nevents), perjob):
        print "{0}___{1}___{2}".format(infile, chunk[0], chunk[-1])
    fi.Close()

if __name__ == "__main__":
    infile = "root://storage01.lcg.cscs.ch/pnfs/lcg.cscs.ch/cms/trivcat/store/user/jpata/mem/Sep14_leptonic_nome_v1__ttHTobb_M125_13TeV_powheg_pythia8.root"
    genSplitting(infile, 100)

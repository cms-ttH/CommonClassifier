import ROOT

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]

def genSplitting(infile, perjob, outfile):
    fi = ROOT.TFile.Open(infile)
    tree = fi.Get("tree")
    nevents = tree.GetEntries()
    print nevents
    of = open(outfile, "w")
    for chunk in chunks(range(nevents), perjob):
        of.write("{0}___{1}___{2}\n".format(infile, chunk[0], chunk[-1]))
    of.close()
    fi.Close()
    return nevents

if __name__ == "__main__":
    pref = "root://xrootd-cms.infn.it///store/user/kelmorab/MEMInputTrees_ICHEP_V3newttsl/"
    
    samples = [
("Tranche3_ttbar_SL_29_JESUP","Tranche3_ttbar_SL_29_JESUP.root"),
("Tranche3_ttbar_SL_30_JERDOWN","Tranche3_ttbar_SL_30_JERDOWN.root"),
("Tranche3_ttbar_SL_31_JESDOWN","Tranche3_ttbar_SL_31_JESDOWN.root"),
("Tranche3_ttbar_SL_32_JESDOWN","Tranche3_ttbar_SL_32_JESDOWN.root"),
("Tranche3_ttbar_SL_34_JERDOWN","Tranche3_ttbar_SL_34_JERDOWN.root"),
("Tranche3_ttbar_SL_34_JERUP","Tranche3_ttbar_SL_34_JERUP.root"),
("Tranche3_ttbar_SL_35_JERDOWN","Tranche3_ttbar_SL_35_JERDOWN.root"),
("Tranche3_ttbar_SL_36_JERDOWN","Tranche3_ttbar_SL_36_JERDOWN.root"),
("Tranche3_ttbar_SL_36_JERUP","Tranche3_ttbar_SL_36_JERUP.root"),
("Tranche3_ttbar_SL_36_JESDOWN","Tranche3_ttbar_SL_36_JESDOWN.root"),
("Tranche3_ttbar_SL_37_JESUP","Tranche3_ttbar_SL_37_JESUP.root"),
("Tranche3_ttbar_SL_37_JERDOWN","Tranche3_ttbar_SL_37_JERDOWN.root"),
("Tranche3_ttbar_SL_37_JERUP","Tranche3_ttbar_SL_37_JERUP.root"),
("Tranche3_ttbar_SL_37_JESDOWN","Tranche3_ttbar_SL_37_JESDOWN.root"),
("Tranche3_ttbar_SL_38_JERUP","Tranche3_ttbar_SL_38_JERUP.root"),
("Tranche3_ttbar_SL_38_JESUP","Tranche3_ttbar_SL_38_JESUP.root"),
("Tranche3_ttbar_SL_39_JESUP","Tranche3_ttbar_SL_39_JESUP.root"),
("Tranche3_ttbar_SL_28_nominal","Tranche3_ttbar_SL_28_nominal.root"),
("Tranche3_ttbar_SL_27_nominal","Tranche3_ttbar_SL_27_nominal.root"),
    ]
   
    samples_events = []
    for name, samp in samples:
        print name
        samples_events += [(
            name,
            pref + samp,
            genSplitting(pref + samp, 1000, "samples/kitMatthiasNewTTSL/{0}.txt".format(name))
        )]

    sample_file = open("samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

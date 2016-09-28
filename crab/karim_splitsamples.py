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
    pref = "root://xrootd-cms.infn.it///store/user/kelmorab/MEMInputTrees_ICHEP_V3/"
    
    samples = [
      ("ttW_JetToLNu_nominal","ttW_JetToLNu_nominal.root"),
("ttW_JetToQQ_nominal","ttW_JetToQQ_nominal.root"),
("ttZ_ToQQ_nominal","ttZ_ToQQ_nominal.root"),
("Zjets_m50toInf_nominal","Zjets_m50toInf_nominal.root"),
("ttW_JetToLNu_JESUP","ttW_JetToLNu_JESUP.root"),
("ttW_JetToQQ_JESUP","ttW_JetToQQ_JESUP.root"),
("ttZ_ToQQ_JESUP","ttZ_ToQQ_JESUP.root"),
("Zjets_m50toInf_JESUP","Zjets_m50toInf_JESUP.root"),
("ttW_JetToLNu_JESDOWN","ttW_JetToLNu_JESDOWN.root"),
("ttW_JetToQQ_JESDOWN","ttW_JetToQQ_JESDOWN.root"),
("ttZ_ToQQ_JESDOWN","ttZ_ToQQ_JESDOWN.root"),
("Zjets_m50toInf_JESDOWN","Zjets_m50toInf_JESDOWN.root"),
("ttW_JetToLNu_JERUP","ttW_JetToLNu_JERUP.root"),
("ttW_JetToQQ_JERUP","ttW_JetToQQ_JERUP.root"),
("ttZ_ToQQ_JERUP","ttZ_ToQQ_JERUP.root"),
("Zjets_m50toInf_JERUP","Zjets_m50toInf_JERUP.root"),
("ttW_JetToLNu_JERDOWN","ttW_JetToLNu_JERDOWN.root"),
("ttW_JetToQQ_JERDOWN","ttW_JetToQQ_JERDOWN.root"),
("ttZ_ToQQ_JERDOWN","ttZ_ToQQ_JERDOWN.root"),
("Zjets_m50toInf_JERDOWN","Zjets_m50toInf_JERDOWN.root"),


    ]
   
    samples_events = []
    for name, samp in samples:
        print name
        samples_events += [(
            name,
            pref + samp,
            genSplitting(pref + samp, 200, "samples/kit/{0}.txt".format(name))
        )]

    sample_file = open("samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

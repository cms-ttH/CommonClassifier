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
("Tranche3_ttbar_SL_30_JERUP","Tranche3_ttbar_SL_30_JERUP.root"),
("Tranche3_ttbar_SL_30_JESDOWN","Tranche3_ttbar_SL_30_JESDOWN.root"),
("Tranche3_ttbar_SL_30_JESUP","Tranche3_ttbar_SL_30_JESUP.root"),
("Tranche3_ttbar_SL_30_nominal","Tranche3_ttbar_SL_30_nominal.root"),
("Tranche3_ttbar_SL_31_JERDOWN","Tranche3_ttbar_SL_31_JERDOWN.root"),
("Tranche3_ttbar_SL_31_JERUP","Tranche3_ttbar_SL_31_JERUP.root"),
("Tranche3_ttbar_SL_31_JESDOWN","Tranche3_ttbar_SL_31_JESDOWN.root"),
("Tranche3_ttbar_SL_31_JESUP","Tranche3_ttbar_SL_31_JESUP.root"),
("Tranche3_ttbar_SL_31_nominal","Tranche3_ttbar_SL_31_nominal.root"),
("Tranche3_ttbar_SL_32_JERDOWN","Tranche3_ttbar_SL_32_JERDOWN.root"),
("Tranche3_ttbar_SL_32_JERUP","Tranche3_ttbar_SL_32_JERUP.root"),
("Tranche3_ttbar_SL_32_JESDOWN","Tranche3_ttbar_SL_32_JESDOWN.root"),
("Tranche3_ttbar_SL_32_JESUP","Tranche3_ttbar_SL_32_JESUP.root"),
("Tranche3_ttbar_SL_32_nominal","Tranche3_ttbar_SL_32_nominal.root"),
("Tranche3_ttbar_SL_33_JERDOWN","Tranche3_ttbar_SL_33_JERDOWN.root"),
("Tranche3_ttbar_SL_33_JERUP","Tranche3_ttbar_SL_33_JERUP.root"),
("Tranche3_ttbar_SL_33_JESDOWN","Tranche3_ttbar_SL_33_JESDOWN.root"),
("Tranche3_ttbar_SL_33_JESUP","Tranche3_ttbar_SL_33_JESUP.root"),
("Tranche3_ttbar_SL_33_nominal","Tranche3_ttbar_SL_33_nominal.root"),
("Tranche3_ttbar_SL_34_JERDOWN","Tranche3_ttbar_SL_34_JERDOWN.root"),
("Tranche3_ttbar_SL_34_JERUP","Tranche3_ttbar_SL_34_JERUP.root"),
("Tranche3_ttbar_SL_34_JESDOWN","Tranche3_ttbar_SL_34_JESDOWN.root"),
("Tranche3_ttbar_SL_34_JESUP","Tranche3_ttbar_SL_34_JESUP.root"),
("Tranche3_ttbar_SL_34_nominal","Tranche3_ttbar_SL_34_nominal.root"),
("Tranche3_ttbar_SL_35_JERDOWN","Tranche3_ttbar_SL_35_JERDOWN.root"),
("Tranche3_ttbar_SL_35_JERUP","Tranche3_ttbar_SL_35_JERUP.root"),
("Tranche3_ttbar_SL_35_JESDOWN","Tranche3_ttbar_SL_35_JESDOWN.root"),
("Tranche3_ttbar_SL_35_JESUP","Tranche3_ttbar_SL_35_JESUP.root"),
("Tranche3_ttbar_SL_35_nominal","Tranche3_ttbar_SL_35_nominal.root"),
("Tranche3_ttbar_SL_36_JERDOWN","Tranche3_ttbar_SL_36_JERDOWN.root"),
("Tranche3_ttbar_SL_36_JERUP","Tranche3_ttbar_SL_36_JERUP.root"),
("Tranche3_ttbar_SL_36_JESDOWN","Tranche3_ttbar_SL_36_JESDOWN.root"),
("Tranche3_ttbar_SL_36_JESUP","Tranche3_ttbar_SL_36_JESUP.root"),
("Tranche3_ttbar_SL_36_nominal","Tranche3_ttbar_SL_36_nominal.root"),
("Tranche3_ttbar_SL_37_JERDOWN","Tranche3_ttbar_SL_37_JERDOWN.root"),
("Tranche3_ttbar_SL_37_JERUP","Tranche3_ttbar_SL_37_JERUP.root"),
("Tranche3_ttbar_SL_37_JESDOWN","Tranche3_ttbar_SL_37_JESDOWN.root"),
("Tranche3_ttbar_SL_37_JESUP","Tranche3_ttbar_SL_37_JESUP.root"),
("Tranche3_ttbar_SL_37_nominal","Tranche3_ttbar_SL_37_nominal.root"),
("Tranche3_ttbar_SL_38_JERDOWN","Tranche3_ttbar_SL_38_JERDOWN.root"),
("Tranche3_ttbar_SL_38_JERUP","Tranche3_ttbar_SL_38_JERUP.root"),
("Tranche3_ttbar_SL_38_JESDOWN","Tranche3_ttbar_SL_38_JESDOWN.root"),
("Tranche3_ttbar_SL_38_JESUP","Tranche3_ttbar_SL_38_JESUP.root"),
("Tranche3_ttbar_SL_38_nominal","Tranche3_ttbar_SL_38_nominal.root"),
("Tranche3_ttbar_SL_39_JERDOWN","Tranche3_ttbar_SL_39_JERDOWN.root"),
("Tranche3_ttbar_SL_39_JERUP","Tranche3_ttbar_SL_39_JERUP.root"),
("Tranche3_ttbar_SL_39_JESDOWN","Tranche3_ttbar_SL_39_JESDOWN.root"),
("Tranche3_ttbar_SL_39_JESUP","Tranche3_ttbar_SL_39_JESUP.root"),
("Tranche3_ttbar_SL_39_nominal","Tranche3_ttbar_SL_39_nominal.root"),
("Tranche3_ttbar_SL_0_JERDOWN","Tranche3_ttbar_SL_0_JERDOWN.root"),
("Tranche3_ttbar_SL_0_JERUP","Tranche3_ttbar_SL_0_JERUP.root"),
("Tranche3_ttbar_SL_0_JESDOWN","Tranche3_ttbar_SL_0_JESDOWN.root"),
("Tranche3_ttbar_SL_0_JESUP","Tranche3_ttbar_SL_0_JESUP.root"),
("Tranche3_ttbar_SL_0_nominal","Tranche3_ttbar_SL_0_nominal.root"),
("Tranche3_ttbar_SL_1_JERDOWN","Tranche3_ttbar_SL_1_JERDOWN.root"),
("Tranche3_ttbar_SL_1_JERUP","Tranche3_ttbar_SL_1_JERUP.root"),
("Tranche3_ttbar_SL_1_JESDOWN","Tranche3_ttbar_SL_1_JESDOWN.root"),
("Tranche3_ttbar_SL_1_JESUP","Tranche3_ttbar_SL_1_JESUP.root"),
("Tranche3_ttbar_SL_1_nominal","Tranche3_ttbar_SL_1_nominal.root"),
("Tranche3_ttbar_SL_21_JERDOWN","Tranche3_ttbar_SL_21_JERDOWN.root"),
("Tranche3_ttbar_SL_21_JERUP","Tranche3_ttbar_SL_21_JERUP.root"),
("Tranche3_ttbar_SL_21_JESDOWN","Tranche3_ttbar_SL_21_JESDOWN.root"),
("Tranche3_ttbar_SL_21_JESUP","Tranche3_ttbar_SL_21_JESUP.root"),
("Tranche3_ttbar_SL_21_nominal","Tranche3_ttbar_SL_21_nominal.root"),
("Tranche3_ttbar_SL_22_JERDOWN","Tranche3_ttbar_SL_22_JERDOWN.root"),
("Tranche3_ttbar_SL_22_JERUP","Tranche3_ttbar_SL_22_JERUP.root"),
("Tranche3_ttbar_SL_22_JESDOWN","Tranche3_ttbar_SL_22_JESDOWN.root"),
("Tranche3_ttbar_SL_22_JESUP","Tranche3_ttbar_SL_22_JESUP.root"),
("Tranche3_ttbar_SL_22_nominal","Tranche3_ttbar_SL_22_nominal.root"),
("Tranche3_ttbar_SL_23_JERDOWN","Tranche3_ttbar_SL_23_JERDOWN.root"),
("Tranche3_ttbar_SL_23_JERUP","Tranche3_ttbar_SL_23_JERUP.root"),
("Tranche3_ttbar_SL_23_JESDOWN","Tranche3_ttbar_SL_23_JESDOWN.root"),
("Tranche3_ttbar_SL_23_JESUP","Tranche3_ttbar_SL_23_JESUP.root"),
("Tranche3_ttbar_SL_23_nominal","Tranche3_ttbar_SL_23_nominal.root"),
("Tranche3_ttbar_SL_24_JERDOWN","Tranche3_ttbar_SL_24_JERDOWN.root"),
("Tranche3_ttbar_SL_24_JERUP","Tranche3_ttbar_SL_24_JERUP.root"),
("Tranche3_ttbar_SL_24_JESDOWN","Tranche3_ttbar_SL_24_JESDOWN.root"),
("Tranche3_ttbar_SL_24_JESUP","Tranche3_ttbar_SL_24_JESUP.root"),
("Tranche3_ttbar_SL_24_nominal","Tranche3_ttbar_SL_24_nominal.root"),
("Tranche3_ttbar_SL_25_JERDOWN","Tranche3_ttbar_SL_25_JERDOWN.root"),
("Tranche3_ttbar_SL_25_JERUP","Tranche3_ttbar_SL_25_JERUP.root"),
("Tranche3_ttbar_SL_25_JESDOWN","Tranche3_ttbar_SL_25_JESDOWN.root"),
("Tranche3_ttbar_SL_25_JESUP","Tranche3_ttbar_SL_25_JESUP.root"),
("Tranche3_ttbar_SL_25_nominal","Tranche3_ttbar_SL_25_nominal.root"),
("Tranche3_ttbar_SL_26_JERDOWN","Tranche3_ttbar_SL_26_JERDOWN.root"),
("Tranche3_ttbar_SL_26_JERUP","Tranche3_ttbar_SL_26_JERUP.root"),
("Tranche3_ttbar_SL_26_JESDOWN","Tranche3_ttbar_SL_26_JESDOWN.root"),
("Tranche3_ttbar_SL_26_JESUP","Tranche3_ttbar_SL_26_JESUP.root"),
("Tranche3_ttbar_SL_26_nominal","Tranche3_ttbar_SL_26_nominal.root"),
("Tranche3_ttbar_SL_27_JERDOWN","Tranche3_ttbar_SL_27_JERDOWN.root"),
("Tranche3_ttbar_SL_27_JERUP","Tranche3_ttbar_SL_27_JERUP.root"),
("Tranche3_ttbar_SL_27_JESDOWN","Tranche3_ttbar_SL_27_JESDOWN.root"),
("Tranche3_ttbar_SL_27_JESUP","Tranche3_ttbar_SL_27_JESUP.root"),
("Tranche3_ttbar_SL_27_nominal","Tranche3_ttbar_SL_27_nominal.root"),
("Tranche3_ttbar_SL_28_JERDOWN","Tranche3_ttbar_SL_28_JERDOWN.root"),
("Tranche3_ttbar_SL_28_JERUP","Tranche3_ttbar_SL_28_JERUP.root"),
("Tranche3_ttbar_SL_28_JESDOWN","Tranche3_ttbar_SL_28_JESDOWN.root"),
("Tranche3_ttbar_SL_28_JESUP","Tranche3_ttbar_SL_28_JESUP.root"),
("Tranche3_ttbar_SL_28_nominal","Tranche3_ttbar_SL_28_nominal.root"),
("Tranche3_ttbar_SL_29_JERDOWN","Tranche3_ttbar_SL_29_JERDOWN.root"),
("Tranche3_ttbar_SL_29_JERUP","Tranche3_ttbar_SL_29_JERUP.root"),
("Tranche3_ttbar_SL_29_JESDOWN","Tranche3_ttbar_SL_29_JESDOWN.root"),
("Tranche3_ttbar_SL_29_JESUP","Tranche3_ttbar_SL_29_JESUP.root"),
("Tranche3_ttbar_SL_29_nominal","Tranche3_ttbar_SL_29_nominal.root"),
("Tranche3_ttbar_SL_30_JERDOWN","Tranche3_ttbar_SL_30_JERDOWN.root"),

    ]
   
    samples_events = []
    for name, samp in samples:
        print name
        samples_events += [(
            name,
            pref + samp,
            genSplitting(pref + samp, 200, "samples/kitnewttsl/{0}.txt".format(name))
        )]

    sample_file = open("samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

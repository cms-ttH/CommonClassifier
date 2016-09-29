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
("ttbar_incl_All_nominal","ttbar_incl_All_nominal.root"),
("ttbar_incl_All_JESUP","ttbar_incl_All_JESUP.root"),
("ttbar_incl_All_JESDOWN","ttbar_incl_All_JESDOWN.root"),
("ttbar_incl_All_JERUP","ttbar_incl_All_JERUP.root"),
("ttbar_incl_All_JERDOWN","ttbar_incl_All_JERDOWN.root"),

      #("ttHbb_nominal","ttHbb_nominal.root"),
#("ttHnonbb_nominal","ttHnonbb_nominal.root"),
#("Tranche3_ttHbb_nominal","Tranche3_ttHbb_nominal.root"),
#("Tranche3_ttHnonbb_nominal","Tranche3_ttHnonbb_nominal.root"),
#("ttW_JetToLNu_nominal","ttW_JetToLNu_nominal.root"),
#("ttW_JetToQQ_nominal","ttW_JetToQQ_nominal.root"),
#("ttZ_ToQQ_nominal","ttZ_ToQQ_nominal.root"),
#("Zjets_m50toInf_nominal","Zjets_m50toInf_nominal.root"),
#("WW_nominal","WW_nominal.root"),
#("WZ_nominal","WZ_nominal.root"),
#("ZZ_nominal","ZZ_nominal.root"),
#("WJets-HT-800-1200_nominal","WJets-HT-800-1200_nominal.root"),
#("WJets-HT-600-800_nominal","WJets-HT-600-800_nominal.root"),
#("WJets-HT-400-600_nominal","WJets-HT-400-600_nominal.root"),
#("WJets-HT-2500-Inf_nominal","WJets-HT-2500-Inf_nominal.root"),
#("WJets-HT-1200-2500_nominal","WJets-HT-1200-2500_nominal.root"),
#("WJets-HT-100-200_nominal","WJets-HT-100-200_nominal.root"),
#("st_tchan_nominal","st_tchan_nominal.root"),
#("stbar_tchan_nominal","stbar_tchan_nominal.root"),
#("st_tWchan_nominal","st_tWchan_nominal.root"),
#("stbar_tWchan_nominal","stbar_tWchan_nominal.root"),
#("stbar_s-channel_nominal","stbar_s-channel_nominal.root"),
#("el_data_nominal","el_data_nominal.root"),
#("mu_data_nominal","mu_data_nominal.root"),
#("ttHbb_JESUP","ttHbb_JESUP.root"),
#("ttHnonbb_JESUP","ttHnonbb_JESUP.root"),
#("Tranche3_ttHbb_JESUP","Tranche3_ttHbb_JESUP.root"),
#("Tranche3_ttHnonbb_JESUP","Tranche3_ttHnonbb_JESUP.root"),
#("ttW_JetToLNu_JESUP","ttW_JetToLNu_JESUP.root"),
#("ttW_JetToQQ_JESUP","ttW_JetToQQ_JESUP.root"),
#("ttZ_ToQQ_JESUP","ttZ_ToQQ_JESUP.root"),
#("Zjets_m50toInf_JESUP","Zjets_m50toInf_JESUP.root"),
#("WW_JESUP","WW_JESUP.root"),
#("WZ_JESUP","WZ_JESUP.root"),
#("ZZ_JESUP","ZZ_JESUP.root"),
#("WJets-HT-800-1200_JESUP","WJets-HT-800-1200_JESUP.root"),
#("WJets-HT-600-800_JESUP","WJets-HT-600-800_JESUP.root"),
#("WJets-HT-400-600_JESUP","WJets-HT-400-600_JESUP.root"),
#("WJets-HT-2500-Inf_JESUP","WJets-HT-2500-Inf_JESUP.root"),
#("WJets-HT-1200-2500_JESUP","WJets-HT-1200-2500_JESUP.root"),
#("WJets-HT-100-200_JESUP","WJets-HT-100-200_JESUP.root"),
#("st_tchan_JESUP","st_tchan_JESUP.root"),
#("stbar_tchan_JESUP","stbar_tchan_JESUP.root"),
#("st_tWchan_JESUP","st_tWchan_JESUP.root"),
#("stbar_tWchan_JESUP","stbar_tWchan_JESUP.root"),
#("stbar_s-channel_JESUP","stbar_s-channel_JESUP.root"),
#("ttHbb_JESDOWN","ttHbb_JESDOWN.root"),
#("ttHnonbb_JESDOWN","ttHnonbb_JESDOWN.root"),
#("Tranche3_ttHbb_JESDOWN","Tranche3_ttHbb_JESDOWN.root"),
#("Tranche3_ttHnonbb_JESDOWN","Tranche3_ttHnonbb_JESDOWN.root"),
#("ttW_JetToLNu_JESDOWN","ttW_JetToLNu_JESDOWN.root"),
#("ttW_JetToQQ_JESDOWN","ttW_JetToQQ_JESDOWN.root"),
#("ttZ_ToQQ_JESDOWN","ttZ_ToQQ_JESDOWN.root"),
#("Zjets_m50toInf_JESDOWN","Zjets_m50toInf_JESDOWN.root"),
#("WW_JESDOWN","WW_JESDOWN.root"),
#("WZ_JESDOWN","WZ_JESDOWN.root"),
#("ZZ_JESDOWN","ZZ_JESDOWN.root"),
#("WJets-HT-800-1200_JESDOWN","WJets-HT-800-1200_JESDOWN.root"),
#("WJets-HT-600-800_JESDOWN","WJets-HT-600-800_JESDOWN.root"),
#("WJets-HT-400-600_JESDOWN","WJets-HT-400-600_JESDOWN.root"),
#("WJets-HT-2500-Inf_JESDOWN","WJets-HT-2500-Inf_JESDOWN.root"),
#("WJets-HT-1200-2500_JESDOWN","WJets-HT-1200-2500_JESDOWN.root"),
#("WJets-HT-100-200_JESDOWN","WJets-HT-100-200_JESDOWN.root"),
#("st_tchan_JESDOWN","st_tchan_JESDOWN.root"),
#("stbar_tchan_JESDOWN","stbar_tchan_JESDOWN.root"),
#("st_tWchan_JESDOWN","st_tWchan_JESDOWN.root"),
#("stbar_tWchan_JESDOWN","stbar_tWchan_JESDOWN.root"),
#("stbar_s-channel_JESDOWN","stbar_s-channel_JESDOWN.root"),
#("ttHbb_JERUP","ttHbb_JERUP.root"),
#("ttHnonbb_JERUP","ttHnonbb_JERUP.root"),
#("Tranche3_ttHbb_JERUP","Tranche3_ttHbb_JERUP.root"),
#("Tranche3_ttHnonbb_JERUP","Tranche3_ttHnonbb_JERUP.root"),
#("ttW_JetToLNu_JERUP","ttW_JetToLNu_JERUP.root"),
#("ttW_JetToQQ_JERUP","ttW_JetToQQ_JERUP.root"),
#("ttZ_ToQQ_JERUP","ttZ_ToQQ_JERUP.root"),
#("Zjets_m50toInf_JERUP","Zjets_m50toInf_JERUP.root"),
#("WW_JERUP","WW_JERUP.root"),
#("WZ_JERUP","WZ_JERUP.root"),
#("ZZ_JERUP","ZZ_JERUP.root"),
#("WJets-HT-800-1200_JERUP","WJets-HT-800-1200_JERUP.root"),
#("WJets-HT-600-800_JERUP","WJets-HT-600-800_JERUP.root"),
#("WJets-HT-400-600_JERUP","WJets-HT-400-600_JERUP.root"),
#("WJets-HT-2500-Inf_JERUP","WJets-HT-2500-Inf_JERUP.root"),
#("WJets-HT-1200-2500_JERUP","WJets-HT-1200-2500_JERUP.root"),
#("WJets-HT-100-200_JERUP","WJets-HT-100-200_JERUP.root"),
#("st_tchan_JERUP","st_tchan_JERUP.root"),
#("stbar_tchan_JERUP","stbar_tchan_JERUP.root"),
#("st_tWchan_JERUP","st_tWchan_JERUP.root"),
#("stbar_tWchan_JERUP","stbar_tWchan_JERUP.root"),
#("stbar_s-channel_JERUP","stbar_s-channel_JERUP.root"),
#("ttHbb_JERDOWN","ttHbb_JERDOWN.root"),
#("ttHnonbb_JERDOWN","ttHnonbb_JERDOWN.root"),
#("Tranche3_ttHbb_JERDOWN","Tranche3_ttHbb_JERDOWN.root"),
#("Tranche3_ttHnonbb_JERDOWN","Tranche3_ttHnonbb_JERDOWN.root"),
#("ttW_JetToLNu_JERDOWN","ttW_JetToLNu_JERDOWN.root"),
#("ttW_JetToQQ_JERDOWN","ttW_JetToQQ_JERDOWN.root"),
#("ttZ_ToQQ_JERDOWN","ttZ_ToQQ_JERDOWN.root"),
#("Zjets_m50toInf_JERDOWN","Zjets_m50toInf_JERDOWN.root"),
#("WW_JERDOWN","WW_JERDOWN.root"),
#("WZ_JERDOWN","WZ_JERDOWN.root"),
#("ZZ_JERDOWN","ZZ_JERDOWN.root"),
#("WJets-HT-800-1200_JERDOWN","WJets-HT-800-1200_JERDOWN.root"),
#("WJets-HT-600-800_JERDOWN","WJets-HT-600-800_JERDOWN.root"),
#("WJets-HT-400-600_JERDOWN","WJets-HT-400-600_JERDOWN.root"),
#("WJets-HT-2500-Inf_JERDOWN","WJets-HT-2500-Inf_JERDOWN.root"),
#("WJets-HT-1200-2500_JERDOWN","WJets-HT-1200-2500_JERDOWN.root"),
#("WJets-HT-100-200_JERDOWN","WJets-HT-100-200_JERDOWN.root"),
#("st_tchan_JERDOWN","st_tchan_JERDOWN.root"),
#("stbar_tchan_JERDOWN","stbar_tchan_JERDOWN.root"),
#("st_tWchan_JERDOWN","st_tWchan_JERDOWN.root"),
#("stbar_tWchan_JERDOWN","stbar_tWchan_JERDOWN.root"),
#("stbar_s-channel_JERDOWN","stbar_s-channel_JERDOWN.root"),

    ]
   
    samples_events = []
    for name, samp in samples:
        print name
        samples_events += [(
            name,
            pref + samp,
            genSplitting(pref + samp, 400, "samples/kit/{0}.txt".format(name))
        )]

    sample_file = open("samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

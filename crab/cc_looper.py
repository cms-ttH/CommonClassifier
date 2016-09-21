import ROOT, json, sys
import numpy as np
ROOT.gSystem.Load("libTTHCommonClassifier")

CvectorLorentz = getattr(ROOT, "std::vector<TLorentzVector>")
Cvectordouble = getattr(ROOT, "std::vector<double>")
CvectorJetType = getattr(ROOT, "std::vector<MEMClassifier::JetType>")

def vec_from_list(vec_type, src):
    """
    Creates a std::vector<T> from a python list.
    vec_type (ROOT type): vector datatype, ex: std::vector<double>
    src (iterable): python list
    """
    v = vec_type()
    for item in src:
        v.push_back(item)
    return v

def main(infile_name, firstEvent, lastEvent, outfile_name, conf):
    """
    Processes an input file with the CommonClassifier, saving the output in a file.
    infile_name (string): path to input file, can be root://, file://, ...
    firstEvent (int): first event to process (inclusive)
    lastEvent (int): last event to process (exclusive)
    outfile_name (string): output file name, must be writeable
    conf (dict): configuration dictionary
    """
    firstEvent = int(firstEvent)
    lastEvent = int(lastEvent)

    #create the MEM classifier, specifying the verbosity and b-tagger type
    cls_mem = ROOT.MEMClassifier(1, conf["btag"])
    cls_bdt = ROOT.BDTClassifier()

    #one file
    if isinstance(infile_name, basestring):
        infile = ROOT.TFile.Open(infile_name)
        tree = infile.Get("tree")
    #many files
    else:
        tree = ROOT.TChain("tree")
        for fi in infile_name:
            tree.AddFile(fi)

    #create the output
    outfile_name = outfile_name
    outfile = ROOT.TFile(outfile_name, "RECREATE")

    #create the output TTree structure
    outtree = ROOT.TTree("tree", "CommonClassifier output tree")
    bufs = {}
    bufs["event"] = np.zeros(1, dtype=np.int64)
    bufs["run"] = np.zeros(1, dtype=np.int64)
    bufs["lumi"] = np.zeros(1, dtype=np.int64)
    bufs["systematic"] = np.zeros(1, dtype=np.int64)
    bufs["mem_p"] = np.zeros(1, dtype=np.float64)
    bufs["mem_p_sig"] = np.zeros(1, dtype=np.float64)
    bufs["mem_p_bkg"] = np.zeros(1, dtype=np.float64)
    bufs["blr_4b"] = np.zeros(1, dtype=np.float64)
    bufs["blr_2b"] = np.zeros(1, dtype=np.float64)
    bufs["bdt"] = np.zeros(1, dtype=np.float64)
    
    outtree.Branch("event", bufs["event"], "event/L")
    outtree.Branch("run", bufs["run"], "run/L")
    outtree.Branch("lumi", bufs["lumi"], "lumi/L")
    outtree.Branch("systematic", bufs["systematic"], "systematic/L")

    outtree.Branch("mem_p", bufs["mem_p"], "mem_p/D")
    outtree.Branch("mem_p_sig", bufs["mem_p_sig"], "mem_p_sig/D")
    outtree.Branch("mem_p_bkg", bufs["mem_p_bkg"], "mem_p_bkg/D")
    
    outtree.Branch("blr_4b", bufs["blr_4b"], "blr_4b/D")
    outtree.Branch("blr_2b", bufs["blr_2b"], "blr_2b/D")
    outtree.Branch("bdt", bufs["bdt"], "bdt/D")

    print "looping over events {0} to {1}".format(firstEvent, lastEvent)
    for iEv in range(firstEvent, lastEvent):
        tree.GetEntry(iEv)
        
        bufs["event"][0] = tree.event
        bufs["run"][0] = tree.run
        bufs["lumi"][0] = tree.lumi
        bufs["systematic"][0] = tree.systematic
    
        njets = tree.njets
        print "njets={0}".format(njets)

        #process jets
        jets_p4 = CvectorLorentz()
        jets_pt = list(tree.jet_pt)
        jets_eta = list(tree.jet_eta)
        jets_phi = list(tree.jet_phi)
        jets_mass = list(tree.jet_mass)
        for iJet in range(njets):
            v = ROOT.TLorentzVector()
            v.SetPtEtaPhiM(jets_pt[iJet], jets_eta[iJet], jets_phi[iJet], jets_mass[iJet])
            jets_p4.push_back(v)
        jets_csv = vec_from_list(Cvectordouble, list(tree.jet_csv))
        jets_cmva = vec_from_list(Cvectordouble, list(tree.jet_cmva))
        jets_type = vec_from_list(CvectorJetType, list(tree.jet_type))
   
        #process leptons
        nleps = tree.nleps
        leps_p4 = CvectorLorentz()
        leps_pt = list(tree.lep_pt)
        leps_eta = list(tree.lep_eta)
        leps_phi = list(tree.lep_phi)
        leps_mass = list(tree.lep_mass)
        leps_charge = vec_from_list(Cvectordouble, list(tree.lep_charge))
        for ilep in range(nleps):
            v = ROOT.TLorentzVector()
            v.SetPtEtaPhiM(leps_pt[ilep], leps_eta[ilep], leps_phi[ilep], leps_mass[ilep])
            leps_p4.push_back(v)
    
        #process MET
        met = ROOT.TLorentzVector()
        met.SetPtEtaPhiM(
            tree.met_pt,
            0,
            tree.met_phi,
            0
        )

        #choose which b-tagger to use
        jets_tagger = None
        if conf["btag"] == "btagCSV_":
            jets_tagger = jets_csv
        elif conf["btag"] == "btagBDT_":
            jets_tagger = jets_cmva
       
        #calculate the MEM
        ret = cls_mem.GetOutput(
            leps_p4,
            leps_charge,
            jets_p4,
            jets_tagger,
            jets_type,
            met,
        )

        #save the output
        bufs["mem_p"][0] = ret.p
        bufs["mem_p_sig"][0] = ret.p_sig
        bufs["mem_p_bkg"][0] = ret.p_bkg
        bufs["blr_4b"][0] = ret.blr_4b
        bufs["blr_2b"][0] = ret.blr_2b
       
        loose_jets_p4 = jets_p4
        loose_jets_csv = jets_csv

        ret_bdt = cls_bdt.GetBDTOutput(
            leps_p4,
            jets_p4,
            jets_csv,
            loose_jets_p4,
            loose_jets_csv,
            met,
        )
        bufs["bdt"][0] = ret_bdt
        outtree.Fill()
    
    outfile.Write()
    outfile.Close()

if __name__ == "__main__":

    #configurations go here
    confs = {
        "CSV": {
            "btag": "btagCSV_",
        },
        "CMVA": {
            "btag": "btagBDT_",
        },
    }

    import argparse
    parser = argparse.ArgumentParser(description='Calculates the CommonClassifier on a common input ntuple')
    parser.add_argument('--infile', action="store", nargs='+', help="Input file name (PFN)")
    parser.add_argument('--firstEvent', action="store", help="first event (by index) in tree to use", type=int)
    parser.add_argument('--lastEvent', action="store", help="last event (by index) in tree to use, exclusive (!)", type=int)
    parser.add_argument('--maxEvents', action="store", help="total number of events to process", type=int, required=False)
    parser.add_argument('--outfile', action="store", help="output file name, must be writeable")
    parser.add_argument('--conf', type=str, choices=sorted(confs.keys()), default="CSV")
    args = parser.parse_args()
    conf = confs[args.conf]

    #use maxEvents if it was specified
    if not args.maxEvents is None:
        args.lastEvent = args.firstEvent + args.maxEvents
    main(args.infile, args.firstEvent, args.lastEvent, args.outfile, conf)

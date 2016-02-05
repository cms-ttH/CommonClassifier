import ROOT, json
ROOT.gSystem.Load("libTTHCommonClassifier")
CvectorLorentz = getattr(ROOT, "std::vector<TLorentzVector>")
Cvectordouble = getattr(ROOT, "std::vector<double>")

f = ROOT.MEMClassifier()

inf = open("root/events.json")
data = inf.read()
events = data.split("\n\n\n")[:-1]

def make_p4(pt, eta, phi, m):
    v = ROOT.TLorentzVector()
    v.SetPtEtaPhiM(pt, eta, phi, m)
    return v

for ev in events:
    jsev = json.loads(ev)
    jets_p4 = jsev["input"]["selectedJetsP4"]
    jets_csv = jsev["input"]["selectedJetsCSV"]
    jets_btag = jsev["input"]["selectedJetsBTag"]

    c_jets_p4 = CvectorLorentz()
    c_jets_csv = Cvectordouble()
    for ij, j in enumerate(jets_p4):
        c_jets_p4.push_back(make_p4(*j))
        c_jets_csv.push_back(jets_csv[ij])

    c_leps_p4 = CvectorLorentz()
    c_leps_charge = Cvectordouble()
    leps_p4 = jsev["input"]["selectedLeptonsP4"]
    leps_charge = jsev["input"]["selectedLeptonsCharge"]
    for il, l in enumerate(leps_p4):
        c_leps_p4.push_back(make_p4(*l))
        c_leps_charge.push_back(leps_charge[il])

    met_p4 = make_p4(jsev["input"]["metP4"][0], 0.0, jsev["input"]["metP4"][1], 0.0)

    c_loosejets_p4 = CvectorLorentz()
    c_loosejets_csv = Cvectordouble()
    if jsev["event"]["cat"].startswith("sl"):
        print "tthbb13 code blr=", jsev["event"]["blr"], "mem=", jsev["output"]["p_tth"], jsev["output"]["p_ttbb"], jsev["output"]["p"]

        ret = f.GetOutput(c_leps_p4, c_leps_charge, c_jets_p4, c_jets_csv, c_loosejets_p4, c_loosejets_csv, met_p4)
        print "mem.py blr=", ret.blr_4b/(ret.blr_4b + ret.blr_2b), "mem=", ret.p_sig, ret.p_bkg, ret.p

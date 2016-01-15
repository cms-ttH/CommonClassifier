#include "TTH/CommonClassifier/interface/MEMClassifier.h"

MEMResult MEMClassifier::GetOutput(
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4
) {
    //integrand->next_event();
    if (selectedLeptonP4.size() != 1) {
        throw std::runtime_error("Expected a single-lepton event");
    }
    
    //store MEM objects
    std::vector<MEM::Object*> objs;

    std::vector<unsigned int> best_perm;
    double blr_4b_2b = GetBTagLikelihoodRatio(selectedJetP4, selectedJetCSV, best_perm);
    std::cout << "blr=" << blr_4b_2b << " perm ";
    if(std::isnan(blr_4b_2b)){
	MEMResult res;
	res.p=-1.;
	res.p_sig=-1.;
	res.p_bkg=-1.;
	res.p_err_sig=-1.;
	res.p_err_bkg=-1.;
	res.n_perm_sig=-1.;
	res.n_perm_bkg=-1.;
	return res;
    }
    for (auto i : best_perm) {
        std::cout << i << " ";
    }
    std::cout << endl;
    
    std::vector<MEM::Object*> tagged;
    std::vector<MEM::Object*> untagged;
    //use up to numMaxJets jets
    for (unsigned int ij=0; ij<std::min(selectedJetP4.size(), numMaxJets); ij++) {
        TLorentzVector p4 = selectedJetP4.at(ij);
        assert(p4.Pt() > 0);
        //Check if this jet was in the best 4b permutation
        auto last = best_perm.begin() + 4;
        bool is_btagged = std::find(best_perm.begin(), last, ij) != last;

        MEM::Object* jet = make_jet(
            p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), is_btagged ? 1.0 : 0.0
        );
        if (is_btagged) {
            tagged.push_back(jet);
        } else {
            untagged.push_back(jet);
        }
        //objs.push_back(jet);
        //integrand->push_back_object(jet);
    }
    for (auto* jet : tagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
    }

    //Ignore the untagged jets
    //for (auto* jet : untagged) {
    //    objs.push_back(jet);
    //    integrand->push_back_object(jet);
    //}

    for (unsigned int il=0; il < selectedLeptonP4.size(); il++) {
        TLorentzVector lep_p4 = selectedLeptonP4.at(il);
        assert(lep_p4.Pt() > 0);
        MEM::Object* lep = make_lepton(lep_p4.Pt(), lep_p4.Eta(), lep_p4.Phi(), lep_p4.M(), selectedLeptonCharge[il]);
        objs.push_back(lep);
        integrand->push_back_object(lep);
    }

    assert(metP4.Pt() > 0);
    MEM::Object met(metP4, MEM::ObjectType::MET );
    integrand->push_back_object(&met);
    integrand->set_cfg(cfg);
    integrand->set_permutation_strategy
    ({MEM::Permutations::BTagged,
      MEM::Permutations::QUntagged,
      MEM::Permutations::QQbarBBbarSymmetry
    });

    MEM::MEMOutput res_sig = integrand->run( MEM::FinalState::LH, MEM::Hypothesis::TTH, {MEM::PSVar::cos_q1, MEM::PSVar::phi_q1, MEM::PSVar::cos_qbar1, MEM::PSVar::phi_qbar1});
    MEM::MEMOutput res_bkg = integrand->run( MEM::FinalState::LH, MEM::Hypothesis::TTBB, {MEM::PSVar::cos_q1, MEM::PSVar::phi_q1, MEM::PSVar::cos_qbar1, MEM::PSVar::phi_qbar1});

    for (auto* obj : objs) {
        delete obj;
    }
    integrand->next_event();

    MEMResult res;
    res.p_sig = res_sig.p;
    res.p_bkg = res_bkg.p;
    res.p_err_sig = res_sig.p_err;
    res.p_err_bkg = res_bkg.p_err;
    res.n_perm_sig = res_sig.num_perm;
    res.n_perm_bkg = res_bkg.num_perm;
    res.p = res_sig.p / (res_sig.p + 0.02*res_bkg.p);
    return res;
}
  
MEM::Object* MEMClassifier::make_jet(double pt, double eta, double phi, double mass, double csv) const {
    TLorentzVector lv;
    lv.SetPtEtaPhiM(pt, eta, phi, mass);
    MEM::Object* obj = new MEM::Object(lv, MEM::ObjectType::Jet);
    obj->addObs( MEM::Observable::BTAG, csv); // 0 - jet is assumed to be from a light quark, 1 - a b quark
    obj->addObs( MEM::Observable::PDGID, 0);  // currently not used
    // attach the transfer functions corresponding to the jet
    obj->addTransferFunction(MEM::TFType::bReco, getTransferFunction("b", lv.Eta()));
    obj->addTransferFunction(MEM::TFType::qReco, getTransferFunction("l", lv.Eta()));
    return obj;
}

MEM::Object* MEMClassifier::make_lepton(double pt, double eta, double phi, double mass, double charge) const {
    TLorentzVector lv;
    lv.SetPtEtaPhiM(pt, eta, phi, mass);
    MEM::Object* obj = new MEM::Object(lv, MEM::ObjectType::Lepton );
    obj->addObs( MEM::Observable::CHARGE, charge);
    return obj;
}

// Returns the transfer function corresponding to a jet flavour and eta
TF1* MEMClassifier::getTransferFunction(const char* flavour, double eta) const {
    int etabin = 0;
    if (std::abs(eta) > 1.0) {
        etabin = 1;
    }
    stringstream ss;
    ss << "tf_" << flavour << "_etabin" << etabin;
    const char* fname = ss.str().c_str();
    TF1* tf = (TF1*)(transfers->Get(fname));
    if (tf == nullptr) {
        cerr << "could not get transfer function " << fname << endl;
        cerr << flush;
        throw std::exception();
    }
    tf->SetNpx(10000);
    tf->SetRange(0, 500);
    return tf;
}

MEMClassifier::MEMClassifier() : cfg(MEM::MEMConfig()) {

    const string cmssw_path = string(std::getenv("CMSSW_BASE"));
    const char* transfers_path = (
        string("file://") +
        cmssw_path +
        string("/src/TTH/CommonClassifier/root/transfer.root")
    ).c_str();
    cout << "opening " << transfers_path << endl;
    transfers = new TFile(transfers_path);
    assert(transfers != nullptr);
    cfg.defaultCfg();
    cfg.transfer_function_method = MEM::TFMethod::External;
    //Transfer functions for jet reconstruction efficiency
    cfg.set_tf_global(MEM::TFType::bLost, 0, getTransferFunction("beff", 0.0));
    cfg.set_tf_global(MEM::TFType::bLost, 1, getTransferFunction("beff", 2.0));
    cfg.set_tf_global(MEM::TFType::qLost, 0, getTransferFunction("leff", 0.0));
    cfg.set_tf_global(MEM::TFType::qLost, 1, getTransferFunction("leff", 2.0));

    integrand = new MEM::Integrand(
        0
        //MEM::DebugVerbosity::output
        //|MEM::DebugVerbosity::init
        //|MEM::DebugVerbosity::input
        //|MEM::DebugVerbosity::init_more
        //|MEM::DebugVerbosity::integration
        ,cfg
    );
    integrand->set_cfg(cfg);

    const char* btagfile_path = (
        string("file://") +
        cmssw_path +
        string("/src/TTH/CommonClassifier/root/ControlPlotsV14.root")
    ).c_str();
    cout << "opening " << btagfile_path << endl;
    btagfile = new TFile(btagfile_path);
    assert(btagfile != nullptr);

    blr = new MEM::JetLikelihood();
    
}

TH3D* MEMClassifier::GetBTagPDF(const char* flavour) {
    TH3D* ret = nullptr;
    ret = (TH3D*)(btagfile->Get((string("btagCSV_")+string(flavour)+string("_pt_eta")).c_str()));
    assert(ret != nullptr);
    return ret;
}

double MEMClassifier::GetJetBProbability(const char* flavour, double pt, double eta, double bdisc) {
    TH3D* h = GetBTagPDF(flavour);
    int i = h->FindBin(pt, std::abs(eta), bdisc);
    return h->GetBinContent(i);
}

MEM::JetProbability MEMClassifier::GetJetBProbabilities(
    const TLorentzVector& p4, double bdisc
    ) {
    MEM::JetProbability jp;
    jp.setProbability(MEM::JetInterpretation::b, GetJetBProbability("b", p4.Pt(), p4.Eta(), bdisc));
    jp.setProbability(MEM::JetInterpretation::c, GetJetBProbability("c", p4.Pt(), p4.Eta(), bdisc));
    jp.setProbability(MEM::JetInterpretation::l, GetJetBProbability("l", p4.Pt(), p4.Eta(), bdisc));
    return jp;
}

double MEMClassifier::GetBTagLikelihoodRatio(
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    std::vector<unsigned int>& out_best_perm
    ) {
    for (unsigned int ij=0; ij < selectedJetP4.size(); ij++) {
        blr->push_back_object(GetJetBProbabilities(selectedJetP4[ij], selectedJetCSV[ij]));
    }

    std::vector<unsigned int> best_perm_4b;
    std::vector<unsigned int> best_perm_2b;
    double P_4b = blr->calcProbability(MEM::JetInterpretation::b, MEM::JetInterpretation::l, 4, best_perm_4b);
    double P_2b = blr->calcProbability(MEM::JetInterpretation::b, MEM::JetInterpretation::l, 2, best_perm_2b);
    out_best_perm = best_perm_4b;
    blr->next_event();

    return P_4b / (P_4b + P_2b);
}

MEMClassifier::~MEMClassifier() {
    delete integrand;
    transfers->Close();
    delete blr;
    btagfile->Close();
}

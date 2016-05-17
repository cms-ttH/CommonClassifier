#include "TTH/CommonClassifier/interface/MEMClassifier.h"

static const double mem_weight = 0.15;

void MEMClassifier::setup_mem(
    const Hypothesis hypo,
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<JetType>& selectedJetType,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4,
    std::vector<MEM::Object*>& objs,
    MEMResult& res
) {

    integrand->next_event();

    integrand->set_cfg(cfg);

    if (hypo==SL_2W2H2T_SJ_RESTPERM){
      integrand->set_permutation_strategy({
	  MEM::Permutations::QQbarBBbarSymmetry,
	  MEM::Permutations::HEPTopTagged
	});
    }
    else{    
      integrand->set_permutation_strategy({
	  MEM::Permutations::QQbarBBbarSymmetry,
	  MEM::Permutations::QUntagged,
	  MEM::Permutations::BTagged,
	});
    }

    switch (hypo) {

    case DEBUG: {
        break;
    }

    case SL_0W2H2T: {
        setup_mem_sl_0w2h2t(selectedLeptonP4,
                            selectedLeptonCharge,
                            selectedJetP4,
                            selectedJetCSV,
                            selectedJetType,
                            looseSelectedJetP4,
                            looseSelectedJetCSV,
                            metP4,
                            objs,
                            res);
        break;
    }

    case SL_2W2H2T: {
        setup_mem_sl_2w2h2t(selectedLeptonP4,
                            selectedLeptonCharge,
                            selectedJetP4,
                            selectedJetCSV,
                            selectedJetType,
                            looseSelectedJetP4,
                            looseSelectedJetCSV,
                            metP4,
                            objs,
                            res);
        break;
    }

    case SL_2W2H2T_SJ: {
        setup_mem_sl_2w2h2t_sj(selectedLeptonP4,
                               selectedLeptonCharge,
                               selectedJetP4,
                               selectedJetCSV,
                               selectedJetType,
                               looseSelectedJetP4,
                               looseSelectedJetCSV,
                               metP4,
                               objs,
                               res);
        break;
    }

    case SL_2W2H2T_SJ_RESTPERM: {
        setup_mem_sl_2w2h2t_sj_restperm(selectedLeptonP4,
					selectedLeptonCharge,
					selectedJetP4,
					selectedJetCSV,
					selectedJetType,
					looseSelectedJetP4,
					looseSelectedJetCSV,
					metP4,
					objs,
					res);
        break;
    }

    case DL_0W2H2T: {
        setup_mem_dl_0w2h2t(selectedLeptonP4,
                            selectedLeptonCharge,
                            selectedJetP4,
                            selectedJetCSV,
                            metP4,
                            objs,
                            res);
        break;
    }

    // Fallback
    default: {
        std::cout << "Warning! Fallback case reached. Invalid MEM Hypo!!!" << std::endl;
        throw 1;
    }

    }

}


void MEMClassifier::setup_mem_sl_0w2h2t(
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<JetType>& selectedJetType,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4,
    std::vector<MEM::Object*>& objs,
    MEMResult& res
) {

    if (selectedLeptonP4.size() != 1) {
        throw std::runtime_error("Expected a single-lepton event");
    }
    if (selectedJetP4.size() != selectedJetCSV.size()) {
        throw std::runtime_error("number of jets and tags should be the same!");
    }
    
    std::vector<unsigned int> best_perm;
    double blr_4b = 0.0;
    double blr_2b = 0.0;

    GetBTagLikelihoodRatio(
        selectedJetP4, selectedJetCSV, best_perm, blr_4b, blr_2b
    );
    assert(best_perm.size() >= 4);

    res.blr_4b = blr_4b;
    res.blr_2b = blr_2b;

    std::vector<MEM::Object*> tagged;
    std::vector<MEM::Object*> untagged;
    //use up to numMaxJets jets
    for (unsigned int ij=0; ij<std::min(selectedJetP4.size(), numMaxJets); ij++) {
        TLorentzVector p4 = selectedJetP4.at(ij);
        assert(p4.Pt() > 0);
        //Check if this jet was in the best 4b permutation, i.e. the first 4 indices of the permutation
        auto last = best_perm.begin() + 4;
        bool is_btagged = std::find(best_perm.begin(), last, ij) != last;

        MEM::Object* jet = make_jet(
                               p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), is_btagged ? 1.0 : 0.0,
                               selectedJetCSV.at(ij),
                               false
                           );
        if (is_btagged) {
            tagged.push_back(jet);
        } else {
            untagged.push_back(jet);
        }
        //objs.push_back(jet);
        //integrand->push_back_object(jet);
    }
    assert(tagged.size() == 4);
    for (auto* jet : tagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    for (unsigned int il=0; il < selectedLeptonP4.size(); il++) {
        TLorentzVector lep_p4 = selectedLeptonP4.at(il);
        assert(lep_p4.Pt() > 0);
        MEM::Object* lep = make_lepton(lep_p4.Pt(), lep_p4.Eta(), lep_p4.Phi(), lep_p4.M(), selectedLeptonCharge[il]);
        objs.push_back(lep);
        integrand->push_back_object(lep);
    }

    assert(metP4.Pt() > 0);
    MEM::Object* met = new MEM::Object(metP4, MEM::ObjectType::MET );
    integrand->push_back_object(met);
}

void MEMClassifier::setup_mem_sl_2w2h2t(
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<JetType>& selectedJetType,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4,
    std::vector<MEM::Object*>& objs,
    MEMResult& res
) {

    if (selectedLeptonP4.size() != 1) {
        throw std::runtime_error("Expected a single-lepton event");
    }

    std::vector<unsigned int> best_perm;
    double blr_4b = 0.0;
    double blr_2b = 0.0;

    GetBTagLikelihoodRatio(
        selectedJetP4, selectedJetCSV, best_perm, blr_4b, blr_2b
    );
    assert(best_perm.size() >= 4);

    res.blr_4b = blr_4b;
    res.blr_2b = blr_2b;

    std::vector<MEM::Object*> tagged;
    std::vector<MEM::Object*> untagged;
    //use up to numMaxJets jets
    for (unsigned int ij=0; ij<std::min(selectedJetP4.size(), numMaxJets); ij++) {
        TLorentzVector p4 = selectedJetP4.at(ij);
        assert(p4.Pt() > 0);
        //Check if this jet was in the best 4b permutation, i.e. the first 4 indices of the permutation
        auto last = best_perm.begin() + 4;
        bool is_btagged = std::find(best_perm.begin(), last, ij) != last;

        MEM::Object* jet = make_jet(
                               p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), is_btagged ? 1.0 : 0.0,
                               selectedJetCSV.at(ij),
                               false
                           );
        if (is_btagged) {
            tagged.push_back(jet);
        } else {
            untagged.push_back(jet);
        }
    }
    assert(tagged.size() == 4);
    for (auto* jet : tagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding tagged jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    assert(untagged.size() >= 2);
    for (auto* jet : untagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding untagged jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    for (unsigned int il=0; il < selectedLeptonP4.size(); il++) {
        TLorentzVector lep_p4 = selectedLeptonP4.at(il);
        assert(lep_p4.Pt() > 0);
        MEM::Object* lep = make_lepton(lep_p4.Pt(), lep_p4.Eta(), lep_p4.Phi(), lep_p4.M(), selectedLeptonCharge[il]);
        objs.push_back(lep);
        integrand->push_back_object(lep);
    }

    assert(metP4.Pt() > 0);
    MEM::Object* met = new MEM::Object(metP4, MEM::ObjectType::MET );
    integrand->push_back_object(met);
}

void MEMClassifier::setup_mem_dl_0w2h2t(
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    TLorentzVector& metP4,
    std::vector<MEM::Object*>& objs,
    MEMResult& res
) {

    if (selectedLeptonP4.size() != 2) {
        throw std::runtime_error("Expected a di-lepton event");
    }

    std::vector<unsigned int> best_perm;
    double blr_4b = 0.0;
    double blr_2b = 0.0;

    GetBTagLikelihoodRatio(
        selectedJetP4, selectedJetCSV, best_perm, blr_4b, blr_2b
    );
    assert(best_perm.size() >= 4);

    res.blr_4b = blr_4b;
    res.blr_2b = blr_2b;

    std::vector<MEM::Object*> tagged;
    std::vector<MEM::Object*> untagged;
    //use up to numMaxJets jets
    for (unsigned int ij=0; ij<std::min(selectedJetP4.size(), numMaxJets); ij++) {
        TLorentzVector p4 = selectedJetP4.at(ij);
        assert(p4.Pt() > 0);
        //Check if this jet was in the best 4b permutation, i.e. the first 4 indices of the permutation
        auto last = best_perm.begin() + 4;
        bool is_btagged = std::find(best_perm.begin(), last, ij) != last;

        MEM::Object* jet = make_jet(
                               p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), is_btagged ? 1.0 : 0.0,
                               selectedJetCSV.at(ij),
                               false
                           );
        if (is_btagged) {
            tagged.push_back(jet);
        } else {
            untagged.push_back(jet);
        }
    }
    assert(tagged.size() == 4);
    for (auto* jet : tagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    for (unsigned int il=0; il < selectedLeptonP4.size(); il++) {
        TLorentzVector lep_p4 = selectedLeptonP4.at(il);
        assert(lep_p4.Pt() > 0);
        MEM::Object* lep = make_lepton(lep_p4.Pt(), lep_p4.Eta(), lep_p4.Phi(), lep_p4.M(), selectedLeptonCharge[il]);
        objs.push_back(lep);
        integrand->push_back_object(lep);
    }

    assert(metP4.Pt() > 0);
    MEM::Object* met = new MEM::Object(metP4, MEM::ObjectType::MET );
    integrand->push_back_object(met);

    integrand->set_permutation_strategy({
        MEM::Permutations::QQbarBBbarSymmetry,
        MEM::Permutations::FirstRankedByBTAG,
    });
}


void MEMClassifier::setup_mem_sl_2w2h2t_sj(
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<JetType>& selectedJetType,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4,
    std::vector<MEM::Object*>& objs,
    MEMResult& res
) {

    if (selectedLeptonP4.size() != 1) {
        throw std::runtime_error("Expected a single-lepton event");
    }

    // Make sure we received a suitable set of input jets
    // Require:
    //  * exactly 6 jets
    //  * 2 light boosted
    //  * 1 b boosted
    //  * 3 resolved

    int n_light_boosted(0), n_b_boosted(0), n_resolved(0);

    assert(selectedJetP4.size() == 6);

    std::vector<MEM::Object*> tagged;
    std::vector<MEM::Object*> untagged;

    for (unsigned int ij=0; ij<selectedJetP4.size(); ij++) {

        TLorentzVector p4 = selectedJetP4.at(ij);
        assert(p4.Pt() > 0);

        switch (selectedJetType[ij]) {

        case RESOLVED: {
            MEM::Object* jet = make_jet(
                                   p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), 1.0,
                                   selectedJetCSV.at(ij),
                                   false
                               );

            tagged.push_back(jet);
            n_resolved++;
            break;
        }

        case BOOSTED_LIGHT: {
            MEM::Object* jet = make_jet(
                                   p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), 0.0,
                                   selectedJetCSV.at(ij),
                                   true
                               );
            untagged.push_back(jet);
            n_light_boosted++;
            break;
        }

        case BOOSTED_B: {
            MEM::Object* jet = make_jet(
                                   p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), 1.0,
                                   selectedJetCSV.at(ij),
                                   true
                               );
            tagged.push_back(jet);
            n_b_boosted++;
            break;
        }
        }
    }

    assert(n_light_boosted==2);
    assert(n_b_boosted==1);
    assert(n_resolved==3);

    for (auto* jet : tagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding tagged jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    for (auto* jet : untagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding untagged jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    for (unsigned int il=0; il < selectedLeptonP4.size(); il++) {
        TLorentzVector lep_p4 = selectedLeptonP4.at(il);
        assert(lep_p4.Pt() > 0);
        MEM::Object* lep = make_lepton(lep_p4.Pt(), lep_p4.Eta(), lep_p4.Phi(), lep_p4.M(), selectedLeptonCharge[il]);
        objs.push_back(lep);
        integrand->push_back_object(lep);
        std::cout << "adding lep " << lep->p4().Pt() << " charge " << lep->getObs(MEM::Observable::CHARGE) << std::endl;
    }

    assert(metP4.Pt() > 0);
    MEM::Object* met = new MEM::Object(metP4, MEM::ObjectType::MET );
    std::cout << "adding met pt " << met->p4().Pt() << " phi " << met->p4().Phi() << std::endl;
    integrand->push_back_object(met);
}



void MEMClassifier::setup_mem_sl_2w2h2t_sj_restperm(
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<JetType>& selectedJetType,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4,
    std::vector<MEM::Object*>& objs,
    MEMResult& res
) {

    if (selectedLeptonP4.size() != 1) {
        throw std::runtime_error("Expected a single-lepton event");
    }

    // Make sure we received a suitable set of input jets
    // Require:
    //  * exactly 6 jets
    //  * 2 light boosted
    //  * 1 b boosted
    //  * 3 resolved

    int n_light_boosted(0), n_b_boosted(0), n_resolved(0);

    assert(selectedJetP4.size() == 6);

    std::vector<MEM::Object*> tagged;
    std::vector<MEM::Object*> untagged;

    for (unsigned int ij=0; ij<selectedJetP4.size(); ij++) {

        TLorentzVector p4 = selectedJetP4.at(ij);
        assert(p4.Pt() > 0);

        switch (selectedJetType[ij]) {

        case RESOLVED: {
            MEM::Object* jet = make_jet(
                                   p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), 1.0,
                                   selectedJetCSV.at(ij),
                                   false, 
				   0
                               );

            tagged.push_back(jet);
            n_resolved++;
            break;
        }

        case BOOSTED_LIGHT: {
            MEM::Object* jet = make_jet(
                                   p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), 0.0,
                                   selectedJetCSV.at(ij),
                                   true,
				   1
                               );
            untagged.push_back(jet);
            n_light_boosted++;
            break;
        }

        case BOOSTED_B: {
            MEM::Object* jet = make_jet(
                                   p4.Pt(), p4.Eta(), p4.Phi(), p4.M(), 1.0,
                                   selectedJetCSV.at(ij),
                                   true,
				   5
                               );
            tagged.push_back(jet);
            n_b_boosted++;
            break;
        }
        }
    }

    assert(n_light_boosted==2);
    assert(n_b_boosted==1);
    assert(n_resolved==3);

    for (auto* jet : tagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding tagged jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    for (auto* jet : untagged) {
        objs.push_back(jet);
        integrand->push_back_object(jet);
        std::cout << "adding untagged jet " << jet->p4().Pt() << " btag " << jet->getObs(MEM::Observable::BTAG) << std::endl;
    }

    for (unsigned int il=0; il < selectedLeptonP4.size(); il++) {
        TLorentzVector lep_p4 = selectedLeptonP4.at(il);
        assert(lep_p4.Pt() > 0);
        MEM::Object* lep = make_lepton(lep_p4.Pt(), lep_p4.Eta(), lep_p4.Phi(), lep_p4.M(), selectedLeptonCharge[il]);
        objs.push_back(lep);
        integrand->push_back_object(lep);
        std::cout << "adding lep " << lep->p4().Pt() << " charge " << lep->getObs(MEM::Observable::CHARGE) << std::endl;
    }

    assert(metP4.Pt() > 0);
    MEM::Object* met = new MEM::Object(metP4, MEM::ObjectType::MET );
    std::cout << "adding met pt " << met->p4().Pt() << " phi " << met->p4().Phi() << std::endl;
    integrand->push_back_object(met);
}


MEMResult MEMClassifier::GetOutput(
    const Hypothesis hypo,
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<JetType>& selectedJetType,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4
) {

    // Make sure vector sizes match up
    assert(selectedLeptonP4.size() == selectedLeptonCharge.size());
    assert(selectedJetP4.size() == selectedJetCSV.size());
    assert(selectedJetP4.size() == selectedJetType.size());
    assert(looseSelectedJetP4.size() == looseSelectedJetCSV.size());

    std::vector<MEM::Object*> objs;

    MEMResult res;

    setup_mem(
        hypo,
        selectedLeptonP4,
        selectedLeptonCharge,
        selectedJetP4,
        selectedJetCSV,
        selectedJetType,
        looseSelectedJetP4,
        looseSelectedJetCSV,
        metP4, objs, res
    );

    MEM::MEMOutput res_sig;
    res_sig.p=-999.9;
    MEM::MEMOutput res_bkg;
    res_bkg.p=-999.9;
    
    switch (hypo) {

    // DEBUG
    case DEBUG: {
        std::cout << "Debug mode - not running MEM" << std::endl;
        break;
    }

    // Single Lepton - Boosted 222
    case SL_2W2H2T_SJ: {
        std::cout << "MEM running signal" << std::endl;
        res_sig = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTH, {}, {});

        std::cout << "MEM running background" << std::endl;
        res_bkg = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTBB, {}, {});

        break;
    }


    // Single Lepton - Boosted 222, Restricted Permuations
    case SL_2W2H2T_SJ_RESTPERM: {
        std::cout << "MEM running signal" << std::endl;
        res_sig = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTH, {}, {});

        std::cout << "MEM running background" << std::endl;
        res_bkg = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTBB, {}, {});

        break;
    }
    
    // Single Lepton - 222
    case SL_2W2H2T: {
        std::cout << "MEM running signal" << std::endl;
        res_sig = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTH, {}, {});

        std::cout << "MEM running background" << std::endl;
        res_bkg = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTBB, {}, {});

        break;
    }

    // Single Lepton - Resolved 022
    case SL_0W2H2T: {
        std::cout << "MEM running signal" << std::endl;
        res_sig = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTH, {},
        {MEM::PSVar::cos_q1, MEM::PSVar::phi_q1, MEM::PSVar::cos_qbar1, MEM::PSVar::phi_qbar1});

        std::cout << "MEM running background" << std::endl;
        res_bkg = integrand->run(MEM::FinalState::LH, MEM::Hypothesis::TTBB, {},
        {MEM::PSVar::cos_q1, MEM::PSVar::phi_q1, MEM::PSVar::cos_qbar1, MEM::PSVar::phi_qbar1});

        break;
    }

    // Di Lepton - Resolved 022
    case DL_0W2H2T: {
        std::cout << "MEM running signal" << std::endl;
        res_sig = integrand->run(MEM::FinalState::LL, MEM::Hypothesis::TTH, {},
                                 {});

        std::cout << "MEM running background" << std::endl;
        res_bkg = integrand->run(MEM::FinalState::LL, MEM::Hypothesis::TTBB, {},
                                 {});

        break;
    }

    // Fallback
    default: {
        std::cerr << "Warning! Fallback case reached. Invalid MEM Hypo!!!" << std::endl;
        throw 1;
    }
    }

    for(auto* o : objs) {
        delete o;
    }
    objs.clear();
    integrand->next_event();

    res.p_sig = res_sig.p;
    res.p_bkg = res_bkg.p;
    res.p_err_sig = res_sig.p_err;
    res.p_err_bkg = res_bkg.p_err;
    res.n_perm_sig = res_sig.num_perm;
    res.n_perm_bkg = res_bkg.num_perm;
    res.p = res_sig.p / (res_sig.p + mem_weight*res_bkg.p);
    return res;
}

MEM::Object* MEMClassifier::make_jet(double pt, double eta, double phi, double mass, double istagged, double csv, bool is_subjet, int pdg_id) const {
    TLorentzVector lv;
    lv.SetPtEtaPhiM(pt, eta, phi, mass);
    MEM::Object* obj = new MEM::Object(lv, MEM::ObjectType::Jet);
    obj->addObs( MEM::Observable::BTAG, istagged); // 0 - jet is assumed to be from a light quark, 1 - a b quark
    obj->addObs( MEM::Observable::CSV, csv); //b-tagger
    obj->addObs( MEM::Observable::PDGID, pdg_id);  // pdg id - can be used to restrict permutations
    // attach the transfer functions corresponding to the jet
    if (is_subjet) {
        obj->addTransferFunction(MEM::TFType::bReco, getTransferFunction("sjb", lv.Eta()));
        obj->addTransferFunction(MEM::TFType::qReco, getTransferFunction("sjl", lv.Eta()));
    } else {
        obj->addTransferFunction(MEM::TFType::bReco, getTransferFunction("b", lv.Eta()));
        obj->addTransferFunction(MEM::TFType::qReco, getTransferFunction("l", lv.Eta()));
    }
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

    const string cmssw_path(std::getenv("CMSSW_BASE"));

    const string transfers_path = (
        string("file://") +
        cmssw_path +
        string("/src/TTH/CommonClassifier/data/transfer.root")
    ).c_str();

    const string btagfile_path = (
        string("file://") +
        cmssw_path +
        string("/src/TTH/CommonClassifier/data/btag_pdfs.root")
    ).c_str();

    cout << "opening " << transfers_path << endl;
    transfers = new TFile(transfers_path.c_str());
    assert(transfers != nullptr);

    cout << "opening " << btagfile_path << endl;
    btagfile = new TFile(btagfile_path.c_str());
    assert(btagfile != nullptr);

    cfg.defaultCfg();
    cfg.transfer_function_method = MEM::TFMethod::External;
    //Transfer functions for jet reconstruction efficiency
    cfg.set_tf_global(MEM::TFType::bLost, 0, getTransferFunction("beff", 0.0));
    cfg.set_tf_global(MEM::TFType::bLost, 1, getTransferFunction("beff", 2.0));
    cfg.set_tf_global(MEM::TFType::qLost, 0, getTransferFunction("leff", 0.0));
    cfg.set_tf_global(MEM::TFType::qLost, 1, getTransferFunction("leff", 2.0));
    cfg.add_distribution_global(MEM::DistributionType::DistributionType::csv_b, GetBTagPDF("b"));
    cfg.add_distribution_global(MEM::DistributionType::DistributionType::csv_c, GetBTagPDF("c"));
    cfg.add_distribution_global(MEM::DistributionType::DistributionType::csv_l, GetBTagPDF("l"));

    integrand = new MEM::Integrand(
        MEM::DebugVerbosity::output
        //|MEM::DebugVerbosity::init
        //|MEM::DebugVerbosity::input
        //|MEM::DebugVerbosity::init_more
        //|MEM::DebugVerbosity::integration
        ,cfg
    );
    integrand->set_cfg(cfg);
    integrand->set_permutation_strategy
    ({MEM::Permutations::BTagged,
      MEM::Permutations::QUntagged,
      MEM::Permutations::QQbarBBbarSymmetry
     });

    blr = new MEM::JetLikelihood();

}

TH3D* MEMClassifier::GetBTagPDF(const char* flavour) {
    assert(btagfile != nullptr);
    TH3D* ret = nullptr;
    ret = (TH3D*)(btagfile->Get((string("btagCSV_")+string(flavour)+string("_pt_eta")).c_str()));
    assert(ret != nullptr);
    return ret;
}

double MEMClassifier::GetJetBProbability(const char* flavour, double pt, double eta, double bdisc) {
    TH3D* h = GetBTagPDF(flavour);
    int i = h->FindBin(pt, std::abs(eta), bdisc);
    double c= h->GetBinContent(i);
    delete h;
    return c;
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
    std::vector<unsigned int>& out_best_perm,
    double& out_P_4b,
    double& out_P_2b
) {
    assert(selectedJetP4.size() >= 4);
    for (unsigned int ij=0; ij < min(selectedJetP4.size(), numMaxJetsBLR); ij++) {
        blr->push_back_object(GetJetBProbabilities(selectedJetP4[ij], selectedJetCSV[ij]));
    }

    std::vector<unsigned int> best_perm_4b;
    std::vector<unsigned int> best_perm_2b;
    double P_4b = blr->calcProbability(MEM::JetInterpretation::b, MEM::JetInterpretation::l, 4, best_perm_4b);
    double P_2b = blr->calcProbability(MEM::JetInterpretation::b, MEM::JetInterpretation::l, 2, best_perm_2b);
    out_best_perm = best_perm_4b;
    blr->next_event();
    out_P_4b = P_4b;
    out_P_2b = P_2b;
    return P_4b / (P_4b + P_2b);
}

MEMClassifier::~MEMClassifier() {
    delete integrand;
    transfers->Close();
    delete blr;
    btagfile->Close();
}

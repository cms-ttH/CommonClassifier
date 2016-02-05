#include "TTH/CommonClassifier/interface/MemBDTClassifierV2.h"

using namespace std;

MEMBDTClassifierV2::MEMBDTClassifierV2 (string weightpath):btagMcut(0.89){
    if(weightpath=="") weightpath=string(getenv("CMSSW_BASE"))+"/src/TTH/CommonClassifier/data/membdtweights_v2/";
    
    // ==================================================
    //init all variables potentially used in BDT set
    variableMap["all_sum_pt_with_met"]=-999.;
    variableMap["aplanarity"]=-999.;
    variableMap["avg_btag_disc_btags"]=-999.;
    variableMap["avg_dr_tagged_jets"]=-999.;
    variableMap["best_higgs_mass"]=-999.;
    variableMap["closest_tagged_dijet_mass"]=-999.;
    variableMap["dEta_fn"]=-999.;
    variableMap["dev_from_avg_disc_btags"]=-999.;
    variableMap["dr_between_lep_and_closest_jet"]=-999.;
    variableMap["fifth_highest_CSV"]=-999.;
    variableMap["first_jet_pt"]=-999.;
    variableMap["fourth_highest_btag"]=-999.;
    variableMap["fourth_jet_pt"]=-999.;
    variableMap["h0"]=-999.;
    variableMap["h1"]=-999.;
    variableMap["h2"]=-999.;
    variableMap["h3"]=-999.;
    variableMap["HT"]=-999.;
    variableMap["invariant_mass_of_everything"]=-999.;
    variableMap["lowest_btag"]=-999.;
    variableMap["M3"]=-999.;
    variableMap["maxeta_jet_jet"]=-999.;
    variableMap["maxeta_jet_tag"]=-999.;
    variableMap["maxeta_tag_tag"]=-999.;
    variableMap["min_dr_tagged_jets"]=-999.;
    variableMap["MET"]=-999.;
    variableMap["MHT"]=-999.;
    variableMap["Mlb"]=-999.;
    variableMap["pt_all_jets_over_E_all_jets"]=-999.;
    variableMap["second_highest_btag"]=-999.;
    variableMap["second_jet_pt"]=-999.;
    variableMap["sphericity"]=-999.;
    variableMap["tagged_dijet_mass_closest_to_125"]=-999.;
    variableMap["third_highest_btag"]=-999.;
    variableMap["third_jet_pt"]=-999.;
    variableMap["Evt_CSV_Average"]=-999.;
    variableMap["Evt_Deta_JetsAverage"]=-999.;
    variableMap["MEM_transformed"]=-999.;
    // ==================================================
    ///init readers for all categories
    readerMap["6j4t"]=new TMVA::Reader("Silent");
    readerMap["5j4t"]=new TMVA::Reader("Silent");
    readerMap["4j4t"]=new TMVA::Reader("Silent");
    readerMap["6j3t"]=new TMVA::Reader("Silent");
    readerMap["5j3t"]=new TMVA::Reader("Silent");
    readerMap["4j3t"]=new TMVA::Reader("Silent");
    readerMap["6j2t"]=new TMVA::Reader("Silent");
    
    // ==================================================
    //add variables to corresponding readers
    // 62
    readerMap["6j2t"]->AddVariable("h1", &variableMap["h1"]);
    readerMap["6j2t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
    readerMap["6j2t"]->AddVariable("sphericity", &variableMap["sphericity"]);
    readerMap["6j2t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
    readerMap["6j2t"]->AddVariable("h3", &variableMap["h3"]);
    readerMap["6j2t"]->AddVariable("HT", &variableMap["HT"]);
    readerMap["6j2t"]->AddVariable("Mlb", &variableMap["Mlb"]);
    readerMap["6j2t"]->AddVariable("fifth_highest_CSV", &variableMap["fifth_highest_CSV"]);
    readerMap["6j2t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);
    
    // 43
    readerMap["4j3t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
    readerMap["4j3t"]->AddVariable("HT", &variableMap["avg_dr_tagged_jets"]);
    readerMap["4j3t"]->AddVariable("MEM_transformed", &variableMap["MEM_transformed"]);
    readerMap["4j3t"]->AddVariable("sphericity", &variableMap["sphericity"]);
    readerMap["4j3t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
    readerMap["4j3t"]->AddVariable("Evt_CSV_Average", &variableMap["Evt_CSV_Average"]);
    readerMap["4j3t"]->AddVariable("M3", &variableMap["M3"]);
    readerMap["4j3t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
    readerMap["4j3t"]->AddVariable("h1", &variableMap["h1"]);
    readerMap["4j3t"]->AddVariable("pt_all_jets_over_E_all_jets", &variableMap["pt_all_jets_over_E_all_jets"]);
    readerMap["4j3t"]->AddVariable("dr_between_lep_and_closest_jet", &variableMap["dr_between_lep_and_closest_jet"]);
    readerMap["4j3t"]->AddVariable("first_jet_pt", &variableMap["first_jet_pt"]);
    readerMap["4j3t"]->AddVariable("closest_tagged_dijet_mass", &variableMap["closest_tagged_dijet_mass"]);

    // 53
    readerMap["5j3t"]->AddVariable("MEM_transformed", &variableMap["MEM_transformed"]);
    readerMap["5j3t"]->AddVariable("pt_all_jets_over_E_all_jets", &variableMap["pt_all_jets_over_E_all_jets"]);
    readerMap["5j3t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
    readerMap["5j3t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
    readerMap["5j3t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);
    readerMap["5j3t"]->AddVariable("Evt_Deta_JetsAverage", &variableMap["Evt_Deta_JetsAverage"]);
    readerMap["5j3t"]->AddVariable("Evt_CSV_Average", &variableMap["Evt_CSV_Average"]);
    
    // 63
    readerMap["6j3t"]->AddVariable("MEM_transformed", &variableMap["MEM_transformed"]);
    readerMap["6j3t"]->AddVariable("Evt_Deta_JetsAverage", &variableMap["Evt_Deta_JetsAverage"]);
    readerMap["6j3t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
    readerMap["6j3t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);
    readerMap["6j3t"]->AddVariable("aplanarity", &variableMap["aplanarity"]);
    readerMap["6j3t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
    readerMap["6j3t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
    readerMap["6j3t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
    readerMap["6j3t"]->AddVariable("tagged_dijet_mass_closest_to_125", &variableMap["tagged_dijet_mass_closest_to_125"]);
    readerMap["6j3t"]->AddVariable("h2", &variableMap["h2"]);
    readerMap["6j3t"]->AddVariable("fifth_highest_CSV", &variableMap["fifth_highest_CSV"]);
    
    // 44
    readerMap["4j4t"]->AddVariable("MEM_transformed", &variableMap["MEM_transformed"]);
    readerMap["4j4t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
    readerMap["4j4t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
    readerMap["4j4t"]->AddVariable("maxeta_tag_tag", &variableMap["maxeta_tag_tag"]);
    readerMap["4j4t"]->AddVariable("first_jet_pt", &variableMap["first_jet_pt"]);
    readerMap["4j4t"]->AddVariable("Evt_Deta_JetsAverage", &variableMap["Evt_Deta_JetsAverage"]);
    readerMap["4j4t"]->AddVariable("dr_between_lep_and_closest_jet", &variableMap["dr_between_lep_and_closest_jet"]);
    readerMap["4j4t"]->AddVariable("fourth_highest_btag", &variableMap["fourth_highest_btag"]);    
    readerMap["4j4t"]->AddVariable("aplanarity", &variableMap["aplanarity"]);    
    readerMap["4j4t"]->AddVariable("invariant_mass_of_everything", &variableMap["invariant_mass_of_everything"]);    
    readerMap["4j4t"]->AddVariable("M3", &variableMap["M3"]);    
    // 54
    readerMap["5j4t"]->AddVariable("MEM_transformed", &variableMap["MEM_transformed"]);
    readerMap["5j4t"]->AddVariable("avg_btag_disc_btags", &variableMap["avg_btag_disc_btags"]);
    readerMap["5j4t"]->AddVariable("Evt_Deta_JetsAverage", &variableMap["Evt_Deta_JetsAverage"]);
    readerMap["5j4t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
    readerMap["5j4t"]->AddVariable("M3", &variableMap["M3"]);
    readerMap["5j4t"]->AddVariable("all_sum_pt_with_met", &variableMap["all_sum_pt_with_met"]);
    readerMap["5j4t"]->AddVariable("h2", &variableMap["h2"]);
    readerMap["5j4t"]->AddVariable("avg_dr_tagged_jets", &variableMap["avg_dr_tagged_jets"]);
    
    // 64
    readerMap["6j4t"]->AddVariable("third_highest_btag", &variableMap["third_highest_btag"]);
    readerMap["6j4t"]->AddVariable("MEM_transformed", &variableMap["MEM_transformed"]);
    readerMap["6j4t"]->AddVariable("Evt_Deta_JetsAverage", &variableMap["Evt_Deta_JetsAverage"]);
    readerMap["6j4t"]->AddVariable("sphericity", &variableMap["sphericity"]);
    readerMap["6j4t"]->AddVariable("fourth_jet_pt", &variableMap["fourth_jet_pt"]);
    readerMap["6j4t"]->AddVariable("aplanarity", &variableMap["aplanarity"]);
    readerMap["6j4t"]->AddVariable("M3", &variableMap["M3"]);
    readerMap["6j4t"]->AddVariable("third_jet_pt", &variableMap["third_jet_pt"]);
    
    // ==================================================
    //book MVAs from weights 
    readerMap["6j4t"]->BookMVA("BDT",weightpath+"/weights_64.xml");
    readerMap["5j4t"]->BookMVA("BDT",weightpath+"/weights_54.xml");
    readerMap["4j4t"]->BookMVA("BDT",weightpath+"/weights_44.xml");
    readerMap["6j3t"]->BookMVA("BDT",weightpath+"/weights_63.xml");
    readerMap["5j3t"]->BookMVA("BDT",weightpath+"/weights_53.xml");
    readerMap["4j3t"]->BookMVA("BDT",weightpath+"/weights_43.xml");
    readerMap["6j2t"]->BookMVA("BDT",weightpath+"/weights_62.xml");
    
}
MEMBDTClassifierV2::~MEMBDTClassifierV2(){
}

void MEMBDTClassifierV2::ResetVariableMap(){
    for(auto it = variableMap.begin(); it != variableMap.end(); it++){
	it->second=-999.;
    }
}

void MEMBDTClassifierV2::SetCategory(const std::vector<TLorentzVector>& selectedLeptonP4, 
				const std::vector<TLorentzVector>& selectedJetP4, 
				const std::vector<double>& selectedJetCSV){
    int njets=selectedJetP4.size();
    int ntagged=0;
    for(uint i=0; i<selectedJetCSV.size(); i++){
	if(selectedJetCSV[i]>btagMcut) ntagged++;
    }
    if(selectedLeptonP4.size()!=1||njets<4||(njets<6&&ntagged<3)){
	category="none";
	return;
    }
    else if(ntagged>=4&&njets>=6){
	category =  "6j4t"; 
    }
    else if(ntagged>=4&&njets==5){
	category =  "5j4t"; 
    }
    else if(ntagged>=4&&njets==4){
	category =  "4j4t"; 
    }
    else if(ntagged==3&&njets>=6){
	category =  "6j3t"; 
    }
    else if(ntagged==3&&njets==5){
	category =  "5j3t"; 
    }
    else if(ntagged==3&&njets==4){
	category =  "4j3t"; 
    }
    else if(ntagged==2&&njets>=6){
	category =  "6j2t"; 
    }
    else{
	category = "none";
    }
    
}

double MEMBDTClassifierV2::GetBDTOutput(const std::vector<TLorentzVector>& selectedLeptonP4, 
				   const std::vector<TLorentzVector>& selectedJetP4, 
				   const std::vector<double>& selectedJetCSV, 
				   const std::vector<TLorentzVector>& looseSelectedJetP4, 
				   const std::vector<double>& looseSelectedJetCSV, 
				   const TLorentzVector& metP4,
				   const double MEM_p_sig,
				   const double MEM_p_bkg){
    
    // Reset all map entries to -999 so that noting is left over from the last event
    ResetVariableMap();
    
    // find out category
    SetCategory(selectedLeptonP4, selectedJetP4, selectedJetCSV);
    if(category=="none"){	
	return -2;
    }
    // ==================================================
    // construct object vectors etc
    
    std::vector<double> selectedJetCSV_fixed;
    for(uint i=0; i<selectedJetCSV.size(); i++){
	double tag=selectedJetCSV[i];
	if (std::isnan(tag)){
	    tag=-.1;
	}
	else if (tag<0){
	    tag=-.1;
	}
	else if(tag>1){
	    tag=1.;
	}
	selectedJetCSV_fixed.push_back(tag);
    }
    
    double transformedMEM=0.01;
    if(MEM_p_sig>0 and MEM_p_bkg>0){
       transformedMEM=(MEM_p_sig/(MEM_p_sig+0.15*MEM_p_bkg));
    }
    
    std::vector<TLorentzVector> selectedTaggedJetP4;
    for(uint i=0; i<selectedJetP4.size();i++){
	if(selectedJetCSV_fixed[i]>btagMcut){
	    selectedTaggedJetP4.push_back(selectedJetP4[i]);
	}
    }
    
    vector< vector<double> > jets_vvdouble;  
    for(auto jet=selectedJetP4.begin();jet!=selectedJetP4.end(); jet++){
	vector<double> pxpypzE;
	pxpypzE.push_back(jet->Px());
	pxpypzE.push_back(jet->Py());
	pxpypzE.push_back(jet->Pz());
	pxpypzE.push_back(jet->E());
	jets_vvdouble.push_back(pxpypzE);
    }
    
    vector<double> sortedCSV=selectedJetCSV_fixed;
    std::sort(sortedCSV.begin(),sortedCSV.end(),std::greater<double>());
    
    // ==================================================
    // calculate variables
    // aplanarity and sphericity
    double aplanarity,sphericity;
    bdtvar.getSp(selectedLeptonP4[0],metP4,selectedJetP4,aplanarity,sphericity);
    
    // Fox Wolfram
    double h0,h1,h2,h3,h4;
    bdtvar.getFox(selectedJetP4,h0,h1,h2,h3,h4);
    
    // best higgs mass 1
    double minChi,dRbb;
    TLorentzVector bjet1,bjet2;
    double bestHiggsMass = bdtvar.getBestHiggsMass(selectedLeptonP4[0],metP4,selectedJetP4,selectedJetCSV_fixed,minChi,dRbb,bjet1,bjet2, looseSelectedJetP4,looseSelectedJetCSV);
    
    // study top bb system
    TLorentzVector dummy_metv;
    double minChiStudy, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbbStudy, testquant1, testquant2, testquant3, testquant4, testquant5, testquant6, testquant7; 
    TLorentzVector b1,b2;
    bdtvar.study_tops_bb_syst (metP4.Pt(), metP4.Phi(), dummy_metv, selectedLeptonP4[0], jets_vvdouble, selectedJetCSV_fixed, minChiStudy, chi2lepW, chi2leptop, chi2hadW, chi2hadtop, mass_lepW, mass_leptop, mass_hadW, mass_hadtop, dRbbStudy, testquant1, testquant2, testquant3, testquant4, testquant5, testquant6, testquant7, b1, b2);
    double dEta_fn=testquant6;
    // ptE ratio
    double pt_E_ratio = bdtvar.pt_E_ratio_jets(jets_vvdouble);
    
    // etamax
    double jet_jet_etamax = bdtvar.get_jet_jet_etamax (jets_vvdouble);
    double jet_tag_etamax = bdtvar.get_jet_tag_etamax (jets_vvdouble,selectedJetCSV_fixed);
    double tag_tag_etamax = bdtvar.get_tag_tag_etamax (jets_vvdouble,selectedJetCSV_fixed);
    
    // jet variables
    double sum_pt_jets=0;
    double dr_between_lep_and_closest_jet=99;
    double mht_px=0;
    double mht_py=0;
    TLorentzVector p4_of_everything=selectedLeptonP4[0];
    p4_of_everything+=metP4;
    for(auto jetvec = selectedJetP4.begin() ; jetvec != selectedJetP4.end(); ++jetvec){
	dr_between_lep_and_closest_jet=fmin(dr_between_lep_and_closest_jet,selectedLeptonP4[0].DeltaR(*jetvec));
	sum_pt_jets += jetvec->Pt();
	mht_px += jetvec->Px();
	mht_py += jetvec->Py();
	p4_of_everything += *jetvec;
    }
    mht_px+=selectedLeptonP4[0].Px();
    mht_py+=selectedLeptonP4[0].Py();
    double mass_of_everything=p4_of_everything.M();
    double sum_pt_wo_met=sum_pt_jets+selectedLeptonP4[0].Pt();
    double sum_pt_with_met=metP4.Pt()+sum_pt_wo_met;
    double MHT=sqrt( mht_px*mht_px + mht_py*mht_py );
    
    double Mlb=0;   // mass of lepton and closest bt-tagged jet
    double minDr_for_Mlb=999.;
    for(auto tagged_jet=selectedTaggedJetP4.begin();tagged_jet!=selectedTaggedJetP4.end();tagged_jet++){
	double drLep=selectedLeptonP4[0].DeltaR(*tagged_jet);
	if(drLep<minDr_for_Mlb){
	    minDr_for_Mlb=drLep;
	    Mlb=(selectedLeptonP4[0]+*tagged_jet).M();
	}
    }
    double closest_tagged_dijet_mass=-99;
    double minDrTagged=99;
    double sumDrTagged=0;
    int npairs=0;
    double tagged_dijet_mass_closest_to_125=-99;
    for(auto tagged_jet1=selectedTaggedJetP4.begin();tagged_jet1!=selectedTaggedJetP4.end();tagged_jet1++){
	for(auto tagged_jet2=tagged_jet1+1;tagged_jet2!=selectedTaggedJetP4.end();tagged_jet2++){
	    double dr=tagged_jet1->DeltaR(*tagged_jet2);
	    double m = (*tagged_jet1+*tagged_jet2).M();
	    sumDrTagged+=dr;
	    npairs++;
	    if(dr<minDrTagged){
		minDrTagged=dr;
		closest_tagged_dijet_mass=m;
	    }
	    if(fabs(tagged_dijet_mass_closest_to_125-125)>fabs(m-125)){
		tagged_dijet_mass_closest_to_125=m;
	    }
	    
	}
    }
    double avgDrTagged=-1;
    if(npairs!=0) avgDrTagged=sumDrTagged/npairs;
    // M3
    double m3 = -1.;
    double maxpt_for_m3=-1;
    for(auto itJetVec1 = selectedJetP4.begin() ; itJetVec1 != selectedJetP4.end(); ++itJetVec1){
	for(auto itJetVec2 = itJetVec1+1 ; itJetVec2 != selectedJetP4.end(); ++itJetVec2){
	    for(auto itJetVec3 = itJetVec2+1 ; itJetVec3 != selectedJetP4.end(); ++itJetVec3){
		
		TLorentzVector m3vec = *itJetVec1 + *itJetVec2 + *itJetVec3;
		
		if(m3vec.Pt() > maxpt_for_m3){
		    maxpt_for_m3 = m3vec.Pt();
		    m3 = m3vec.M();
		}
	    } 
	}
    }
    double detaJetsAverage = 0;
    int nPairsJets = 0;
    for(auto itJetVec1 = selectedJetP4.begin() ; itJetVec1 != selectedJetP4.end(); ++itJetVec1){
	for(auto itJetVec2 = itJetVec1+1 ; itJetVec2 != selectedJetP4.end(); ++itJetVec2){
	    detaJetsAverage += fabs(itJetVec1->Eta()-itJetVec2->Eta());
	    nPairsJets++;
	}
    }
    if(nPairsJets > 0){
	detaJetsAverage /= (double) nPairsJets;
    }
    
    // btag variables
    double averageCSV_tagged = 0;
    double averageCSV_all = 0;
    double lowest_btag=99;
    int njets=selectedJetP4.size();
    int ntags=0;
    for(auto itCSV = selectedJetCSV_fixed.begin() ; itCSV != selectedJetCSV_fixed.end(); ++itCSV){
	averageCSV_all += fmax(*itCSV,0);
	if(*itCSV<btagMcut) continue;
	lowest_btag=fmin(*itCSV,lowest_btag);
	averageCSV_tagged += fmax(*itCSV,0);
	ntags++;
    }
    if(ntags>0)
	averageCSV_tagged /= ntags;
    else
	averageCSV_tagged=0;
    if(selectedJetCSV_fixed.size()>0)
	averageCSV_all /= selectedJetCSV_fixed.size();
    else
	averageCSV_all=0;
    
    if(lowest_btag>90) lowest_btag=-1;
    
    double csvDev = 0;
    for(auto itCSV = selectedJetCSV_fixed.begin() ; itCSV != selectedJetCSV_fixed.end(); ++itCSV){
	if(*itCSV<btagMcut) continue;
	csvDev += pow(*itCSV - averageCSV_tagged,2);
    }
    if(ntags>0)
	csvDev /= ntags;
    else
	csvDev=-1.;
    
    
    // ==================================================
    // Fill variable map
    variableMap["all_sum_pt_with_met"]=sum_pt_with_met;
    variableMap["aplanarity"]=aplanarity;
    variableMap["avg_btag_disc_btags"]=averageCSV_tagged;
    variableMap["avg_dr_tagged_jets"]=avgDrTagged;
    variableMap["best_higgs_mass"]=bestHiggsMass;
    variableMap["closest_tagged_dijet_mass"]=closest_tagged_dijet_mass;
    variableMap["dEta_fn"]=dEta_fn;
    variableMap["dev_from_avg_disc_btags"]=csvDev;
    variableMap["dr_between_lep_and_closest_jet"]=dr_between_lep_and_closest_jet;
    variableMap["fifth_highest_CSV"]=njets>4?sortedCSV[4]:-1.;
    variableMap["first_jet_pt"]=selectedJetP4.size()>0?selectedJetP4[0].Pt():-99;
    variableMap["fourth_highest_btag"]=njets>3?sortedCSV[3]:-1.;
    variableMap["fourth_jet_pt"]=selectedJetP4.size()>3?selectedJetP4[3].Pt():-99;
    variableMap["h0"]=h0;
    variableMap["h1"]=h1;
    variableMap["h2"]=h2;
    variableMap["h3"]=h3;
    variableMap["HT"]=sum_pt_jets;
    variableMap["invariant_mass_of_everything"]=mass_of_everything;
    variableMap["lowest_btag"]=lowest_btag;
    variableMap["M3"]=m3;
    variableMap["maxeta_jet_jet"]=jet_jet_etamax;
    variableMap["maxeta_jet_tag"]=jet_tag_etamax;
    variableMap["maxeta_tag_tag"]=tag_tag_etamax;
    variableMap["min_dr_tagged_jets"]=minDrTagged;
    variableMap["MET"]=metP4.Pt();
    variableMap["MHT"]=MHT;
    variableMap["Mlb"]=Mlb;
    variableMap["pt_all_jets_over_E_all_jets"]=pt_E_ratio;
    variableMap["second_highest_btag"]=njets>1?sortedCSV[1]:-1.;
    variableMap["second_jet_pt"]=selectedJetP4.size()>1?selectedJetP4[1].Pt():-99;
    variableMap["sphericity"]=sphericity;
    variableMap["tagged_dijet_mass_closest_to_125"]=tagged_dijet_mass_closest_to_125;
    variableMap["third_highest_btag"]=njets>2?sortedCSV[2]:-1.;
    variableMap["third_jet_pt"]=selectedJetP4.size()>2?selectedJetP4[2].Pt():-99;
    variableMap["Evt_CSV_Average"]=averageCSV_all;
    variableMap["Evt_Deta_JetsAverage"]=detaJetsAverage;
    variableMap["MEM_transformed"]=transformedMEM;

    
    // ==================================================
    // evaluate BDT of current category
    return readerMap[category]->EvaluateMVA("BDT");
}

std::string MEMBDTClassifierV2::GetCategoryOfLastEvaluation() const{
    return category;
}

std::map<std::string,float> MEMBDTClassifierV2::GetVariablesOfLastEvaluation() const{
    return variableMap;
}

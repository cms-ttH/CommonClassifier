#include "TTH/CommonClassifier/interface/DLBDTClassifier.h"

//TODO check category definitions and change cate0 etc. to actual names

using namespace std;

DLBDTClassifier::DLBDTClassifier (string weightpath):btagMcut(0.8){
  //TODO put BDT weights into path and correct path name maybe
    if(weightpath=="") weightpath=string(getenv("CMSSW_BASE"))+"/src/TTH/CommonClassifier/data/dlbdtweights_v3/";
    // ==================================================
    //init all variables potentially used in BDT set
    variableMap["multiplicity_jets"]=-999.;
    variableMap["btagDiscriminatorAverage_tagged"]=-999.;
    variableMap["btagDiscriminatorAverage_untagged"]=-999.;
    variableMap["minDeltaR_jet_jet"]=-999.;
    variableMap["minDeltaR_tag_tag"]=-999.;
    variableMap["avgDeltaR_jet_jet"]=-999.;
    variableMap["avgDeltaR_jet_tag"]=-999.;
    variableMap["avgDeltaR_tag_tag"]=-999.;
    variableMap["ptSum_jets_leptons"]=-999.;
    variableMap["multiplicity_higgsLikeDijet15"]=-999.;
    variableMap["mass_higgsLikeDijet"]=-999.;
    variableMap["mass_higgsLikeDijet2"]=-999.;
    variableMap["mass_jet_jet_min_deltaR"]=-999.;
    variableMap["mass_tag_tag_min_deltaR"]=-999.;
    variableMap["mass_jet_tag_min_deltaR"]=-999.;
    variableMap["mass_tag_tag_max_mass"]=-999.;
    variableMap["median_mass_jet_jet"]=-999.;
    variableMap["maxDeltaEta_jet_jet"]=-999.;
    variableMap["maxDeltaEta_tag_tag"]=-999.;
    variableMap["HT_jets"]=-999.;
    variableMap["HT_tags"]=-999.;
    variableMap["pT_jet_jet_min_deltaR"]=-999.;
    variableMap["pT_jet_tag_min_deltaR"]=-999.;
    variableMap["pT_tag_tag_min_deltaR"]=-999.;
    variableMap["mass_jet_jet_jet_max_pT"]=-999.;
    variableMap["mass_jet_tag_tag_max_pT"]=-999.;
    variableMap["centrality_jets_leps"]=-999.;
    variableMap["centrality_tags"]=-999.;
    variableMap["twist_jet_jet_max_mass"]=-999.;
    variableMap["twist_jet_tag_max_mass"]=-999.;
    variableMap["twist_tag_tag_max_mass"]=-999.;
    variableMap["twist_tag_tag_min_deltaR"]=-999.;
    variableMap["sphericity_jet"]=-999.;
    variableMap["aplanarity_jet"]=-999.;
    variableMap["circularity_jet"]=-999.;
    variableMap["isotropy_jet"]=-999.;
    variableMap["C_jet"]=-999.;
    variableMap["D_jet"]=-999.;
    variableMap["transSphericity_jet"]=-999.;
    variableMap["sphericity_tag"]=-999.;
    variableMap["aplanarity_tag"]=-999.;
    variableMap["circularity_tag"]=-999.;
    variableMap["isotropy_tag"]=-999.;
    variableMap["C_tag"]=-999.;
    variableMap["D_tag"]=-999.;
    variableMap["transSphericity_tag"]=-999.;
    variableMap["H0_jet"]=-999.;
    variableMap["H1_jet"]=-999.;
    variableMap["H2_jet"]=-999.;
    variableMap["H3_jet"]=-999.;
    variableMap["H4_jet"]=-999.;
    variableMap["R1_jet"]=-999.;
    variableMap["R2_jet"]=-999.;
    variableMap["R3_jet"]=-999.;
    variableMap["R4_jet"]=-999.;
    variableMap["H0_tag"]=-999.;
    variableMap["H1_tag"]=-999.;
    variableMap["H2_tag"]=-999.;
    variableMap["H3_tag"]=-999.;
    variableMap["H4_tag"]=-999.;
    variableMap["R1_tag"]=-999.;
    variableMap["R2_tag"]=-999.;
    variableMap["R3_tag"]=-999.;
    variableMap["R4_tag"]=-999.;

    // ==================================================
    ///init readers for all categories
    readerMap["cate0"]=new TMVA::Reader("Silent");
    readerMap["cate1"]=new TMVA::Reader("Silent");
    readerMap["cate2"]=new TMVA::Reader("Silent");
    readerMap["cate3"]=new TMVA::Reader("Silent");
    readerMap["cate4"]=new TMVA::Reader("Silent");
    
    
    // ==================================================
    //add variables to corresponding readers
    // cate0 3j2t
    readerMap["cate0"]->AddVariable("ptSum_jets_leptons", & variableMap["ptSum_jets_leptons"]);
    readerMap["cate0"]->AddVariable("btagDiscriminatorAverage_untagged", & variableMap["btagDiscriminatorAverage_untagged"]);
    readerMap["cate0"]->AddVariable("R1_jet", & variableMap["R1_jet"]);
    readerMap["cate0"]->AddVariable("mass_tag_tag_max_mass", & variableMap["mass_tag_tag_max_mass"]);
    readerMap["cate0"]->AddVariable("H1_jet", & variableMap["H1_jet"]);
    readerMap["cate0"]->AddVariable("minDeltaR_jet_jet", & variableMap["minDeltaR_jet_jet"]);
    readerMap["cate0"]->AddVariable("HT_jets", & variableMap["HT_jets"]);
    readerMap["cate0"]->AddVariable("mass_higgsLikeDijet", & variableMap["mass_higgsLikeDijet"]);
    readerMap["cate0"]->AddVariable("H0_jet", & variableMap["H0_jet"]);
    readerMap["cate0"]->AddVariable("mass_jet_tag_min_deltaR", & variableMap["mass_jet_tag_min_deltaR"]);
    
    // cate1 3j3t
    readerMap["cate1"]->AddVariable("btagDiscriminatorAverage_tagged", & variableMap["btagDiscriminatorAverage_tagged"]);
    readerMap["cate1"]->AddVariable("pT_tag_tag_min_deltaR", & variableMap["pT_tag_tag_min_deltaR"]);
    readerMap["cate1"]->AddVariable("avgDeltaR_tag_tag", & variableMap["avgDeltaR_tag_tag"]);
    readerMap["cate1"]->AddVariable("mass_jet_tag_min_deltaR", & variableMap["mass_jet_tag_min_deltaR"]);
    readerMap["cate1"]->AddVariable("mass_higgsLikeDijet", & variableMap["mass_higgsLikeDijet"]);
    readerMap["cate1"]->AddVariable("mass_jet_jet_min_deltaR", & variableMap["mass_jet_jet_min_deltaR"]);
    readerMap["cate1"]->AddVariable("twist_tag_tag_min_deltaR", & variableMap["twist_tag_tag_min_deltaR"]);
    readerMap["cate1"]->AddVariable("maxDeltaEta_jet_jet", & variableMap["maxDeltaEta_jet_jet"]);
    readerMap["cate1"]->AddVariable("R2_tag", & variableMap["R2_tag"]);
    readerMap["cate1"]->AddVariable("avgDeltaR_jet_jet", & variableMap["avgDeltaR_jet_jet"]);
    readerMap["cate1"]->AddVariable("mass_tag_tag_max_mass", & variableMap["mass_tag_tag_max_mass"]);
    readerMap["cate1"]->AddVariable("HT_jets", & variableMap["HT_jets"]);

    // cate2 >=4j2t
    readerMap["cate2"]->AddVariable("HT_jets", & variableMap["HT_jets"]);
    readerMap["cate2"]->AddVariable("multiplicity_jets", & variableMap["multiplicity_jets"]);
    readerMap["cate2"]->AddVariable("D_jet", & variableMap["D_jet"]);
    readerMap["cate2"]->AddVariable("avgDeltaR_jet_tag", & variableMap["avgDeltaR_jet_tag"]);
    readerMap["cate2"]->AddVariable("mass_tag_tag_min_deltaR", & variableMap["mass_tag_tag_min_deltaR"]);
    readerMap["cate2"]->AddVariable("pT_jet_tag_min_deltaR", & variableMap["pT_jet_tag_min_deltaR"]);
    readerMap["cate2"]->AddVariable("R1_jet", & variableMap["R1_jet"]);
    readerMap["cate2"]->AddVariable("centrality_jets_leps", & variableMap["centrality_jets_leps"]);
    readerMap["cate2"]->AddVariable("minDeltaR_jet_jet", & variableMap["minDeltaR_jet_jet"]);
    readerMap["cate2"]->AddVariable("pT_tag_tag_min_deltaR", & variableMap["pT_tag_tag_min_deltaR"]);
    readerMap["cate2"]->AddVariable("centrality_tags", & variableMap["centrality_tags"]);
    readerMap["cate2"]->AddVariable("H4_jet", & variableMap["H4_jet"]);

    // cate3 >=4j3t
    readerMap["cate3"]->AddVariable("btagDiscriminatorAverage_untagged", & variableMap["btagDiscriminatorAverage_untagged"]);
    readerMap["cate3"]->AddVariable("maxDeltaEta_tag_tag", & variableMap["maxDeltaEta_tag_tag"]);
    readerMap["cate3"]->AddVariable("btagDiscriminatorAverage_tagged", & variableMap["btagDiscriminatorAverage_tagged"]);
    readerMap["cate3"]->AddVariable("maxDeltaEta_jet_jet", & variableMap["maxDeltaEta_jet_jet"]);
    readerMap["cate3"]->AddVariable("ptSum_jets_leptons", & variableMap["ptSum_jets_leptons"]);
    readerMap["cate3"]->AddVariable("minDeltaR_jet_jet", & variableMap["minDeltaR_jet_jet"]);
    readerMap["cate3"]->AddVariable("mass_tag_tag_min_deltaR", & variableMap["mass_tag_tag_min_deltaR"]);
    readerMap["cate3"]->AddVariable("H0_jet", & variableMap["H0_jet"]);
    readerMap["cate3"]->AddVariable("avgDeltaR_tag_tag", & variableMap["avgDeltaR_tag_tag"]);
    readerMap["cate3"]->AddVariable("multiplicity_higgsLikeDijet15", & variableMap["multiplicity_higgsLikeDijet15"]);
    readerMap["cate3"]->AddVariable("minDeltaR_tag_tag", & variableMap["minDeltaR_tag_tag"]);
    readerMap["cate3"]->AddVariable("multiplicity_jets", & variableMap["multiplicity_jets"]);

    // cate4 >=4j>=4t
    readerMap["cate4"]->AddVariable("sphericity_tag", & variableMap["sphericity_tag"]);
    readerMap["cate4"]->AddVariable("btagDiscriminatorAverage_tagged", & variableMap["btagDiscriminatorAverage_tagged"]);
    readerMap["cate4"]->AddVariable("HT_tags", & variableMap["HT_tags"]);
    readerMap["cate4"]->AddVariable("H1_tag", & variableMap["H1_tag"]);
    readerMap["cate4"]->AddVariable("circularity_tag", & variableMap["circularity_tag"]);
    readerMap["cate4"]->AddVariable("H4_tag", & variableMap["H4_tag"]);
    readerMap["cate4"]->AddVariable("C_jet", & variableMap["C_jet"]);
    readerMap["cate4"]->AddVariable("maxDeltaEta_tag_tag", & variableMap["maxDeltaEta_tag_tag"]);
    readerMap["cate4"]->AddVariable("multiplicity_higgsLikeDijet15", & variableMap["multiplicity_higgsLikeDijet15"]);
    readerMap["cate4"]->AddVariable("mass_tag_tag_min_deltaR", & variableMap["mass_tag_tag_min_deltaR"]);
    readerMap["cate4"]->AddVariable("avgDeltaR_jet_tag", & variableMap["avgDeltaR_jet_tag"]);
    
    // ==================================================
    
//TODO uncomment the reader booking if weights are available
    //book MVAs from weights 
    readerMap["cate0"]->BookMVA("BDT",weightpath+"/classification_step7_cate0_k0002.weights.xml");
    readerMap["cate1"]->BookMVA("BDT",weightpath+"/classification_step7_cate1_k1002.weights.xml");
    readerMap["cate2"]->BookMVA("BDT",weightpath+"/classification_step7_cate2_k2002.weights.xml");
    readerMap["cate3"]->BookMVA("BDT",weightpath+"/classification_step7_cate3_k3002.weights.xml");
    readerMap["cate4"]->BookMVA("BDT",weightpath+"/classification_step7_cate4_k4002.weights.xml");
}
DLBDTClassifier::~DLBDTClassifier(){
}

void DLBDTClassifier::ResetVariableMap(){
    for(auto it = variableMap.begin(); it != variableMap.end(); it++){
	it->second=-999.;
    }
}

void DLBDTClassifier::SetCategory(const std::vector<TLorentzVector>& selectedLeptonP4, 
				const std::vector<TLorentzVector>& selectedJetP4, 
				const std::vector<double>& selectedJetCSV){
    int njets=selectedJetP4.size();
    int ntagged=0;
    for(uint i=0; i<selectedJetCSV.size(); i++){
	if(selectedJetCSV[i]>btagMcut) ntagged++;
    }
    if(selectedLeptonP4.size()!=2||njets<2||ntagged<2){
	category="none";
	return;
    }
    else if(ntagged==2&&njets==3){
	category =  "cate0"; 
    }
    else if(ntagged==3&&njets==3){
	category =  "cate1"; 
    }
    else if(ntagged==2&&njets>=4){
	category =  "cate2"; 
    }
    else if(ntagged==3&&njets>=4){
	category =  "cate3"; 
    }
    else if(ntagged>=4&&njets>=4){
	category =  "cate4"; 
    }
    else{
	category = "none";
    }
    
}

double DLBDTClassifier::GetBDTOutput(const std::vector<TLorentzVector>& selectedLeptonP4, 
				   const std::vector<double>& selectedLeptonCharge,
				   const std::vector<TLorentzVector>& selectedJetP4, 
				   const std::vector<double>& selectedJetCSV, 
// 				   const std::vector<TLorentzVector>& looseSelectedJetP4, 
// 				   const std::vector<double>& looseSelectedJetCSV, 
				   const TLorentzVector& metP4){
    
    // Reset all map entries to -999 so that noting is left over from the last event
    ResetVariableMap();
    
    // find out category
    SetCategory(selectedLeptonP4, selectedJetP4, selectedJetCSV);
    if(category=="none"){	
	return -2;
    }
    // ==================================================
    // construct object vectors etc
    
    // handle CSV values outside of reasonable range (happened some time ago)
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
//        std::cout<<"calling  DLBDTMvaVariablesEventClassification"<<std::endl;

    DLBDTMvaVariablesEventClassification* dlbdtvar=DLBDTMvaVariablesEventClassification::fillVariables(selectedLeptonP4, selectedLeptonCharge,selectedJetP4,selectedJetCSV,btagMcut );
    
    // ==================================================
    // Fill variable map
    variableMap["multiplicity_jets"]=dlbdtvar->multiplicity_jets_.value_;
    variableMap["btagDiscriminatorAverage_tagged"]=dlbdtvar->btagDiscriminatorAverage_tagged_.value_;
    variableMap["btagDiscriminatorAverage_untagged"]=dlbdtvar->btagDiscriminatorAverage_untagged_.value_;
    variableMap["minDeltaR_jet_jet"]=dlbdtvar->minDeltaR_jet_jet_.value_;
    variableMap["minDeltaR_tag_tag"]=dlbdtvar->minDeltaR_tag_tag_.value_;
    variableMap["avgDeltaR_jet_jet"]=dlbdtvar->avgDeltaR_jet_jet_.value_;
    variableMap["avgDeltaR_jet_tag"]=dlbdtvar->avgDeltaR_jet_tag_.value_;
    variableMap["avgDeltaR_tag_tag"]=dlbdtvar->avgDeltaR_tag_tag_.value_;
    variableMap["ptSum_jets_leptons"]=dlbdtvar->ptSum_jets_leptons_.value_;
    variableMap["multiplicity_higgsLikeDijet15"]=dlbdtvar->multiplicity_higgsLikeDijet15_.value_;
    variableMap["mass_higgsLikeDijet"]=dlbdtvar->mass_higgsLikeDijet_.value_;
    variableMap["mass_higgsLikeDijet2"]=dlbdtvar->mass_higgsLikeDijet2_.value_;
    variableMap["mass_jet_jet_min_deltaR"]=dlbdtvar->mass_jet_jet_min_deltaR_.value_;
    variableMap["mass_tag_tag_min_deltaR"]=dlbdtvar->mass_tag_tag_min_deltaR_.value_;
    variableMap["mass_jet_tag_min_deltaR"]=dlbdtvar->mass_jet_tag_min_deltaR_.value_;
    variableMap["mass_tag_tag_max_mass"]=dlbdtvar->mass_tag_tag_max_mass_.value_;
    variableMap["median_mass_jet_jet"]=dlbdtvar->median_mass_jet_jet_.value_;
    variableMap["maxDeltaEta_jet_jet"]=dlbdtvar->maxDeltaEta_jet_jet_.value_;
    variableMap["maxDeltaEta_tag_tag"]=dlbdtvar->maxDeltaEta_tag_tag_.value_;
    variableMap["HT_jets"]=dlbdtvar->HT_jets_.value_;
    variableMap["HT_tags"]=dlbdtvar->HT_tags_.value_;
    variableMap["pT_jet_jet_min_deltaR"]=dlbdtvar->pT_jet_jet_min_deltaR_.value_;
    variableMap["pT_jet_tag_min_deltaR"]=dlbdtvar->pT_jet_tag_min_deltaR_.value_;
    variableMap["pT_tag_tag_min_deltaR"]=dlbdtvar->pT_tag_tag_min_deltaR_.value_;
    variableMap["mass_jet_jet_jet_max_pT"]=dlbdtvar->mass_jet_jet_jet_max_pT_.value_;
    variableMap["mass_jet_tag_tag_max_pT"]=dlbdtvar->mass_jet_tag_tag_max_pT_.value_;
    variableMap["centrality_jets_leps"]=dlbdtvar->centrality_jets_leps_.value_;
    variableMap["centrality_tags"]=dlbdtvar->centrality_tags_.value_;
    variableMap["twist_jet_jet_max_mass"]=dlbdtvar->twist_jet_jet_max_mass_.value_;
    variableMap["twist_jet_tag_max_mass"]=dlbdtvar->twist_jet_tag_max_mass_.value_;
    variableMap["twist_tag_tag_max_mass"]=dlbdtvar->twist_tag_tag_max_mass_.value_;
    variableMap["twist_tag_tag_min_deltaR"]=dlbdtvar->twist_tag_tag_min_deltaR_.value_;
    variableMap["sphericity_jet"]=dlbdtvar->sphericity_jet_.value_;
    variableMap["aplanarity_jet"]=dlbdtvar->aplanarity_jet_.value_;
    variableMap["circularity_jet"]=dlbdtvar->circularity_jet_.value_;
    variableMap["isotropy_jet"]=dlbdtvar->isotropy_jet_.value_;
    variableMap["C_jet"]=dlbdtvar->C_jet_.value_;
    variableMap["D_jet"]=dlbdtvar->D_jet_.value_;
    variableMap["transSphericity_jet"]=dlbdtvar->transSphericity_jet_.value_;
    variableMap["sphericity_tag"]=dlbdtvar->sphericity_tag_.value_;
    variableMap["aplanarity_tag"]=dlbdtvar->aplanarity_tag_.value_;
    variableMap["circularity_tag"]=dlbdtvar->circularity_tag_.value_;
    variableMap["isotropy_tag"]=dlbdtvar->isotropy_tag_.value_;
    variableMap["C_tag"]=dlbdtvar->C_tag_.value_;
    variableMap["D_tag"]=dlbdtvar->D_tag_.value_;
    variableMap["transSphericity_tag"]=dlbdtvar->transSphericity_tag_.value_;
    variableMap["H0_jet"]=dlbdtvar->H0_jet_.value_;
    variableMap["H1_jet"]=dlbdtvar->H1_jet_.value_;
    variableMap["H2_jet"]=dlbdtvar->H2_jet_.value_;
    variableMap["H3_jet"]=dlbdtvar->H3_jet_.value_;
    variableMap["H4_jet"]=dlbdtvar->H4_jet_.value_;
    variableMap["R1_jet"]=dlbdtvar->R1_jet_.value_;
    variableMap["R2_jet"]=dlbdtvar->R2_jet_.value_;
    variableMap["R3_jet"]=dlbdtvar->R3_jet_.value_;
    variableMap["R4_jet"]=dlbdtvar->R4_jet_.value_;
    variableMap["H0_tag"]=dlbdtvar->H0_tag_.value_;
    variableMap["H1_tag"]=dlbdtvar->H1_tag_.value_;
    variableMap["H2_tag"]=dlbdtvar->H2_tag_.value_;
    variableMap["H3_tag"]=dlbdtvar->H3_tag_.value_;
    variableMap["H4_tag"]=dlbdtvar->H4_tag_.value_;
    variableMap["R1_tag"]=dlbdtvar->R1_tag_.value_;
    variableMap["R2_tag"]=dlbdtvar->R2_tag_.value_;
    variableMap["R3_tag"]=dlbdtvar->R3_tag_.value_;
    variableMap["R4_tag"]=dlbdtvar->R4_tag_.value_;
    // ==================================================
    // evaluate BDT of current category

  delete dlbdtvar;
//TODO uncomment reader line and delete the next line
//           return -3.0;
    return readerMap[category]->EvaluateMVA("BDT");
}

std::string DLBDTClassifier::GetCategoryOfLastEvaluation() const{
    return category;
}

std::map<std::string,float> DLBDTClassifier::GetVariablesOfLastEvaluation() const{
    return variableMap;
}

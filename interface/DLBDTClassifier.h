#ifndef TTH_DLBDTCLASSIFIER_H
#define TTH_DLBDTCLASSIFIER_H
#include <vector>
#include <map>
#include <math.h> 
#include "TLorentzVector.h"
#include "TMVA/Reader.h"
#include "TTH/CommonClassifier/interface/DLBDTVars.h"


// class to evaluate lepton plus jets BDT set
class DLBDTClassifier{
  
public:

    DLBDTClassifier(std::string weightpath="");
    ~DLBDTClassifier();

    // Call this method to return the BDT output, provide all necessary inputs. Jet CSV should be sorted the same way as jet p4. 
    // We could also write a class to contain the jet CSV and p4 information
    double GetBDTOutput(const std::vector<TLorentzVector>& selectedLeptonP4, 
			const std::vector<double>& selectedLeptonCharge,
			const std::vector<TLorentzVector>& selectedJetP4, 
			const std::vector<double>& selectedJetCSV, 
// 			const std::vector<TLorentzVector>& looseSelectedJetP4, 
// 			const std::vector<double>& looseSelectedJetCSV, 
			const TLorentzVector& metP4);
  
    // returns the category of the last evaluated Event
    std::string GetCategoryOfLastEvaluation() const;
    
    // return the variable names and their values for the last evaluated event
    std::map<std::string,float> GetVariablesOfLastEvaluation() const;


private:  
    void SetCategory(const std::vector<TLorentzVector>& selectedLeptonP4, 
		     const std::vector<TLorentzVector>& selectedJetP4, 
		     const std::vector<double>& selectedJetCSV);
    void ResetVariableMap();

    const double btagMcut;
    
    std::string category;
    std::map<std::string,TMVA::Reader*> readerMap;
    std::map<std::string,float> variableMap;
//     MvaVariablesEventClassification dlbdtvar;

};

#endif

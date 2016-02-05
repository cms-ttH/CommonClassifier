#ifndef TTH_MEMBDTCLASSIFIER_H
#define TTH_MEMBDTCLASSIFIER_H
#include <vector>
#include <map>
#include <math.h> 
#include "TLorentzVector.h"
#include "TMVA/Reader.h"
#include "TTH/CommonClassifier/interface/CommonBDTvars.h"


// class to evaluate lepton plus jets BDT set
class MEMBDTClassifier{
  
public:

    MEMBDTClassifier(std::string weightpath="");
    ~MEMBDTClassifier();

    // Call this method to return the BDT output, provide all necessary inputs. Jet CSV should be sorted the same way as jet p4. 
    // We could also write a class to contain the jet CSV and p4 information
    double GetBDTOutput(const std::vector<TLorentzVector>& selectedLeptonP4, 
			const std::vector<TLorentzVector>& selectedJetP4, 
			const std::vector<double>& selectedJetCSV, 
			const std::vector<TLorentzVector>& looseSelectedJetP4, 
			const std::vector<double>& looseSelectedJetCSV, 
			const TLorentzVector& metP4,
		        const double MEM_p);
  
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
    CommonBDTvars bdtvar;

};

#endif

#ifndef MEMCLASSIFIER_H
#define MEMCLASSIFIER_H

#include "TTH/MEIntegratorStandalone/interface/Integrand.h"
#include "TTH/MEIntegratorStandalone/interface/JetLikelihood.h"
#include "TFile.h"
#include "TH3D.h"
#include "TLorentzVector.h"

class MEMResult {
public:
  //likelihood ratio
  double p;

  //individual signal and background probabilities
  double p_sig;
  double p_bkg;

  //Integration uncertainties of the probabilities
  double p_err_sig;
  double p_err_bkg;
  
  //Number of permutations per hypothesis 
  double n_perm_sig;
  double n_perm_bkg;
};

class MEMClassifier{
  
public:

  //The constructor loads the transfer functions and b-tag PDF-s
  MEMClassifier();
  ~MEMClassifier();

  // Call this method to return the BDT output, provide all necessary inputs. Jet CSV should be sorted the same way as jet p4. 
  // We could also write a class to contain the jet CSV and p4 information
  MEMResult GetOutput(
    const std::vector<TLorentzVector>& selectedLeptonP4,
    const std::vector<double>& selectedLeptonCharge,
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    const std::vector<TLorentzVector>& looseSelectedJetP4,
    const std::vector<double>& looseSelectedJetCSV,
    TLorentzVector& metP4
  );

  // returns the category of the last evaluated Event
  std::string GetCategoryOfLastEvaluation() const;

  double GetBTagLikelihoodRatio(
    const std::vector<TLorentzVector>& selectedJetP4,
    const std::vector<double>& selectedJetCSV,
    std::vector<unsigned int>& out_best_perm
  );


private:
  //Holds the transfer functions
  TFile* transfers;
  //holds the b-tag PDF-s
  TFile* btagfile;

  //This is the MEM workhorse from the ETH side
  MEM::Integrand* integrand;
  MEM::MEMConfig cfg;

  MEM::JetLikelihood* blr;

  //Convenience functions to construct MEM input objects
  MEM::Object* make_jet(double pt, double eta, double phi, double mass, double csv) const;
  MEM::Object* make_lepton(double pt, double eta, double phi, double mass, double charge) const;
  
  // Returns the transfer function corresponding to a jet flavour and eta
  TF1* getTransferFunction(const char* flavour, double eta) const;
  double GetJetBProbability(const char* flavour, double pt, double eta, double bdisc);
  MEM::JetProbability GetJetBProbabilities(const TLorentzVector& p4, double bdisc);
  TH3D* GetBTagPDF(const char* flavour);

  long unsigned int numMaxJets = 8;
};

#endif


#ifndef MEMCLASSIFIER_H
#define MEMCLASSIFIER_H

#include "TTH/MEIntegratorStandalone/interface/Integrand.h"
#include "TTH/MEIntegratorStandalone/interface/JetLikelihood.h"
#include "TFile.h"
#include "TH3D.h"
#include "TLorentzVector.h"

class MEMResult {
public:
    double blr_4b;
    double blr_2b;

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

class MEMClassifier {

public:

    // Jet type: Needed to decide:
    //   - which jets to put into which slot of the MEM
    //   - which transfer function to use

    // Hypothesis
    enum Hypothesis {
        DEBUG,         // Don't run the MEM. Print debug info
        SL_0W2H2T,     // Default SL MEM: Integrate over light jets
        SL_1W2H2T,     // Default SL MEM: Integrate over light jets
        SL_2W2H2T,     // Fully reconstructed hypothesis
        SL_2W2H2T_SJ,  // Boosted SL MEM: 2 light jets + bjets
        DL_0W2H2T,     // Default DL MEM
    };

    enum JetType {
        RESOLVED,
        BOOSTED_LIGHT,
        BOOSTED_B
    };

    enum Systematic {
        NOMINAL,
        JESUP,
        JESDOWN,
        JERUP,
        JERDOWN
    };

    //The constructor loads the transfer functions and b-tag PDF-s
    MEMClassifier(int verbosity, const char* _btag_prefix);
    MEMClassifier();
    ~MEMClassifier();

    // Call this method to return the MEM output, provide all necessary inputs.
    // Jet CSV and type should be sorted the same way as jet p4.
    // We could also write a class to contain the jet CSV, type, and p4 information
    MEMResult GetOutput(
        const Hypothesis hypo,
        const std::vector<TLorentzVector>& selectedLeptonP4,
        const std::vector<double>& selectedLeptonCharge,
        const std::vector<TLorentzVector>& selectedJetP4,
        const std::vector<double>& selectedJetCSV,
        const std::vector<JetType>& selectedJetType,
        const std::vector<TLorentzVector>& looseSelectedJetP4,
        const std::vector<double>& looseSelectedJetCSV,
        TLorentzVector& metP4,
        int ncalls=-1
    );

    //Default method to get the MEM output
    MEMResult GetOutput(
        const std::vector<TLorentzVector>& selectedLeptonP4,
        const std::vector<double>& selectedLeptonCharge,
        const std::vector<TLorentzVector>& selectedJetP4,
        const std::vector<double>& selectedJetCSV,
        const std::vector<JetType>& selectedJetType,
        TLorentzVector& metP4
    );

    void setup_mem(
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
    );

    void setup_mem_impl(
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
    );

    void setup_mem_sl_2w2h2t_sj(
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
    );

    // returns the category of the last evaluated Event
    std::string GetCategoryOfLastEvaluation() const;

    double GetBTagLikelihoodRatio(
        const std::vector<TLorentzVector>& selectedJetP4,
        const std::vector<double>& selectedJetCSV,
        std::vector<unsigned int>& out_best_perm,
        double& out_P_4b,
        double& out_P_2b
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
    MEM::Object* make_jet(double pt, double eta, double phi, double mass, double istagged, double csv, bool is_subjet) const;
    MEM::Object* make_lepton(double pt, double eta, double phi, double mass, double charge) const;

    // Returns the transfer function corresponding to a jet flavour and eta
    TF1* getTransferFunction(const char* flavour, double eta) const;
    double GetJetBProbability(const char* prefix, const char* flavour, double pt, double eta, double bdisc);
    MEM::JetProbability GetJetBProbabilities(const TLorentzVector& p4, double bdisc);
    
    TH3D* GetBTagPDF(const char* prefix, const char* flavour);

    long unsigned int numMaxJets = 8;
    long unsigned int numMaxJetsBLR = 8;
    const char* btag_prefix;
};

#endif

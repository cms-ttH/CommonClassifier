#ifndef TTH_DLBDTVARS_H
#define TTH_DLBDTVARS_H
#include <string>
#include <Rtypes.h>

#include <TVector.h>
#include <TVectorD.h>
#include <TVector3.h>
#include <Math/Vector3D.h>
#include <TLorentzVector.h>

#include "TMatrixDSym.h"





// /// Templated struct which defines all relevant parameters for MVA input variables
// template<class T> struct DLBDTMvaVariable{
//     DLBDTMvaVariable(const char* name):
//         branch_(0), name_(name){}
//     
// public:
//     T value_;
//     TBranch* branch_;
//     
//     std::string name()const{return name_;}
//     char type()const{return type_;}
//     
// private:
//     const char* name_;
//     static constexpr char type_ = 'I';
// };



/// Struct which defines all relevant parameters for MVA input variables of type int
struct DLBDTMvaVariableInt{
    DLBDTMvaVariableInt(const char* name):
        value_(-999), valueFloat_(-999.F), name_(name){}
    
public:
    void setValue(const int value){value_ = value; valueFloat_ = static_cast<float>(value);}
    
    Int_t value_;
    Float_t valueFloat_; // Needed as newer root versions do not allow Int in TMVA reader anymore !?!
   
    std::string name()const{return name_;}
    const char* type()const{return type_;}
    
private:
    const char* name_;
    static constexpr const char* type_ = "I";
};



/// Struct which defines all relevant parameters for MVA input variables of type float
struct DLBDTMvaVariableFloat{
    DLBDTMvaVariableFloat(const char* name):
        value_(-999.F), name_(name){}
    
public:
    void setValue(const float value){value_ = value;}
    
    Float_t value_;
    
    std::string name()const{return name_;}
    const char* type()const{return type_;}
    
private:
    const char* name_;
    static constexpr const char* type_ = "F";
};



/// Base class for holding MVA input variables
class DLBDTMvaVariablesBase{
    
public:
    
    /// Empty constructor
    DLBDTMvaVariablesBase();
    
    /// Constructor setting up event weight
//     DLBDTMvaVariablesBase(const double& eventWeight);
        DLBDTMvaVariablesBase(const double& eventWeight);

    /// Destructor
    virtual ~DLBDTMvaVariablesBase(){}
        
    /// Clear the MVA input variables, i.e. delete all pointers properly
    static void clearVariables(std::vector<DLBDTMvaVariablesBase*>& v_DLBDTMvaVariables);

    /// Event weight including all scale factors
    DLBDTMvaVariableFloat eventWeight_;
    
    
    
private:
    
    static constexpr const char* name_eventWeight_ = "eventWeight";
};




//------------------------------------------------------------------------------------

/*

class RecoObjects;
namespace tth{
    class RecoObjectIndices;
}*/


class DLBDTMvaVariablesEventClassification : public DLBDTMvaVariablesBase{
    
public:
    
    /// Empty constructor
    DLBDTMvaVariablesEventClassification();
    
    /// Constructor setting up input variables from physics objects
    DLBDTMvaVariablesEventClassification(const int multiplicity_jets,
                                    const double& btagDiscriminatorAverage_tagged,
                                    const double& btagDiscriminatorAverage_untagged,
                                    const double& minDeltaR_jet_jet,
                                    const double& minDeltaR_tag_tag,
                                    const double& avgDeltaR_jet_jet,
                                    const double& avgDeltaR_jet_tag,
                                    const double& avgDeltaR_tag_tag,
                                    const double& ptSum_jets_leptons,
                                    const int multiplicity_higgsLikeDijet15,
                                    const double& mass_higgsLikeDijet,
                                    const double& mass_higgsLikeDijet2,
                                    const double& mass_jet_jet_min_deltaR,
                                    const double& mass_tag_tag_min_deltaR,
                                    const double& mass_jet_tag_min_deltaR,
                                    const double& mass_tag_tag_max_mass,
                                    const double& median_mass_jet_jet,
                                    const double& maxDeltaEta_jet_jet,
                                    const double& maxDeltaEta_tag_tag,
                                    const double& HT_jets,
                                    const double& HT_tags,
                                    const double& pT_jet_jet_min_deltaR,
                                    const double& pT_jet_tag_min_deltaR,
                                    const double& pT_tag_tag_min_deltaR,
                                    const double& mass_jet_jet_jet_max_pT,
                                    const double& mass_jet_tag_tag_max_pT,
                                    const double& centrality_jets_leps,
                                    const double& centrality_tags,
                                    const double& twist_jet_jet_max_mass,
                                    const double& twist_jet_tag_max_mass,
                                    const double& twist_tag_tag_max_mass,
                                    const double& twist_tag_tag_min_deltaR,
				    const double& sphericity_jet,
				    const double& aplanarity_jet,
				    const double& circularity_jet,
				    const double& isotropy_jet,
				    const double& C_jet,
				    const double& D_jet,
				    const double& transSphericity_jet,
				    const double& sphericity_tag,
				    const double& aplanarity_tag,
				    const double& circularity_tag,
				    const double& isotropy_tag,
				    const double& C_tag,
				    const double& D_tag,
				    const double& transSphericity_tag,
				    const double& H0_jet,
				    const double& H1_jet,
				    const double& H2_jet,
				    const double& H3_jet,
				    const double& H4_jet,
				    const double& R1_jet,
				    const double& R2_jet,
				    const double& R3_jet,
				    const double& R4_jet,
				    const double& H0_tag,
				    const double& H1_tag,
				    const double& H2_tag,
				    const double& H3_tag,
				    const double& H4_tag,
				    const double& R1_tag,
				    const double& R2_tag,
				    const double& R3_tag,
				    const double& R4_tag);
    
    /// Destructor
    ~DLBDTMvaVariablesEventClassification(){}
    
    /// Fill the MVA input structs for one event
    static DLBDTMvaVariablesEventClassification* fillVariables(const std::vector<TLorentzVector>& leptons, const std::vector<double>& selectedLeptonCharge,
				   const std::vector<TLorentzVector>& jets, 
				   const std::vector<double>& jetBtags, const double btagWP=0.89);
    
    
    
    // The variables needed for MVA
    
    // FIXME: describe each variable in doxygen
    /// Variables for MVA
    DLBDTMvaVariableInt multiplicity_jets_;
    DLBDTMvaVariableFloat btagDiscriminatorAverage_tagged_;
    DLBDTMvaVariableFloat btagDiscriminatorAverage_untagged_;
    DLBDTMvaVariableFloat minDeltaR_jet_jet_;
    DLBDTMvaVariableFloat minDeltaR_tag_tag_;
    DLBDTMvaVariableFloat avgDeltaR_jet_jet_;
    DLBDTMvaVariableFloat avgDeltaR_jet_tag_;
    DLBDTMvaVariableFloat avgDeltaR_tag_tag_;
    DLBDTMvaVariableFloat ptSum_jets_leptons_;
    DLBDTMvaVariableInt multiplicity_higgsLikeDijet15_;
    DLBDTMvaVariableFloat mass_higgsLikeDijet_;
    DLBDTMvaVariableFloat mass_higgsLikeDijet2_;
        
    DLBDTMvaVariableFloat mass_jet_jet_min_deltaR_;
    DLBDTMvaVariableFloat mass_tag_tag_min_deltaR_;
    DLBDTMvaVariableFloat mass_jet_tag_min_deltaR_;

    DLBDTMvaVariableFloat mass_tag_tag_max_mass_;
    DLBDTMvaVariableFloat median_mass_jet_jet_;

    DLBDTMvaVariableFloat maxDeltaEta_jet_jet_;
    DLBDTMvaVariableFloat maxDeltaEta_tag_tag_;

    DLBDTMvaVariableFloat HT_jets_;
    DLBDTMvaVariableFloat HT_tags_;

    DLBDTMvaVariableFloat pT_jet_jet_min_deltaR_;
    DLBDTMvaVariableFloat pT_jet_tag_min_deltaR_;
    DLBDTMvaVariableFloat pT_tag_tag_min_deltaR_;

    DLBDTMvaVariableFloat mass_jet_jet_jet_max_pT_;
    DLBDTMvaVariableFloat mass_jet_tag_tag_max_pT_;

    DLBDTMvaVariableFloat centrality_jets_leps_;
    DLBDTMvaVariableFloat centrality_tags_;

    DLBDTMvaVariableFloat twist_jet_jet_max_mass_;
    DLBDTMvaVariableFloat twist_jet_tag_max_mass_;
    DLBDTMvaVariableFloat twist_tag_tag_max_mass_;

    DLBDTMvaVariableFloat twist_tag_tag_min_deltaR_;

    //Event shape variables
    DLBDTMvaVariableFloat sphericity_jet_;
    DLBDTMvaVariableFloat aplanarity_jet_;
    DLBDTMvaVariableFloat circularity_jet_;
    DLBDTMvaVariableFloat isotropy_jet_;
    DLBDTMvaVariableFloat C_jet_;
    DLBDTMvaVariableFloat D_jet_;
    DLBDTMvaVariableFloat transSphericity_jet_;

    DLBDTMvaVariableFloat sphericity_tag_;
    DLBDTMvaVariableFloat aplanarity_tag_;
    DLBDTMvaVariableFloat circularity_tag_;
    DLBDTMvaVariableFloat isotropy_tag_;
    DLBDTMvaVariableFloat C_tag_;
    DLBDTMvaVariableFloat D_tag_;
    DLBDTMvaVariableFloat transSphericity_tag_;

    DLBDTMvaVariableFloat H0_jet_;
    DLBDTMvaVariableFloat H1_jet_;
    DLBDTMvaVariableFloat H2_jet_;
    DLBDTMvaVariableFloat H3_jet_;
    DLBDTMvaVariableFloat H4_jet_;
    DLBDTMvaVariableFloat R1_jet_;
    DLBDTMvaVariableFloat R2_jet_;
    DLBDTMvaVariableFloat R3_jet_;
    DLBDTMvaVariableFloat R4_jet_;

    DLBDTMvaVariableFloat H0_tag_;
    DLBDTMvaVariableFloat H1_tag_;
    DLBDTMvaVariableFloat H2_tag_;
    DLBDTMvaVariableFloat H3_tag_;
    DLBDTMvaVariableFloat H4_tag_;
    DLBDTMvaVariableFloat R1_tag_;
    DLBDTMvaVariableFloat R2_tag_;
    DLBDTMvaVariableFloat R3_tag_;
    DLBDTMvaVariableFloat R4_tag_;


    class EventShapeVariables {

    public:
      /// Constructor from XYZ coordinates
      explicit EventShapeVariables(const std::vector<TLorentzVector>& inputVectors);
            
      /// Default destructor  
      ~EventShapeVariables(){};
      
      /// The return value is 1 for spherical events and 0 for events linear in r-phi.
      double isotropy(const unsigned int& numberOfSteps = 1000) const;
      /// The return value is 1 for spherical and 0 linear events in r-phi.
      double circularity(const unsigned int& numberOfSteps = 1000) const;
      /// 1.5*(v1+v2) where 0<=v1<=v2<=v3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 1 for spherical, 3/4 for 
      /// plane and 0 for linear events
      double sphericity(double = 2.)  const;
      /// 1.5*v1 where 0<=v1<=v2<=v3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return values are 0.5 for spherical and 0 
      /// for plane and linear events
      double aplanarity(double = 2.)  const;
      /// 3.*(v1*v2+v1*v3+v2*v3) where 0<=v1<=v2<=v3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
      /// and measures the 3-jet structure of the event (C vanishes for a "perfect" 2-jet event)
      double C(double = 2.) const;
      /// 27.*(v1*v2*v3) where 0<=v1<=v2<=v3 are the eigenvalues of the momemtum tensor 
      /// sum{p_j[a]*p_j[b]}/sum{p_j**2} normalized to 1. Return value is between 0 and 1 
      /// and measures the 4-jet structure of the event (D vanishes for a planar event)
      double D(double = 2.) const;
      /// 2.*v2/(v1+v2) where 0<=v1<=v2<=v3 are the eigenvalues of the momemtum tensor. Return value is between 0 and 1
      /// and measures "isotropic" structore for a value of 1 and "pencile-like" limit for value of 0
      double transSphericity(double = 2.)  const;
      
      /// Fox Wolfram moment calculations
      double H(int order) const;
      /// Zeroth moment to be used
      double ZerothMoment() const;
      /// Ratio between one of the Fox Wolfram moment to the 0-th Fox Wolfram moment
      double R(int order) const;
      
    private:
      /// Helper function to fill the 3 dimensional momentum tensor from the inputVectors
      TMatrixDSym compMomentumTensor(double = 2.) const;
      TVectorD compEigenValues(double = 2.) const;
      
      /// Cashing of input vectors
      std::vector<ROOT::Math::XYZVector> inputVectors_;

      /// Method used to convert vector of TLorentzVector to XYZVector type
      std::vector<ROOT::Math::XYZVector> makeVecForEventShape(const std::vector<TLorentzVector>& jets);
    };

    class FoxWolframMoments {
      
    public:
      FoxWolframMoments(int order = 4);
      ~FoxWolframMoments(){};
      
      /// Compute given input vector, which is a collection of physics objects
      void Compute(const std::vector<ROOT::Math::XYZVector>& inputVectors);
      void Reset();

      /// Method of class
      const TVector& Moments()  const     { return _FWarray; }   
      const TVector& SumArray() const     { return _sumarray; } 
      double H(int order)   const     { return _FWarray(order); }
      double ZerothMoment() const     { return _FWarray(0); } 
      double R(int order) const;    // normalized to zeroth-moment

      static double Legendre(int l, int m, double x);
      
    private:
      int _nmom;
      TVector _FWarray;
      TVector _sumarray;

    };

private:
    
    // The names associated to the variables
    
    static constexpr const char* name_multiplicity_jets_ = "multiplicity_jets";
    static constexpr const char* name_btagDiscriminatorAverage_tagged_  = "btagDiscriminatorAverage_tagged";
    static constexpr const char* name_averageBtagDiscriminatorUntagged_ = "btagDiscriminatorAverage_untagged";
    static constexpr const char* name_minDeltaR_jet_jet_  = "minDeltaR_jet_jet";
    static constexpr const char* name_minDeltaR_tag_tag_  = "minDeltaR_tag_tag";
    static constexpr const char* name_avgDeltaR_jet_jet_  = "avgDeltaR_jet_jet";
    static constexpr const char* name_avgDeltaR_jet_tag_  = "avgDeltaR_jet_tag";
    static constexpr const char* name_avgDeltaR_tag_tag_  = "avgDeltaR_tag_tag";
    static constexpr const char* name_ptSum_jets_leptons_ = "ptSum_jets_leptons";
    static constexpr const char* name_multiplicity_higgsLikeDijet15_ = "multiplicity_higgsLikeDijet15";
    static constexpr const char* name_mass_higgsLikeDijet_  = "mass_higgsLikeDijet";
    static constexpr const char* name_mass_higgsLikeDijet2_ = "mass_higgsLikeDijet2";
    
    static constexpr const char* name_mass_jet_jet_min_deltaR_ = "mass_jet_jet_min_deltaR";
    static constexpr const char* name_mass_tag_tag_min_deltaR_ = "mass_tag_tag_min_deltaR";    
    static constexpr const char* name_mass_jet_tag_min_deltaR_ = "mass_jet_tag_min_deltaR";

    static constexpr const char* name_mass_tag_tag_max_mass_ = "mass_tag_tag_max_mass";
    static constexpr const char* name_median_mass_jet_jet_   = "median_mass_jet_jet";

    static constexpr const char* name_maxDeltaEta_jet_jet_ = "maxDeltaEta_jet_jet";
    static constexpr const char* name_maxDeltaEta_tag_tag_ = "maxDeltaEta_tag_tag";

    static constexpr const char* name_HT_jets_ = "HT_jets";
    static constexpr const char* name_HT_tags_ = "HT_tags";

    static constexpr const char* name_pT_jet_jet_min_deltaR_ = "pT_jet_jet_min_deltaR";
    static constexpr const char* name_pT_jet_tag_min_deltaR_ = "pT_jet_tag_min_deltaR";
    static constexpr const char* name_pT_tag_tag_min_deltaR_ = "pT_tag_tag_min_deltaR";

    static constexpr const char* name_mass_jet_jet_jet_max_pT_ = "mass_jet_jet_jet_max_pT";
    static constexpr const char* name_mass_jet_tag_tag_max_pT_ = "mass_jet_tag_tag_max_pT";

    static constexpr const char* name_centrality_jets_leps_    = "centrality_jets_leps";
    static constexpr const char* name_centrality_tags_         = "centrality_tags";
    
    static constexpr const char* name_twist_jet_jet_max_mass_ = "twist_jet_jet_max_mass";
    static constexpr const char* name_twist_jet_tag_max_mass_ = "twist_jet_tag_max_mass";
    static constexpr const char* name_twist_tag_tag_max_mass_ = "twist_tag_tag_max_mass";
    
    static constexpr const char* name_twist_tag_tag_min_deltaR_ = "twist_tag_tag_min_deltaR";

    // Event shape variables
    static constexpr const char* name_sphericity_jet_  = "sphericity_jet";
    static constexpr const char* name_aplanarity_jet_  = "aplanarity_jet";
    static constexpr const char* name_circularity_jet_ = "circularity_jet";
    static constexpr const char* name_isotropy_jet_    = "isotropy_jet";
    static constexpr const char* name_C_jet_ = "C_jet";
    static constexpr const char* name_D_jet_ = "D_jet";
    static constexpr const char* name_transSphericity_jet_ = "transSphericity_jet";

    static constexpr const char* name_sphericity_tag_  = "sphericity_tag";
    static constexpr const char* name_aplanarity_tag_  = "aplanarity_tag";
    static constexpr const char* name_circularity_tag_ = "circularity_tag";
    static constexpr const char* name_isotropy_tag_    = "isotropy_tag";
    static constexpr const char* name_C_tag_ = "C_tag";
    static constexpr const char* name_D_tag_ = "D_tag";
    static constexpr const char* name_transSphericity_tag_ = "transSphericity_tag";

    static constexpr const char* name_H0_jet_ = "H0_jet";
    static constexpr const char* name_H1_jet_ = "H1_jet";
    static constexpr const char* name_H2_jet_ = "H2_jet";
    static constexpr const char* name_H3_jet_ = "H3_jet";
    static constexpr const char* name_H4_jet_ = "H4_jet";
    static constexpr const char* name_R1_jet_ = "R1_jet";
    static constexpr const char* name_R2_jet_ = "R2_jet";
    static constexpr const char* name_R3_jet_ = "R3_jet";
    static constexpr const char* name_R4_jet_ = "R4_jet";

    static constexpr const char* name_H0_tag_ = "H0_tag";
    static constexpr const char* name_H1_tag_ = "H1_tag";
    static constexpr const char* name_H2_tag_ = "H2_tag";
    static constexpr const char* name_H3_tag_ = "H3_tag";
    static constexpr const char* name_H4_tag_ = "H4_tag";
    static constexpr const char* name_R1_tag_ = "R1_tag";
    static constexpr const char* name_R2_tag_ = "R2_tag";
    static constexpr const char* name_R3_tag_ = "R3_tag";
    static constexpr const char* name_R4_tag_ = "R4_tag";
};






#endif










#include "TTH/CommonClassifier/interface/MEMClassifier.h"
#include "TFile.h"
#include <iostream>

using namespace std;
using namespace MEM;

const TLorentzVector p4(double pt, double eta, double phi, double mass) {
    TLorentzVector lv;
    lv.SetPtEtaPhiM(pt, eta, phi, mass);
    return lv;
}

int main(){

  //Setup the MEM
  MEMClassifier mem;

  //Add some objects to the MEM
  auto jets_p4 = {
       p4(340.654388428, -2.27929639816, 1.07088756561, 28.3690547943),
       p4(169.823135376, -1.09558558464, -1.68332433701, 19.2100219727),
       p4(106.471191406, -1.73152184486, -2.89366841316, 14.1999740601),
       p4(91.0636901855, -1.16678476334, -2.92009735107, 11.6663913727),
       p4(58.3697357178, -1.38574934006, -0.656430959702, 8.05632019043),
       p4(31.2667369843, 0.307675540447, -0.434196174145, 5.55666637421),
       p4(30.9939250946, -0.466470509768, -2.50881528854, 6.00200891495)
  };
  
  auto leps_p4 = {
    p4(52.8751449585, -0.260020583868, -2.55171084404, 0.139569997787)
  };

  //create a MET
  TLorentzVector lv_met;
  lv_met.SetPtEtaPhiM(92.1731872559,0., -1.08158898354, 0.);
  for (int i=0; i<2; i++) {
    auto res = mem.GetOutput(
      MEMClassifier::Hypothesis::SL_0W2H2T,
      leps_p4,
      {-1},
      jets_p4,
      {
        0.0429882630706,
        0.990463197231,
        0.899696052074,
        0.979629218578,
        0.437245458364,
        0.996093869209,
        0.212953850627
      },
      {  
	MEMClassifier::JetType::RESOLVED,
	MEMClassifier::JetType::RESOLVED,
	MEMClassifier::JetType::RESOLVED,
	MEMClassifier::JetType::RESOLVED,
        MEMClassifier::JetType::RESOLVED,
        MEMClassifier::JetType::RESOLVED,
	MEMClassifier::JetType::RESOLVED,
      },
      {},
      {},
      lv_met
    );
    std::cout << "mem=" << res.p << std::endl;
  }
}

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
      p4(
        51.62411880493164, 
        -0.8125799298286438, 
        -3.0860791206359863, 
        7.721531867980957
      ), 
      p4(
        51.45940399169922, 
        -2.1350724697113037, 
        2.794322967529297, 
        6.909081935882568
      ), 
      p4(
        38.61643981933594, 
        -1.6606312990188599, 
        0.2091505527496338, 
        5.794722080230713
      ), 
      p4(
        22.914491653442383, 
        -0.4653875529766083, 
        -0.5745444893836975, 
        3.8986964225769043
      )
  };
  
  auto leps_p4 = {
    p4(
        63.742523193359375,
        -1.606768250465393,
        -0.6526610851287842,
        0.10570000112056732
    ),
    p4(
        30.206972122192383,
        -1.7477864027023315,
        1.7761988639831543,
        0.015261447988450527
    )
  };

  //create a MET
  TLorentzVector lv_met;
  lv_met.SetPtEtaPhiM(
      45.685523986816406,
      0.0,
      0.9771100282669067,
      0.0
  );
  for (int i=0; i<2; i++) {
    auto res = mem.GetOutput(
      MEMClassifier::Hypothesis::DL_0W2H2T,
      leps_p4,
      {-1, 1},
      jets_p4,
      {
        0.0429882630706,
        0.990463197231,
        0.899696052074,
        0.979629218578,
      },
      {  
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

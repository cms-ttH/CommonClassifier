#include "TTH/CommonClassifier/interface/MemBDTClassifier.h"
#include <iostream>

using namespace std;

const TLorentzVector p4(double pt, double eta, double phi, double mass) {
    TLorentzVector lv;
    lv.SetPtEtaPhiM(pt, eta, phi, mass);
    return lv;
}

int main(){

  //Setup the BDT
  MEMBDTClassifier bdt;

  //Add some objects to the BDT
  auto jets_p4 = {
    p4(242.816604614, -0.107542805374, 1.25506973267, 24.5408706665),
    p4(191.423553467, -0.46368226409, 0.750520706177, 30.5682048798),
    p4(77.6708831787, -0.709680855274, -2.53739523888, 10.4904966354),
    p4(235.892044067, -0.997860729694, -2.10646605492, 27.9887943268),
    p4(52.0134391785, -0.617823541164, -1.23360788822, 6.45914268494),
    p4(35.6511192322, 0.566395223141, -2.51394343376, 8.94268417358),
  };
  
  auto leps_p4 = {
    p4(52.8751449585, -0.260020583868, -2.55171084404, 0.139569997787)
  };

  //create a MET
  TLorentzVector lv_met;
  lv_met.SetPtEtaPhiM(92.1731872559,0., -1.08158898354, 0.);
  for (int i=0; i<3; i++) {
    auto result = bdt.GetBDTOutput(
				leps_p4,				
				jets_p4,
				{0.92, 0.95, 0.9, 0.1, 0.3, 0.99},
				{},
				{},
				lv_met,
				0.7
    );
    std::cout << "================================" << std::endl;
    std::cout << "bdtoutput=" << result << std::endl;
    std::cout << "bdtcategory=" << bdt.GetCategoryOfLastEvaluation() << std::endl;
    auto varMap = bdt.GetVariablesOfLastEvaluation();
    std::cout << "Name : Value of all potential BDT inputs " << std::endl;
    for (auto& i : varMap) {
	std::cout << i.first << " : " << i.second << std::endl;
    }
    std::cout << std::endl;
  }
}

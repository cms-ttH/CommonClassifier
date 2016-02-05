Common classifiers for ttH analysis
===================================



Setup
-----

~~~
cd $CMSSW_BASE/src
cmsenv
mkdir TTH
cd TTH
git clone https://github.com/cms-ttH/CommonClassifier.git
source CommonClassifier/setup/install_mem.sh
scram b
mem_test
bdt_test
~~~

Usage
-----
* Objects have to fulfill the cuts described here: https://twiki.cern.ch/twiki/bin/view/CMS/TTbarHbbRun2ReferenceAnalysis
* Loose jets are defined by the same cuts as the standard ak4-jets except for the p_T-cut which is p_T > 20 GeV instead of p_T > 30 GeV. The loose jet collection is inclusive and also contains the standard jets.
* The BDTs are trained and optimized on odd-numbered Events, to avoid bias they should only be evaluated on even-numbered events (edm::Event.id().event()%2==0)

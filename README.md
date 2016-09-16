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
* 

# Common classifier data format

## Input data

A tree with exactly this structure:

~~~
long run
long lumi
long event
int systematic //keep track of systematically variated events
int hypothesis //MEM hypothesis type (e.g. 0 for SL, 1 for DL etc)
int numcalls //MEM integration points

int nleps //varying number of leptons
//the following arrays should be of varying length, with buffer sizes of 2 
float leps_pt[nleps]
float leps_eta[nleps]
float leps_phi[nleps]
float leps_mass[nleps]
float leps_charge[nleps]

int njets //varying number of jets
//the following arrays should be of varying length, with buffer sizes of 10
float jets_pt[njets]
float jets_eta[njets]
float jets_phi[njets]
float jets_mass[njets]
float jets_csv[njets]
float jets_cmva[njets]
int jets_type[njets] //if jet is resolved, boosted

float met_pt
float met_phi
~~~

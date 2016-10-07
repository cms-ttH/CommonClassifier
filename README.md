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

# Running the CommonClassifier industrially

As discussed, we will make a common infrastructure to run the MEM on group-specific ntuples in a common way on either a local cluster or the CMS grid (CRAB3). The following diagram explains the principle:
~~~
ntuplization chain:
group ntuple -> CommonClassifier input ntuple -> CommonClassifier on the cluster/grid -> CommonClassifier output ntuple

analysis of ntuples:
|--------------------------------|
|    group-specific ntuple       |
|     via (run, lumi, event)     | -> histograms with BDT, MEM, ...
| CommonClassifier output ntuple | 
|--------------------------------|
~~~

Technically, the access of the CommonClassifier output ntuple from the histogramming code can be done using the `(run, lumi, event)` lookup database at https://github.com/kit-cn-cms/MEMDataBase

## CommonClassifier input ntuple

In order to run the CommonClassifier using the gridding infractructure, you must export your private ntuples to a TTree with exactly this structure:

~~~
long run
long lumi
long event
int systematic //keep track of systematically variated events, according to enum MEMClassifier::Systematics
int hypothesis //MEM hypothesis type (e.g. 0 for SL, 1 for DL etc), set to -1 now if you want the MEM to be calculated, -2 if you don't want the MEM to be calculated (e.g. 2-tag event)
int numcalls //MEM integration points, set to -1 now

int nleps //varying number of leptons
//the following arrays should be of varying length, with buffer sizes of 2 
float lep_pt[nleps]
float lep_eta[nleps]
float lep_phi[nleps]
float lep_mass[nleps]
float lep_charge[nleps]

int njets //varying number of jets
//the following arrays should be of varying length, with buffer sizes of 10
float jet_pt[njets]
float jet_eta[njets]
float jet_phi[njets]
float jet_mass[njets]
float jet_csv[njets]
float jet_cmva[njets] // fill with -1 in case you don't have it
int jet_type[njets] //if jet is resolved, boosted, according to MEMClassifier::JetType enum

int nloose_jets //varying number of loose jets, i.e. jets with 20<pt<30 NOT in jets collection, set to 0 if you don't use loose jets (SL BDT will be incorrect) 
//the following arrays should be of varying length, with buffer sizes of 5
float loose_jet_pt[njets]
float loose_jet_eta[njets]
float loose_jet_phi[njets]
float loose_jet_mass[njets]
float loose_jet_csv[njets]
float loose_jet_cmva[njets] // fill with -1 in case you don't have it

float met_pt
float met_phi
~~~

An example tree can be found here: https://github.com/cms-ttH/CommonClassifier/blob/master/interface/intree.h, it's suggested to use this class in order to reduce errors from re-implementing this TTree.

## CommonClassifier output ntuple

The structure should be the following

~~~
long run
long lumi
long event
int systematic
int hypothesis
double bdt
double mem
~~~

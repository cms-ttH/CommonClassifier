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

As discussed, we will make a common gridding infrastructure to run the MEM on group-specific ntuples in a common way 
~~~

ntuple chain:
group ntuple -> CommonClassifier input ntuple -> CommonClassifier on the cluster/grid -> CommonClassifier output ntuple

analysis of ntuples:
--------------------------------
group-specific ntuple          |
                               | -> histograms with BDT, MEM, ...
CommonClassifier output ntuple | 
--------------------------------
~~~

Technically, the access of the CommonClassifier output ntuple from the histogramming code can be done using the `(run, lumi, event)` lookup database at https://github.com/kit-cn-cms/MEMDataBase

## CommonClassifier input ntuple

In order to run the CommonClassifier using the gridding infractructure, you must export your private ntuples to a TTree with exactly this structure:

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

An example tree can be found here: https://github.com/cms-ttH/CommonClassifier/blob/master/interface/intree.h, it's suggested to use this class in order to reduce errors from re-implementing this TTree.

## CommonClassifier output ntuple

The proposed structure would be the following:

~~~
long run
long lumi
long event
int systematic
int hypothesis
double bdt
double mem
~~~

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
int hypothesis //MEM hypothesis type (e.g. 0 for SL, 1 for DL etc), set to -1 now
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

int nloose_jets //varying number of loose jets, i.e. jets with 20<pt<30 NOT in jets collection
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

The TTree should be called `tree`:

~~~
[jpata@t3ui17 gc]$ root ~/tth/gc/CommonClassifierEvents/GCb65634721d2b/Sep14_leptonic_nome_v1__ttHTobb_M125_13TeV_powheg_pyt
>root [0]
Attaching file /mnt/t3nfs01/data01/shome/jpata/tth/gc/CommonClassifierEvents/GCb65634721d2b/Sep14_leptonic_nome_v1__ttHTobb_M125_13TeV_powheg_pythia8.root as _file0...
S(TFile *) 0x2657980
root [1] tree->Scan()
***********************************************************************************************************************
*    Row   * Instance * systemati *     njets *    jet_pt *   jet_eta *   jet_phi *  jet_mass *   jet_csv *  jet_cmva *
***********************************************************************************************************************
*        0 *        0 *         0 *         6 * 177.14239 * -0.052165 * -2.828265 * 20.478263 * 0.9895136 * 0.9971207 *
*        0 *        1 *         0 *         6 * 69.510925 * 0.7877875 * 0.3808440 * 7.2543778 * 0.0905931 * -0.857876 *
*        0 *        2 *         0 *         6 * 66.424903 * 0.4279073 * 1.5178282 * 9.6658573 * 0.1186879 * -0.962871 *
*        0 *        3 *         0 *         6 * 65.595512 * 0.0620128 * 1.1088844 * 8.2773714 * 0.1906057 * -0.966070 *
*        0 *        4 *         0 *         6 * 55.845230 * -0.117159 * 2.4891586 * 7.1776804 * 0.9706692 * 0.9264151 *
*        0 *        5 *         0 *         6 * 37.665302 * 1.4149088 * -0.584131 * 5.0920801 * 0.9466056 * 0.8015335 *
*        1 *        0 *         0 *         6 * 288.93145 * -0.731546 * -2.582718 * 36.371589 * 0.9566396 * 0.9597303 *
*        1 *        1 *
~~~

An example tree can be found here: https://github.com/cms-ttH/CommonClassifier/blob/master/interface/intree.h, it's suggested to use this class in order to reduce errors from re-implementing this TTree.

TODO: describe how the CommonClassifier input ntuple will be distributed so that it will be accessible via crab.

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

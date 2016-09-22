//created with TTHNtupleAnalyzer/python/headergen.py MEAnalysis/interface/commonclassifier_intree_template.h CommonClassifier/interface/intree.h MEAnalysis/test/commonclassifier_intree.py
#ifndef COMMONCLASSIFIER_INPUT_TREE
#define COMMONCLASSIFIER_INPUT_TREE

#include <TTree.h>
#include <cmath>
#include <string>

//HEADERGEN_DEFINES

//macros to initialize 1D and 2D (square) arrays
//x is the array, n is the size, y is the initialized value
#define SET_ZERO(x,n,y) for(int i=0;i<n;i++) {x[i]=y;}
#define SET_ZERO_2(x,n,m,y) for(int i=0;i<n;i++) { for(int j=0;j<m;j++) { x[i][j]=y; } }

/*
This is a simple wrapper class for the TTH-specific flat data format.
To use it, one should load the input file in the standard way using
TFile* f = new TFile("ntuple.root");
TTree* _ttree = (TTree*)f->Get("tthNtupleAnalyzer/events");
and then initialize the class using
CommonClassifierInputTree tree(_ttree);
CommonClassifierInputTree contains the C++ variables for all the branches and functions to conveniently set them.
To attach the branches in the read mode (call SetBranchAddress), call
tree.set_branch_addresses();
outside the event loop.
 You can loop over the events in the standard way
 for (unsigned int i=0; i < _ttree->GetEntries(); i++) {
     tree.loop_initialize(); // <-- this makes sure all the branch variables are cleared from the previous entry
     _ttree->GetEntry(i); // <--- loads the branch contents into the branch variables
     for (int njet=0; njet < tree.n__jet; njet++) {
         float x = tree.jet__pt[njet];
         //do something with the jet pt 
     }
*/
class CommonClassifierInputTree {
public:
    CommonClassifierInputTree(TTree* _tree) { tree = _tree; };
    TTree* tree;
   
        // Helper functions for accessing branches
    template <typename T> 
    T get_address(const std::string name) {
        auto* br = tree->GetBranch(name.c_str());
        if (br==0) {
            std::cerr << "ERROR: get_address CommonClassifierInputTree " << "branch " << name << " does not exist" << std::endl;
            throw std::exception();
        }
        auto* p = br->GetAddress();
        return reinterpret_cast<T>(p);
    }
    
    long run;
    long event;
    long lumi;
    int nleps;
    int njets;
    int hypothesis;
    int numcalls;
    int systematic;
    float met_pt;
    float met_phi;
    float lep_pt[2];
    float lep_eta[2];
    float lep_phi[2];
    float lep_mass[2];
    float lep_charge[2];
    float jet_pt[10];
    float jet_eta[10];
    float jet_phi[10];
    float jet_mass[10];
    float jet_csv[10];
    float jet_cmva[10];
    int jet_type[10];
    //HEADERGEN_BRANCH_VARIABLES
    //This comment is for automatic header generation, do not remove

    //initializes all branch variables
    void loop_initialize(void) {        
        run = 0;
        event = 0;
        lumi = 0;
        nleps = 0;
        njets = 0;
        hypothesis = 0;
        numcalls = 0;
        systematic = 0;
        met_pt = 0;
        met_phi = 0;
        SET_ZERO(lep_pt, 2, 0);
        SET_ZERO(lep_eta, 2, 0);
        SET_ZERO(lep_phi, 2, 0);
        SET_ZERO(lep_mass, 2, 0);
        SET_ZERO(lep_charge, 2, 0);
        SET_ZERO(jet_pt, 10, 0);
        SET_ZERO(jet_eta, 10, 0);
        SET_ZERO(jet_phi, 10, 0);
        SET_ZERO(jet_mass, 10, 0);
        SET_ZERO(jet_csv, 10, 0);
        SET_ZERO(jet_cmva, 10, 0);
        SET_ZERO(jet_type, 10, 0);
        //HEADERGEN_BRANCH_INITIALIZERS
    }

    //makes branches on a new TTree
    void make_branches(void) {
        tree->Branch("run", &run, "run/L");
        tree->Branch("event", &event, "event/L");
        tree->Branch("lumi", &lumi, "lumi/L");
        tree->Branch("nleps", &nleps, "nleps/I");
        tree->Branch("njets", &njets, "njets/I");
        tree->Branch("hypothesis", &hypothesis, "hypothesis/I");
        tree->Branch("numcalls", &numcalls, "numcalls/I");
        tree->Branch("systematic", &systematic, "systematic/I");
        tree->Branch("met_pt", &met_pt, "met_pt/F");
        tree->Branch("met_phi", &met_phi, "met_phi/F");
        tree->Branch("lep_pt", lep_pt, "lep_pt[nleps]/F");
        tree->Branch("lep_eta", lep_eta, "lep_eta[nleps]/F");
        tree->Branch("lep_phi", lep_phi, "lep_phi[nleps]/F");
        tree->Branch("lep_mass", lep_mass, "lep_mass[nleps]/F");
        tree->Branch("lep_charge", lep_charge, "lep_charge[nleps]/F");
        tree->Branch("jet_pt", jet_pt, "jet_pt[njets]/F");
        tree->Branch("jet_eta", jet_eta, "jet_eta[njets]/F");
        tree->Branch("jet_phi", jet_phi, "jet_phi[njets]/F");
        tree->Branch("jet_mass", jet_mass, "jet_mass[njets]/F");
        tree->Branch("jet_csv", jet_csv, "jet_csv[njets]/F");
        tree->Branch("jet_cmva", jet_cmva, "jet_cmva[njets]/F");
        tree->Branch("jet_type", jet_type, "jet_type[njets]/I");
        //HEADERGEN_BRANCH_CREATOR
    }

    //connects the branches of an existing TTree to variables
    //used when loading the file
    void set_branch_addresses(void) {        
        tree->SetBranchAddress("run", &run);
        tree->SetBranchAddress("event", &event);
        tree->SetBranchAddress("lumi", &lumi);
        tree->SetBranchAddress("nleps", &nleps);
        tree->SetBranchAddress("njets", &njets);
        tree->SetBranchAddress("hypothesis", &hypothesis);
        tree->SetBranchAddress("numcalls", &numcalls);
        tree->SetBranchAddress("systematic", &systematic);
        tree->SetBranchAddress("met_pt", &met_pt);
        tree->SetBranchAddress("met_phi", &met_phi);
        tree->SetBranchAddress("lep_pt", lep_pt);
        tree->SetBranchAddress("lep_eta", lep_eta);
        tree->SetBranchAddress("lep_phi", lep_phi);
        tree->SetBranchAddress("lep_mass", lep_mass);
        tree->SetBranchAddress("lep_charge", lep_charge);
        tree->SetBranchAddress("jet_pt", jet_pt);
        tree->SetBranchAddress("jet_eta", jet_eta);
        tree->SetBranchAddress("jet_phi", jet_phi);
        tree->SetBranchAddress("jet_mass", jet_mass);
        tree->SetBranchAddress("jet_csv", jet_csv);
        tree->SetBranchAddress("jet_cmva", jet_cmva);
        tree->SetBranchAddress("jet_type", jet_type);
        //HEADERGEN_BRANCH_SETADDRESS
    }
};

#endif

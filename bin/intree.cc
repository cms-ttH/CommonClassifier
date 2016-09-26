//compile with
//c++ `root-config --cflags --libs` -I$CMSSW_BASE/src/ bin/intree.cc -o intree
#include "TTH/CommonClassifier/interface/intree.h"

#include "TTree.h"
#include "TFile.h"

int main(int argc, const char** argv) {
    TFile* of = new TFile("out.root", "RECREATE");
    TTree* tree = new TTree("tree", "tree");


    CommonClassifierInputTree cc(tree);

    cc.make_branches();

    for (int i=0; i<1000; i++) {
        cc.loop_initialize();
        cc.event = i;

        cc.njets = 4;
        cc.jet_type[0] = 0;
        cc.jet_type[1] = 1;
        cc.jet_type[2] = 2;
        cc.jet_type[3] = 3;

        cc.tree->Fill();
    }

    of->Write();
    of->Close();
    return 0;
}

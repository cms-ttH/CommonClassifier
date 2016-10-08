import ROOT, sys, shelve

class Classifiers:
    def __init__(self, **kwargs):
        self.mem_p_sig = kwargs.get("mem_p_sig", 0)
        self.mem_p_bkg = kwargs.get("mem_p_bkg", 0)
        self.bdt = kwargs.get("bdt", 0)

class ClassifierDB:
    def __init__(self, *args, **kwargs):
        fn = kwargs.get("filename")
        if fn.endswith(".root"):
            self.data = {}

            if len(fn)>0:
                self.tfile = ROOT.TFile.Open(fn)
                self.tree = self.tfile.Get("tree")

                for ev in self.tree:
                    run = ev.run
                    evt = ev.event
                    lumi = ev.lumi
                    syst = ev.systematic

                    key = "_".join(map(str, [run, lumi, evt, syst]))

                    self.data[key] = Classifiers(
                        mem_p_sig=ev.mem_p_sig,
                        mem_p_bkg=ev.mem_p_bkg,
                        bdt=getattr(ev, "bdt", 0)
                    )
                self.tfile.Close()
                
            print "ClassifierDB initialized from file={0} with len(k)={1} keys".format(
                fn,
                len(self.data)
            )
            
            print "first few keys are", sorted(self.data.keys())[:5]
            self.shelf = shelve.open(fn + ".shelve")
            self.shelf.update(self.data)
            self.shelf.close()
        elif fn.endswith(".shelve"):
            self.shelf = shelve.open(fn + ".shelve")
            self.data = self.shelf

    def __getitem__(self, key):
        return self.data[key]
    
    def get(self, key, default=Classifiers()):
        if self.data.has_key(key):
            return self.data[key]
        return default
    
    def dump_missing_events(self, infile_name, outfile_name):
        inf = ROOT.TFile.Open(infile_name)
        tt = inf.Get("tree")
        outf = ROOT.TFile(outfile_name, "RECREATE")
        tt2 = tt.CloneTree(0)
        n_missing = 0
        for iEv in range(tt.GetEntries()):
            tt.GetEntry(iEv)
            run = tt.run
            lumi = tt.lumi
            ev = tt.event
            syst = tt.systematic
            k = (run, lumi, ev, syst)
            if not self.data.has_key(k):
                n_missing += 1
                if n_missing % 100 == 0:
                    print n_missing
                tt2.Fill()
       
        print "input tree {0}, db {1}, output {2} ({3:.2f}%)".format(
            tt.GetEntries(),
            len(self.data),
            tt2.GetEntries(),
            100.0 * float(tt2.GetEntries())/float(tt.GetEntries())
        )

        outf.Write()
        outf.Close()
        inf.Close()
        return n_missing

if __name__ == "__main__":
    cls = ClassifierDB(filename=sys.argv[1])

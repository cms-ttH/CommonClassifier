import ROOT, sys

class Classifiers:
    def __init__(self, **kwargs):
        self.mem_p_sig = kwargs.get("mem_p_sig", 0)
        self.mem_p_bkg = kwargs.get("mem_p_bkg", 0)
        self.bdt = kwargs.get("bdt", 0)

class ClassifierDB:
    def __init__(self, *args, **kwargs):
        fn = kwargs.get("filename")
        self.data = {}

        if len(fn)>0:
            self.tfile = ROOT.TFile.Open(fn)
            self.tree = self.tfile.Get("tree")

            for ev in self.tree:
                run = ev.run
                evt = ev.event
                lumi = ev.lumi
                syst = ev.systematic

                self.data[(int(run), int(lumi), int(evt), int(syst))] = Classifiers(
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

    def __getitem__(self, key):
        return self.data[key]
    
    def get(self, key, default=Classifiers()):
        if self.data.has_key(key):
            return self.data[key]
        return default

if __name__ == "__main__":
    cls = ClassifierDB(filename=sys.argv[1])
    for k in cls.data.keys()[:10]:
        print k, cls[k]

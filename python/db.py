import ROOT, sys

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

                self.data[(int(run), int(lumi), int(evt), int(syst))] = ev.mem_p
            self.tfile.Close()
            
        print "ClassifierDB initialized from file={0} with len(k)={1} keys".format(
            fn,
            len(self.data)
        )
        
        print "first few keys are", sorted(self.data.keys())[:5]

    def __getitem__(self, key):
        return self.data[key]
    
    def get(self, key, default=0):
        if self.data.has_key(key):
            return self.data[key]
        return default

if __name__ == "__main__":
    cls = ClassifierDB(filename=sys.argv[1])
    for k in cls.data.keys()[:10]:
        print k, cls[k]

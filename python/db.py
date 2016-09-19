import ROOT, sys

class ClassifierDB:
    def __init__(self, *args, **kwargs):
        self.tfile = ROOT.TFile.Open(kwargs.get("filename"))
        self.tree = self.tfile.Get("tree")
        self.data = {}

        for ev in self.tree:
            evt = ev.event
            run = ev.run
            lumi = ev.lumi

            self.data[(run, lumi, evt)] = ev.mem


    def __getitem__(self, key):
        return self.data[key]

if __name__ == "__main__":
    cls = ClassifierDB(filename=sys.argv[1])
    for k in cls.data.keys()[:10]:
        print k, cls[k]

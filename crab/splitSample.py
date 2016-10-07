import ROOT, os, math
import ConfigParser
from TTH.CommonClassifier.db import ClassifierDB
from TTH.CommonClassifier.remote_hadd import xrootd_walk

def chunks(l, n):
    """Yield successive n-sized chunks from l."""
    for i in range(0, len(l), n):
        yield l[i:i + n]

def roundup(x):
    return int(math.ceil(x / 100.0)) * 100

def genSplitting(infile, perjob, outfile):
    fi = ROOT.TFile.Open(infile)
    tree = fi.Get("tree")

    #all events
    nevents = tree.GetEntries()

    if hasattr(tree, "hypothesis"):
        #events where we askes the MEM to be calculated
        nevents_hypo = tree.GetEntries("hypothesis >= -1")
        ratio_mem = float(nevents)/float(nevents_hypo)
        perjob = roundup(int(perjob*ratio_mem))
    elif hasattr(tree, "hypo"):
        #events where we askes the MEM to be calculated
        nevents_hypo = tree.GetEntries("hypo >= -1")
        ratio_mem = float(nevents)/float(nevents_hypo)
        perjob = roundup(int(perjob*ratio_mem))
    else:
        print "tree has no hypo branch"
        nevents_hypo = nevents
        ratio_mem = 1

    if nevents > 0:
        job_chunks = list(chunks(range(nevents), perjob))
        print "{0} Nall={1} Nmem={2} perjob={3} jobs={4}".format(
            infile,
            nevents,
            nevents_hypo,
            perjob,
            len(job_chunks)
        )
        if len(job_chunks) > 10000:
            raise Exception("too many jobs, reduce splitting!")

        of = open(outfile, "w")
        for chunk in job_chunks:
            of.write("{0}___{1}___{2}\n".format(infile, chunk[0], chunk[-1]))
        of.close()
        fi.Close()
    return nevents

def create_splitting(samples, target_dir, perjob=200):
    samples_events = []
    for samp in samples:
        samples_events += [(
            samp.name,
            samp.input_file,
            genSplitting(samp.input_file, perjob, target_dir + "/{0}.txt".format(samp.name))
        )]
    
    sample_file = open(target_dir + "/samples.dat", "w")
    for name, path, nevents in samples_events:
        sample_file.write("[{0}]\n".format(name))
        sample_file.write("{0} = {1}\n".format(path, nevents))
    sample_file.close()

class Sample:
    def __init__(self, name, input_file, output_path, classifier_db_path, additional_classifier_db_path):
        self.name = name
        self.input_file = input_file
        self.output_path = output_path
        self.classifier_db_path = classifier_db_path
        self.additional_classifier_db_path = additional_classifier_db_path

    def make_missing(self):
        db = ClassifierDB(filename=self.classifier_db_path)
        missing_file = self.classifier_db_path.replace(".root", "_MISSING.root") 
        n_missing = db.dump_missing_events(
            self.input_file,
            missing_file,
        )
        return (missing_file, n_missing)

    def get_output_files(self):
        opath = self.output_path + self.name
        s = opath.replace("root://", "")
        server = s[0:s.index("/")]
        path = s[s.index("/"):]
        print server, path

        files = xrootd_walk(server, path)
        good_files = filter(lambda x: "failed" not in x and x.endswith(".root"), files)
        good_files = ["root://" + server + "//" + fi for fi in good_files]
        return good_files
    
    def merge_classifiers(self):
        print "hadd -f2 {0}.root {1} {2}".format(
            self.name,
            self.classifier_db_path,
            self.additional_classifier_db_path
        )
        #merger = ROOT.TFileMerger(False)
        #merger.OutputFile(self.name + ".root")
        #for res in [self.classifier_db_path, self.additional_classifier_db_path]:
        #    merger.AddFile(res, False)
        #merger.Merge()

def make_missing(samples):
    of = open("missing.dat", "w")
    for samp in samples:
        of.write("[{0}]\n".format(samp.name))
        fn, n = samp.make_missing()
        of.write("{0} = {1}\n".format(fn, n))
    of.close()

def parse_config(cfg_path):
    config = ConfigParser.SafeConfigParser()
    config.optionxform = str # Turn on case-sensitivity
    config.read(cfg_path)
    samples = []

    for workflow in config.get("general", "workflows_list").split():
        input_location = config.get(workflow, "input_location")
        output_location = config.get(workflow, "output_location")
        classifier_db_location = config.get(workflow, "classifier_db_location")
        additional_classifier_db_location = config.get(workflow, "additional_classifier_db_location")
        for sample_name in config.get(workflow,"samples_list").split():
            samp = Sample(
                sample_name,
                "root://" + input_location + sample_name + ".root",
                "root://" + output_location,
                classifier_db_location + sample_name + ".root",
                additional_classifier_db_location + sample_name + ".root",
            )
            print samp.name, samp.input_file, samp.output_path, samp.classifier_db_path

            samples += [samp]
    return samples

if __name__ == "__main__":
    #samples = parse_config("samples_desy.cfg")
    #create_splitting(samples, "samples/desy", 100)
    
    samples = parse_config("samples_kit.cfg")
    #for samp in samples:
    #    if os.path.exists(samp.additional_classifier_db_path):
    #        samp.merge_classifiers()
    make_missing(samples) 
    # mergefile = open("merge.dat", "w")
    # for samp in samples:
    #     files = samp.get_output_files()
    #     mergefile.write("[{0}]\n".format(samp.name))
    #     for fi in files:
    #         mergefile.write("{0} = 1\n".format(fi))
    #     print "sample {0} had {1} merge files".format(samp.name, len(files))
    # mergefile.close()

    #create_splitting(samples, "samples/kit_dl", 200)
    #make_missing(samples) 

    #pref = "root://eoscms.cern.ch/"
    #samples = [(os.path.basename(s).split(".")[0], s.strip()) for s in open("samples_eth").readlines()]
    #create_splitting(pref, samples, "samples/eth", 200)

    #pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/DESY/"
    #samples = [(s.split(".")[0], s) for s in os.listdir("/afs/cern.ch/work/g/gvonsem/public/MEMttH/28Sep2016/")]
    #create_splitting(pref, samples, "samples/desy", 100)

    # KIT jobs have all >=4j >=2t events, which is 4x >=4j >=3.
    # For jobs that last 5h = 300min, 1 minute/MEM, it would be 300 MEM events, which is ~1200 any events
    # so specifying 1000events and 5h should be on the safe side
    #pref = "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/MEMInputTrees_ICHEP_V3newttsl/" 
    #samples = [(s.split(".")[0].strip(), s.strip()) for s in open("/mnt/t3nfs01/data01/shome/jpata/karim_samples/sample_list.txt").readlines()]
    #create_splitting(pref, samples, "samples/kit", 1000)
   


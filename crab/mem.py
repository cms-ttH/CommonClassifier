print "running mem.py"
import PSet
import ROOT
import numpy as np
from cc_looper import main
import os

infile_pattern = PSet.process.source.fileNames[0]
outfile_name = PSet.process.output.fileName.value()
infile_name, firstEvent, lastEvent = infile_pattern.split("___")

firstEvent = int(firstEvent)
lastEvent = int(lastEvent)

#Check if we have local data
if infile_name.startswith("/store"):
    pfn=os.popen("edmFileUtil -d %s"%(infile_name)).read()
    pfn=re.sub("\n","",pfn)
    inf_local = ROOT.TFile.Open(pfn)
    if not inf_local or inf_local.IsZombie():
        infile_name = "root://cms-xrd-global.cern.ch//" + infile_name
    else:
        infile_name = pfn
        inf_local.Close()

#copy subsection of the tree
print "opening {0}".format(infile_name)
inf_remote = ROOT.TFile.Open(infile_name)
tt = inf_remote.Get("tree")
inf_local = ROOT.TFile("infile.root", "RECREATE")
tt2 = tt.CloneTree(0)
nEvents = 0
for iEv in range(firstEvent, lastEvent+1):
    tt.GetEntry()
    tt2.Fill()
    nEvents += 1

inf_local.Write()
inf_local.Close()
inf_remote.Close()

#now do the processing
conf = {
    "btag": "btagCSV_",
}

main("infile.root", 0, nEvents, outfile_name, conf)
print "loop done"

infile_lfn = infile_name[infile_name.index("/store"):]

#create framework job report
fwkreport="""<FrameworkJobReport>
<ReadBranches>
</ReadBranches>
<PerformanceReport>
  <PerformanceSummary Metric="StorageStatistics">
    <Metric Name="Parameter-untracked-bool-enabled" Value="true"/>
    <Metric Name="Parameter-untracked-bool-stats" Value="true"/>
    <Metric Name="Parameter-untracked-string-cacheHint" Value="application-only"/>
    <Metric Name="Parameter-untracked-string-readHint" Value="auto-detect"/>
    <Metric Name="ROOT-tfile-read-totalMegabytes" Value="0"/>
    <Metric Name="ROOT-tfile-write-totalMegabytes" Value="0"/>
  </PerformanceSummary>
</PerformanceReport>

<GeneratorInfo>
</GeneratorInfo>
"""
inf = """
<InputFile>
<LFN>%s</LFN>
<PFN></PFN>
<Catalog></Catalog>
<InputType>primaryFiles</InputType>
<ModuleLabel>source</ModuleLabel>
<GUID></GUID>
<InputSourceClass>PoolSource</InputSourceClass>
<EventsRead>1</EventsRead>
</InputFile>
""" % (infile_lfn)

fwkreport += inf

output_entries = 0

fwkreport += """
<File>
<LFN></LFN>
<PFN>%s</PFN>
<Catalog></Catalog>
<ModuleLabel>HEPPY</ModuleLabel>
""" % (outfile_name)

fwkreport += """
<GUID></GUID>
<OutputModuleClass>PoolOutputModule</OutputModuleClass>
<TotalEvents>%d</TotalEvents>
<BranchHash>dc90308e392b2fa1e0eff46acbfa24bc</BranchHash>
</File>
</FrameworkJobReport>""" % (output_entries)

of = open("FrameworkJobReport.xml", "w")
of.write(fwkreport)
of.close()

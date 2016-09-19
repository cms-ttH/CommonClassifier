print "running mem.py"
import PSet
import numpy as np
from cc_looper import main

infile_pattern = PSet.process.source.fileNames[0]
outfile_name = PSet.process.output.fileName.value()
infile_name, firstEvent, lastEvent = infile_pattern.split("___")
firstEvent = int(firstEvent)
lastEvent = int(lastEvent)

main(infile_name, firstEvent, lastEvent, outfile_name)
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

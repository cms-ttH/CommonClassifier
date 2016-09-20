The scripts under this folder allow the CommonClassifier to be run over common ntuples.

The main worker script is `cc_looper.py`, the documentation of which you can find under

~~~
python cc_looper.py --help
#example call
python cc_looper.py --infile /mnt/t3nfs01/data01/shome/jpata/tth/sw/CMSSW/src/TTH/MEAnalysis/out.root --outfile out.root --firstEvent 0 --lastEvent 4

~~~

When run with the appropriate inputs, it will produce the CommonClassifier tree.

Running this script via CRAB3 is supported using `crab_config.py` (simple example) or `multicrab.py` (many samples).

The sample splitting is generated using `splitSample.py`. The input files need to be stored in an xrootd-accessible T2 site.

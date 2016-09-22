#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh
source env.sh
cd ${CMSSW_BASE}
eval `scram runtime -sh`
cd $GC_SCRATCH
python ${CMSSW_BASE}/src/TTH/CommonClassifier/crab/cc_looper.py --infile $FILE_NAMES --outfile out.root --firstEvent $SKIP_EVENTS --maxEvents $MAX_EVENTS

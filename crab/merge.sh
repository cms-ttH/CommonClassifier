#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh
source env.sh
cd ${CMSSW_BASE}
eval `scram runtime -sh`
cd $GC_SCRATCH
hadd out.root $FILE_NAMES

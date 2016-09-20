import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("FAKE")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring([
        "root://eoscms.cern.ch//store/group/phys_higgs/hbb/mem/Sep14_leptonic_nome_v1__ttHTobb_M125_13TeV_powheg_pythia8.root___0___4",
    ]),
)
process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('out.root')
)


process.out = cms.EndPath(process.output)



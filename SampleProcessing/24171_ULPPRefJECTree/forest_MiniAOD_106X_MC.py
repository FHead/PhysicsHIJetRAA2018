### HiForest Configuration
# Input: miniAOD
# Type: mc

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run2_2017_ppRef_cff import Run2_2017_ppRef
from Configuration.ProcessModifiers.run2_miniAOD_UL_cff import run2_miniAOD_UL
process = cms.Process('HiForest', Run2_2017_ppRef, run2_miniAOD_UL)

###############################################################################

# HiForest info
process.load("HeavyIonsAnalysis.EventAnalysis.HiForestInfo_cfi")
process.HiForestInfo.info = cms.vstring("HiForest, miniAOD, 106X, MC")

# import subprocess, os
# version = subprocess.check_output(
#     ['git', '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
# if version == '':
#     version = 'no git info'
# process.HiForestInfo.HiForestVersion = cms.string(version)

###############################################################################

# input files
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
        # 'file:/afs/cern.ch/work/m/mnguyen/public/integration/CMSSW_11_2_4_patch4/src/step3_inMINIAODSIM.root'
        '/store/user/anstahll/UltraLegacy/MC/MINIAOD/20211122/QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122/RunIISummer20UL17pp5TeV/QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122/211122_035312/0000/HIN-RunIISummer20UL17pp5TeVMiniAOD-00003_1.root'
    ),
)

# number of events to process, set to -1 to process all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )

###############################################################################

# load Global Tag, geometry, etc.
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_mc2017_realistic_forppRef5TeV_v3', '')
process.HiForestInfo.GlobalTagLabel = process.GlobalTag.globaltag
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("BTagTrackProbability3DRcd"),
             tag = cms.string("JPcalib_MC103X_2018PbPb_v4"),
             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS")
         )
])


###############################################################################

# root output
process.TFileService = cms.Service("TFileService",
    fileName = cms.string("HiForestMiniAOD.root"))

# # edm output for debugging purposes
# process.output = cms.OutputModule(
#     "PoolOutputModule",
#     fileName = cms.untracked.string('HiForestEDM.root'),
#     outputCommands = cms.untracked.vstring(
#         'keep *',
#         )
#     )

# process.output_path = cms.EndPath(process.output)

###############################################################################

#############################
# Gen Analyzer
#############################
process.load('HeavyIonsAnalysis.EventAnalysis.HiGenAnalyzer_cfi')
# making cuts looser so that we can actually check dNdEta
process.HiGenParticleAna.ptMin = cms.untracked.double(0.0) # default is 5
process.HiGenParticleAna.etaMax = cms.untracked.double(8.) # default is 2.5

# event analysis
# process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.particleFlowAnalyser_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_mc_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
# process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
# process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

process.particleFlowAnalyser.ptMin = cms.double(0.)

# from HeavyIonsAnalysis.EventAnalysis.hltobject_cfi import trigger_list_mc
# process.hltobject.triggerNames = trigger_list_mc

# process.load('HeavyIonsAnalysis.EventAnalysis.particleFlowAnalyser_cfi')
################################
# electrons, photons, muons
# process.load('HeavyIonsAnalysis.EGMAnalysis.ggHiNtuplizer_cfi')
# process.ggHiNtuplizer.doGenParticles = cms.bool(True)
# process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
################################
# jet reco sequence
# process.load('HeavyIonsAnalysis.JetAnalysis.akCs4PFJetSequence_pponPbPb_mc_cff')
################################
# tracks
# process.load("HeavyIonsAnalysis.TrackAnalysis.TrackAnalyzers_cff")
#muons
# process.load("HeavyIonsAnalysis.MuonAnalysis.unpackedMuons_cfi")
# process.load("HeavyIonsAnalysis.MuonAnalysis.hltMuTree_cfi")

###############################################################################



###############################################################################
# main forest sequence
process.forest = cms.Path(
    process.HiForestInfo +
    # process.hltanalysis +
    # process.hltobject +
    # process.trackSequencePbPb +
    process.particleFlowAnalyser +
    process.hiEvtAnalyzer +
    process.HiGenParticleAna
    # process.unpackedMuons +
    # process.ggHiNtuplizer +
    # process.akCs4PFJetAnalyzer +
    # process.hltMuTree
    )

#########################
# Event Selection -> add the needed filters here
#########################

# process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
# process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
# process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
# process.pAna = cms.EndPath(process.skimanalysis)

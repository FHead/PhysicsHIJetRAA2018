### HiForest Configuration
# Input: miniAOD
# Type: data

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run2_2018_pp_on_AA_cff import Run2_2018_pp_on_AA
from Configuration.ProcessModifiers.run2_miniAOD_pp_on_AA_103X_cff import run2_miniAOD_pp_on_AA_103X
process = cms.Process('HiForest', Run2_2018_pp_on_AA,run2_miniAOD_pp_on_AA_103X)

###############################################################################

# HiForest info
process.load("HeavyIonsAnalysis.EventAnalysis.HiForestInfo_cfi")
process.HiForestInfo.info = cms.vstring("HiForest, miniAOD, 112X, data")

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
        "/store/hidata/HIRun2018A/HISingleMuon/MINIAOD/PbPb18_MiniAODv1-v1/00000/00345f79-641f-4002-baf1-19ae8e83c48b.root"
        # '__INPUT__'
    ),
)
#input file produced from:
#"file:/afs/cern.ch/work/r/rbi/public/forest/HIHardProbes_HIRun2018A-PromptReco-v2_AOD.root"

# import FWCore.PythonUtilities.LumiList as LumiList
# process.source.lumisToProcess = LumiList.LumiList(filename = 'JSON.txt').getVLuminosityBlockRange()

# number of events to process, set to -1 to process all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
    )

###############################################################################

# load Global Tag, geometry, etc.
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data_promptlike_hi', '')
process.HiForestInfo.GlobalTagLabel = process.GlobalTag.globaltag

centralityTag = "CentralityTable_HFtowers200_DataPbPb_periHYDJETshape_run2v1031x02_offline"
process.HiForestInfo.info.append(centralityTag)

print('\n')
print('\033[31m~*~ CENTRALITY TABLE FOR 2018 PBPB DATA ~*~\033[0m')
print('\033[36m~*~ TAG: ' + centralityTag + ' ~*~\033[0m')
print('\n')
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(
        record = cms.string("HeavyIonRcd"),
        tag = cms.string(centralityTag),
        label = cms.untracked.string("HFtowers"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
        ),
    ])

process.GlobalTag.toGet.extend([
    cms.PSet(
        record = cms.string("BTagTrackProbability3DRcd"),
        tag = cms.string("JPcalib_Data103X_2018PbPb_v1"),
        connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
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

# event analysis
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

from HeavyIonsAnalysis.EventAnalysis.hltobject_cfi import trigger_list_data
process.hltobject.triggerNames = trigger_list_data

process.load('HeavyIonsAnalysis.EventAnalysis.particleFlowAnalyser_cfi')
################################
# electrons, photons, muons
process.load('HeavyIonsAnalysis.MuonAnalysis.unpackedMuons_cfi')
process.load('HeavyIonsAnalysis.EGMAnalysis.ggHiNtuplizer_cfi')
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
################################
# jet reco sequence
process.load('HeavyIonsAnalysis.JetAnalysis.akCs4PFJetSequence_pponPbPb_data_cff')
################################
# tracks
process.load("HeavyIonsAnalysis.TrackAnalysis.TrackAnalyzers_cff")
###############################################################################



###############################################################################
# main forest sequence
process.forest = cms.Path(
    process.HiForestInfo +
    process.hltanalysis +
    process.hltobject +
    # process.trackSequencePbPb +
    # process.particleFlowAnalyser +
    process.hiEvtAnalyzer +
    # process.unpackedMuons +
    # process.ggHiNtuplizer +
    process.akCs4PFJetAnalyzer
    )

#customisation

addRXJets = True

if addRXJets :
    process.load("HeavyIonsAnalysis.JetAnalysis.extraJets_cff")
    from HeavyIonsAnalysis.JetAnalysis.clusterJetsFromMiniAOD_cff import setupHeavyIonJets
    setupHeavyIonJets('akCs1PF',  process.extraJetsData, process, isMC = 0, radius = 0.15, JECTag = 'AK4PF')
    setupHeavyIonJets('akCs2PF',  process.extraJetsData, process, isMC = 0, radius = 0.20, JECTag = 'AK4PF')
    setupHeavyIonJets('akCs3PF',  process.extraJetsData, process, isMC = 0, radius = 0.30, JECTag = 'AK3PF')
    setupHeavyIonJets('akCs5PF',  process.extraJetsData, process, isMC = 0, radius = 0.50, JECTag = 'AK4PF')
    setupHeavyIonJets('akCs6PF',  process.extraJetsData, process, isMC = 0, radius = 0.60, JECTag = 'AK4PF')
    setupHeavyIonJets('akCs7PF',  process.extraJetsData, process, isMC = 0, radius = 0.80, JECTag = 'AK4PF')
    setupHeavyIonJets('akCs8PF',  process.extraJetsData, process, isMC = 0, radius = 1.00, JECTag = 'AK4PF')
    setupHeavyIonJets('akCs9PF',  process.extraJetsData, process, isMC = 0, radius = 1.20, JECTag = 'AK4PF')
    process.akCs1PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs2PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs3PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs5PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs6PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs7PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs8PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs9PFpatJetCorrFactors.levels = ['L2Relative', 'L2L3Residual']
    process.akCs1PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs1PFpatJets")
    process.akCs2PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs2PFpatJets")
    process.akCs3PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs3PFpatJets")
    process.akCs5PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs5PFpatJets")
    process.akCs6PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs6PFpatJets")
    process.akCs7PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs7PFpatJets")
    process.akCs8PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs8PFpatJets")
    process.akCs9PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs9PFpatJets")

    process.forest += process.extraJetsData * process.akCs1PFJetAnalyzer
    process.forest += process.extraJetsData * process.akCs2PFJetAnalyzer
    process.forest += process.extraJetsData * process.akCs3PFJetAnalyzer
    process.forest += process.extraJetsData * process.akCs5PFJetAnalyzer
    process.forest += process.extraJetsData * process.akCs6PFJetAnalyzer
    process.forest += process.extraJetsData * process.akCs7PFJetAnalyzer
    process.forest += process.extraJetsData * process.akCs8PFJetAnalyzer
    process.forest += process.extraJetsData * process.akCs9PFJetAnalyzer





addCandidateTagging = True

if addCandidateTagging:
    process.load("HeavyIonsAnalysis.JetAnalysis.candidateBtaggingMiniAOD_cff")

    from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
    updateJetCollection(
        process,
        jetSource = cms.InputTag('slimmedJets'),
        jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
        btagDiscriminators = ['pfCombinedSecondaryVertexV2BJetTags', 'pfDeepCSVDiscriminatorsJetTags:BvsAll', 'pfDeepCSVDiscriminatorsJetTags:CvsB', 'pfDeepCSVDiscriminatorsJetTags:CvsL'], ## to add discriminators,
        btagPrefix = 'TEST',
    )

    process.updatedPatJets.addJetCorrFactors = False
    process.updatedPatJets.discriminatorSources = cms.VInputTag(
        cms.InputTag('pfDeepCSVJetTags:probb'),
        cms.InputTag('pfDeepCSVJetTags:probc'),
        cms.InputTag('pfDeepCSVJetTags:probudsg'),
        cms.InputTag('pfDeepCSVJetTags:probbb'),
    )

    process.akCs4PFJetAnalyzer.jetTag = "updatedPatJets"

    process.forest.insert(1,process.candidateBtagging*process.updatedPatJets)

    process.akCs4PFJetAnalyzer.addDeepCSV = True

#########################
# Event Selection -> add the needed filters here
#########################

process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
process.load('HeavyIonsAnalysis.EventAnalysis.hffilter_cfi')
process.pphfCoincFilter2Th4 = cms.Path(process.phfCoincFilter2Th4)

process.load('CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi')
process.fHBHENoiseFilterResult = cms.EDFilter(
      'BooleanFlagFilter',
      inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResult'),
      reverseDecision = cms.bool(False)
      )
process.fHBHENoiseFilterResultRun1 = process.fHBHENoiseFilterResult.clone(
      inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResultRun1'))
process.fHBHENoiseFilterResultRun2Loose = process.fHBHENoiseFilterResult.clone(
      inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResultRun2Loose'))
process.fHBHENoiseFilterResultRun2Tight = process.fHBHENoiseFilterResult.clone(
      inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResultRun2Tight'))
process.fHBHEIsoNoiseFilterResult = process.fHBHENoiseFilterResult.clone(
      inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHEIsoNoiseFilterResult'))
process.HBHENoiseFilterResult = cms.Path(process.HBHENoiseFilterResultProducer * process.fHBHENoiseFilterResult)
process.HBHENoiseFilterResultRun1 = cms.Path(process.HBHENoiseFilterResultProducer * process.fHBHENoiseFilterResultRun1)
process.HBHENoiseFilterResultRun2Loose = cms.Path(process.HBHENoiseFilterResultProducer * process.fHBHENoiseFilterResultRun2Loose)
process.HBHENoiseFilterResultRun2Tight = cms.Path(process.HBHENoiseFilterResultProducer * process.fHBHENoiseFilterResultRun2Tight)
process.HBHEIsoNoiseFilterResult = cms.Path(process.HBHENoiseFilterResultProducer * process.fHBHEIsoNoiseFilterResult)

process.pAna = cms.EndPath(process.skimanalysis)

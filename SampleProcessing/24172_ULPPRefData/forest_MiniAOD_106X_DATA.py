### HiForest Configuration
# Input: miniAOD
# Type: data

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run2_2017_ppRef_cff import Run2_2017_ppRef
from Configuration.ProcessModifiers.run2_miniAOD_UL_cff import run2_miniAOD_UL
process = cms.Process('HiForest', Run2_2017_ppRef, run2_miniAOD_UL)

###############################################################################

# HiForest info
process.load("HeavyIonsAnalysis.EventAnalysis.HiForestInfo_cfi")
process.HiForestInfo.info = cms.vstring("HiForest, miniAOD, 106X, data")

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
        '/store/data/Run2017G/HighEGJet/MINIAOD/UL2017_MiniAODv2-v1/240000/C57221ED-14F4-514E-A4F0-57B94569CB3B.root'
    ),
)

# number of events to process, set to -1 to process all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
    )

###############################################################################

# load Global Tag, geometry, etc.
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v33', '')
process.HiForestInfo.GlobalTagLabel = process.GlobalTag.globaltag

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
# process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

process.load('HeavyIonsAnalysis.EventAnalysis.particleFlowAnalyser_cfi')
process.particleFlowAnalyser.ptMin = cms.double(0.)

################################
# electrons, photons, muons
#process.load('HeavyIonsAnalysis.MuonAnalysis.unpackedMuons_cfi')
#process.load('HeavyIonsAnalysis.EGMAnalysis.ggHiNtuplizer_cfi')
#process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
################################
# jet reco sequence
#process.load('HeavyIonsAnalysis.JetAnalysis.akCs4PFJetSequence_pponPbPb_data_cff')
################################
# tracks
#process.load("HeavyIonsAnalysis.TrackAnalysis.TrackAnalyzers_cff")
###############################################################################

process.load('RecoJets.JetProducers.ak4PFJets_cfi')
process.ak4PFJets.src = "packedPFCandidates"

process.ak4PFJetCorr = cms.EDProducer("JetCorrFactorsProducer",
      emf = cms.bool(False),
      extraJPTOffset = cms.string('L1FastJet'),
      flavorType = cms.string('J'),
      levels = cms.vstring('L2Relative', 'L3Absolute'),
      payload = cms.string('AK4PF'),
      primaryVertices = cms.InputTag("offlinePrimaryVertices"),
      rho = cms.InputTag("dummy"),
      src = cms.InputTag("ak4PFJets"),
      useNPV = cms.bool(False),
      useRho = cms.bool(False)
      )

process.ak4PFPatJets = cms.EDProducer("PATJetProducer",
      JetFlavourInfoSource = cms.InputTag("dummy"),
      JetPartonMapSource = cms.InputTag("dummy"),
      addAssociatedTracks = cms.bool(False),
      addBTagInfo = cms.bool(False),
      addDiscriminators = cms.bool(False),
      addEfficiencies = cms.bool(False),
      addGenJetMatch = cms.bool(False),
      addGenPartonMatch = cms.bool(False),
      addJetCharge = cms.bool(False),
      addJetCorrFactors = cms.bool(True),
      addJetFlavourInfo = cms.bool(False),
      addJetID = cms.bool(False),
      addPartonJetMatch = cms.bool(False),
      addResolutions = cms.bool(False),
      addTagInfos = cms.bool(False),
      discriminatorSources = cms.VInputTag(),
      efficiencies = cms.PSet(),
      embedGenJetMatch = cms.bool(False),
      embedGenPartonMatch = cms.bool(False),
      embedPFCandidates = cms.bool(False),
      genJetMatch = cms.InputTag("akCs9PFpatJetGenJetMatch"),
      genPartonMatch = cms.InputTag("akCs9PFpatJetPartonMatch"),
      getJetMCFlavour = cms.bool(False),
      jetChargeSource = cms.InputTag("patJetCharge"),
      jetCorrFactorsSource = cms.VInputTag("ak4PFJetCorr"),
      jetIDMap = cms.InputTag("ak4JetID"),
      jetSource = cms.InputTag("ak4PFJets"),
      partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
      resolutions = cms.PSet(),
      tagInfoSources = cms.VInputTag(),
      trackAssociationSource = cms.InputTag("ak4JetTracksAssociatorAtVertex"),
      useLegacyJetMCFlavour = cms.bool(True),
      userData = cms.PSet(
         userCands = cms.PSet(src = cms.VInputTag("")),
         userClasses = cms.PSet(src = cms.VInputTag("")),
         userFloats = cms.PSet(src = cms.VInputTag("")),
         userFunctionLabels = cms.vstring(),
         userFunctions = cms.vstring(),
         userInts = cms.PSet(src = cms.VInputTag(""))
         )
      )

process.load('HeavyIonsAnalysis.JetAnalysis.inclusiveJetAnalyzer_cff')
process.ak4PFJetAnalyzer = process.inclusiveJetAnalyzer.clone(
   jetTag = cms.InputTag("ak4PFPatJets"),
   rParam = cms.double(0.4),
   fillGenJets = cms.untracked.bool(False),
   isMC = cms.untracked.bool(False),
   doLifeTimeTagging = cms.untracked.bool(False),
   # doWTARecluster = cms.untracked.bool(True),
   bTagJetName = cms.untracked.string('ak4PF'),
   jetName = cms.untracked.string('ak4PF')
   )


process.ak1PFJets = process.ak4PFJets.clone(rParam = 0.15)
process.ak2PFJets = process.ak4PFJets.clone(rParam = 0.20)
process.ak3PFJets = process.ak4PFJets.clone(rParam = 0.30)
process.ak5PFJets = process.ak4PFJets.clone(rParam = 0.50)
process.ak6PFJets = process.ak4PFJets.clone(rParam = 0.60)
process.ak7PFJets = process.ak4PFJets.clone(rParam = 0.80)
process.ak8PFJets = process.ak4PFJets.clone(rParam = 1.00)
process.ak9PFJets = process.ak4PFJets.clone(rParam = 1.20)

process.ak1PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak1PFJets')
process.ak2PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak2PFJets')
process.ak3PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak3PFJets')
process.ak5PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak5PFJets')
process.ak6PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak6PFJets')
process.ak7PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak7PFJets')
process.ak8PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak8PFJets')
process.ak9PFJetCorr = process.ak4PFJetCorr.clone(src = 'ak9PFJets')

process.ak1PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak1PFJetCorr"), jetSource = "ak1PFJets")
process.ak2PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak2PFJetCorr"), jetSource = "ak2PFJets")
process.ak3PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak3PFJetCorr"), jetSource = "ak3PFJets")
process.ak5PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak5PFJetCorr"), jetSource = "ak5PFJets")
process.ak6PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak6PFJetCorr"), jetSource = "ak6PFJets")
process.ak7PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak7PFJetCorr"), jetSource = "ak7PFJets")
process.ak8PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak8PFJetCorr"), jetSource = "ak8PFJets")
process.ak9PFPatJets = process.ak4PFPatJets.clone(jetCorrFactorsSource = cms.VInputTag("ak9PFJetCorr"), jetSource = "ak9PFJets")

process.ak1PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 0.15, jetName = "ak1PF", jetTag = "ak1PFPatJets")
process.ak2PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 0.20, jetName = "ak2PF", jetTag = "ak2PFPatJets")
process.ak3PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 0.30, jetName = "ak3PF", jetTag = "ak3PFPatJets")
process.ak5PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 0.50, jetName = "ak5PF", jetTag = "ak5PFPatJets")
process.ak6PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 0.60, jetName = "ak6PF", jetTag = "ak6PFPatJets")
process.ak7PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 0.80, jetName = "ak7PF", jetTag = "ak7PFPatJets")
process.ak8PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 1.00, jetName = "ak8PF", jetTag = "ak8PFPatJets")
process.ak9PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(rParam = 1.20, jetName = "ak9PF", jetTag = "ak9PFPatJets")

###############################################################################
# main forest sequence
process.forest = cms.Path(process.HiForestInfo
    + process.hltanalysis
    + process.hltobject
    # + process.trackSequencePbPb
    # + process.particleFlowAnalyser
    + process.hiEvtAnalyzer
    + (process.ak1PFJets * process.ak1PFJetCorr * process.ak1PFPatJets * process.ak1PFJetAnalyzer)
    + (process.ak2PFJets * process.ak2PFJetCorr * process.ak2PFPatJets * process.ak2PFJetAnalyzer)
    + (process.ak3PFJets * process.ak3PFJetCorr * process.ak3PFPatJets * process.ak3PFJetAnalyzer)
    + (process.ak4PFJets * process.ak4PFJetCorr * process.ak4PFPatJets * process.ak4PFJetAnalyzer)
    + (process.ak5PFJets * process.ak5PFJetCorr * process.ak5PFPatJets * process.ak5PFJetAnalyzer)
    + (process.ak6PFJets * process.ak6PFJetCorr * process.ak6PFPatJets * process.ak6PFJetAnalyzer)
    + (process.ak7PFJets * process.ak7PFJetCorr * process.ak7PFPatJets * process.ak7PFJetAnalyzer)
    + (process.ak8PFJets * process.ak8PFJetCorr * process.ak8PFPatJets * process.ak8PFJetAnalyzer)
    + (process.ak9PFJets * process.ak9PFJetCorr * process.ak9PFPatJets * process.ak9PFJetAnalyzer)
    # + process.unpackedMuons
    # + process.ggHiNtuplizer
    )

#customisation

#########################
# Event Selection -> add the needed filters here
#########################

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


process.load("RecoMET.METFilters.EcalDeadCellTriggerPrimitiveFilter_cfi")
process.pEcalDeadTP = cms.Path(process.EcalDeadCellTriggerPrimitiveFilter)

# process.NoScraping = cms.EDFilter("FilterOutScraping",
#       applyfilter = cms.untracked.bool(True),
#       debugOn = cms.untracked.bool(False),
#       numtrack = cms.untracked.uint32(10),
#       thresh = cms.untracked.double(0.25)
#       )
# process.pBeamScrapingFilter=cms.Path(process.NoScraping)

process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
process.pAna = cms.EndPath(process.skimanalysis)


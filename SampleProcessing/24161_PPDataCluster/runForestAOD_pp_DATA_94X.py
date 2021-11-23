### HiForest Configuration
# Collisions: pp
# Type: Data
# Input: AOD

import FWCore.ParameterSet.Config as cms
process = cms.Process('HiForest')
process.options = cms.untracked.PSet()

#####################################################################################
# HiForest labelling info
#####################################################################################

process.load("HeavyIonsAnalysis.JetAnalysis.HiForest_cff")
process.HiForest.inputLines = cms.vstring("HiForest 94X",)
import subprocess, os
version = subprocess.check_output(['git',
    '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
if version == '':
    version = 'no git info'
process.HiForest.HiForestVersion = cms.string(version)

#####################################################################################
# Input source
#####################################################################################

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/afs/cern.ch/work/r/rbi/public/forest/HighEGJet_Run2017G_17Nov2017-v2_AOD_large.root'
    )
)

# Number of events we want to process, -1 = all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(8))

#####################################################################################
# Load Global Tag, Geometry, etc.
#####################################################################################

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '94X_dataRun2_ReReco_EOY17_v6', '')
process.HiForest.GlobalTagLabel = process.GlobalTag.globaltag

process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("BTagTrackProbability3DRcd"),
             tag = cms.string("JPcalib_Data94X_2017pp_v2"),
             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS")

         )
      ])

#####################################################################################
# Define tree output
#####################################################################################

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("HiForestAOD.root"))

#####################################################################################
# Additional Reconstruction and Analysis: Main Body
#####################################################################################

#############################
# Jets
#############################
process.load('HeavyIonsAnalysis.JetAnalysis.fullJetSequence_pp_data_cff')

from HeavyIonsAnalysis.Configuration.CommonFunctions_cff import overrideJEC_DATA_pp5020_2017
process = overrideJEC_DATA_pp5020_2017(process)

#####################################################################################

############################
# Event Analysis
############################
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_data_cfi')
process.hiEvtAnalyzer.Vertex = cms.InputTag("offlinePrimaryVertices")
process.hiEvtAnalyzer.doCentrality = cms.bool(False)
process.hiEvtAnalyzer.doEvtPlane = cms.bool(False)

process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cff')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

process.load("HeavyIonsAnalysis.JetAnalysis.pfcandAnalyzer_cfi")
process.pfcandAnalyzer.skipCharged = False
process.pfcandAnalyzer.pfPtMin = 0
process.pfcandAnalyzer.pfCandidateLabel = cms.InputTag("particleFlow")
process.pfcandAnalyzer.doVS = cms.untracked.bool(False)
process.pfcandAnalyzer.doUEraw_ = cms.untracked.bool(False)
process.pfcandAnalyzer.genLabel = cms.InputTag("genParticles")
process.load("HeavyIonsAnalysis.JetAnalysis.hcalNoise_cff")

#####################################################################################

#########################
# Track Analyzer
#########################
process.load('HeavyIonsAnalysis.JetAnalysis.ExtraTrackReco_cff')
process.load('HeavyIonsAnalysis.JetAnalysis.TrkAnalyzers_cff')

####################################################################################

#####################
# Photons
#####################
process.load('HeavyIonsAnalysis.PhotonAnalysis.ggHiNtuplizer_cfi')
process.ggHiNtuplizer.doGenParticles = False
process.ggHiNtuplizerGED.doGenParticles = False

####################################################################################

#####################
# Electron ID
#####################

from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
# turn on VID producer, indicate data format to be processed
# DataFormat.AOD or DataFormat.MiniAOD
dataFormat = DataFormat.AOD
switchOnVIDElectronIdProducer(process, dataFormat)

# define which IDs we want to produce. Check here https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedElectronIdentificationRun2#Recipe_for_regular_users_for_7_4
my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff']

# add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

#####################################################################################

#####################
# Other jet collections
#####################

process.CustomAK1PFJets = process.ak4PFJets.clone(rParam = 0.15)
process.CustomAK2PFJets = process.ak4PFJets.clone(rParam = 0.20)
process.CustomAK5PFJets = process.ak4PFJets.clone(rParam = 0.50)
process.CustomAK6PFJets = process.ak4PFJets.clone(rParam = 0.60)
process.CustomAK7PFJets = process.ak4PFJets.clone(rParam = 0.80)
process.CustomAK8PFJets = process.ak4PFJets.clone(rParam = 1.00)
process.CustomAK9PFJets = process.ak4PFJets.clone(rParam = 1.20)

process.CustomAK1PFPATJets = cms.EDProducer("PATJetProducer",
   JetFlavourInfoSource = cms.InputTag("ak4PFPatJetFlavourAssociation"),
   JetPartonMapSource = cms.InputTag("ak4PFPatJetFlavourAssociation"),
   addAssociatedTracks = cms.bool(False),
   addBTagInfo = cms.bool(False),
   addDiscriminators = cms.bool(False),
   addEfficiencies = cms.bool(False),
   addGenJetMatch = cms.bool(False),
   addGenPartonMatch = cms.bool(False),
   addJetCharge = cms.bool(False),
   addJetCorrFactors = cms.bool(False),
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
   genJetMatch = cms.InputTag("ak4PFmatch"),
   genPartonMatch = cms.InputTag("ak4PFparton"),
   getJetMCFlavour = cms.bool(False),
   jetChargeSource = cms.InputTag("patJetCharge"),
   jetCorrFactorsSource = cms.VInputTag(cms.InputTag("ak4PFcorr")),
   jetIDMap = cms.InputTag("ak4PFJetID"),
   jetSource = cms.InputTag("CustomAK1PFJets"),
   partonJetSource = cms.InputTag("NOT_IMPLEMENTED"),
   resolutions = cms.PSet(),
   tagInfoSources = cms.VInputTag(),
   trackAssociationSource = cms.InputTag("ak4PFJetTracksAssociatorAtVertex"),
   useLegacyJetMCFlavour = cms.bool(False),
   userData = cms.PSet(
      userCands = cms.PSet(src = cms.VInputTag("")),
      userClasses = cms.PSet(src = cms.VInputTag("")),
      userFloats = cms.PSet(src = cms.VInputTag("")),
      userFunctionLabels = cms.vstring(),
      userFunctions = cms.vstring(),
      userInts = cms.PSet(src = cms.VInputTag(""))
   )
)

process.CustomAK2PFPATJets = process.CustomAK1PFPATJets.clone(jetSource = 'CustomAK2PFJets')
process.CustomAK5PFPATJets = process.CustomAK1PFPATJets.clone(jetSource = 'CustomAK5PFJets')
process.CustomAK6PFPATJets = process.CustomAK1PFPATJets.clone(jetSource = 'CustomAK6PFJets')
process.CustomAK7PFPATJets = process.CustomAK1PFPATJets.clone(jetSource = 'CustomAK7PFJets')
process.CustomAK8PFPATJets = process.CustomAK1PFPATJets.clone(jetSource = 'CustomAK8PFJets')
process.CustomAK9PFPATJets = process.CustomAK1PFPATJets.clone(jetSource = 'CustomAK9PFJets')

process.ak4PFJetAnalyzer.doLifeTimeTagging = cms.untracked.bool(False)

process.ak1PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(jetTag = 'CustomAK1PFPATJets', jetName = 'ak1PF', groomedJets = "ak1PFJets", rParam = 0.15)
process.ak2PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(jetTag = 'CustomAK2PFPATJets', jetName = 'ak2PF', groomedJets = "ak2PFJets", rParam = 0.20)
process.ak5PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(jetTag = 'CustomAK5PFPATJets', jetName = 'ak5PF', groomedJets = "ak5PFJets", rParam = 0.50)
process.ak6PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(jetTag = 'CustomAK6PFPATJets', jetName = 'ak6PF', groomedJets = "ak6PFJets", rParam = 0.60)
process.ak7PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(jetTag = 'CustomAK7PFPATJets', jetName = 'ak7PF', groomedJets = "ak7PFJets", rParam = 0.80)
process.ak8PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(jetTag = 'CustomAK8PFPATJets', jetName = 'ak8PF', groomedJets = "ak8PFJets", rParam = 1.00)
process.ak9PFJetAnalyzer = process.ak4PFJetAnalyzer.clone(jetTag = 'CustomAK9PFPATJets', jetName = 'ak9PF', groomedJets = "ak9PFJets", rParam = 1.20)


#########################
# Main analysis list
#########################

process.ana_step = cms.Path(
   process.hltanalysis *
   process.hltobject *
   # process.l1object +
   process.hiEvtAnalyzer *
   process.jetSequence +
   # Should be added in the path for VID module
   # process.egmGsfElectronIDSequence +
   # process.ggHiNtuplizer +
   # process.ggHiNtuplizerGED +
   process.pfcandAnalyzer +
   process.CustomAK1PFJets * process.CustomAK1PFPATJets * process.ak1PFJetAnalyzer +
   process.CustomAK2PFJets * process.CustomAK2PFPATJets * process.ak2PFJetAnalyzer +
   process.CustomAK5PFJets * process.CustomAK5PFPATJets * process.ak5PFJetAnalyzer +
   process.CustomAK6PFJets * process.CustomAK6PFPATJets * process.ak6PFJetAnalyzer +
   process.CustomAK7PFJets * process.CustomAK7PFPATJets * process.ak7PFJetAnalyzer +
   process.CustomAK8PFJets * process.CustomAK8PFPATJets * process.ak8PFJetAnalyzer +
   process.CustomAK9PFJets * process.CustomAK9PFPATJets * process.ak9PFJetAnalyzer +
   process.HiForest
   # process.trackSequencesPP
)

#####################################################################################

#####################################################################################

#########################
# Event Selection
#########################

process.load('HeavyIonsAnalysis.JetAnalysis.EventSelection_cff')
process.pHBHENoiseFilterResultProducer = cms.Path(process.HBHENoiseFilterResultProducer)
process.HBHENoiseFilterResult = cms.Path(process.fHBHENoiseFilterResult)
process.HBHENoiseFilterResultRun1 = cms.Path(process.fHBHENoiseFilterResultRun1)
process.HBHENoiseFilterResultRun2Loose = cms.Path(process.fHBHENoiseFilterResultRun2Loose)
process.HBHENoiseFilterResultRun2Tight = cms.Path(process.fHBHENoiseFilterResultRun2Tight)
process.HBHEIsoNoiseFilterResult = cms.Path(process.fHBHEIsoNoiseFilterResult)

process.PAprimaryVertexFilter = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"),
    filter = cms.bool(True), # otherwise it won't filter the events
)

process.NoScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.pPAprimaryVertexFilter = cms.Path(process.PAprimaryVertexFilter)
process.pBeamScrapingFilter=cms.Path(process.NoScraping)

process.load("HeavyIonsAnalysis.VertexAnalysis.PAPileUpVertexFilter_cff")
process.pVertexFilterCutG = cms.Path(process.pileupVertexFilterCutG)
process.pVertexFilterCutGloose = cms.Path(process.pileupVertexFilterCutGloose)
process.pVertexFilterCutGtight = cms.Path(process.pileupVertexFilterCutGtight)
process.pVertexFilterCutGplus = cms.Path(process.pileupVertexFilterCutGplus)
process.pVertexFilterCutE = cms.Path(process.pileupVertexFilterCutE)
process.pVertexFilterCutEandG = cms.Path(process.pileupVertexFilterCutEandG)

process.pAna = cms.EndPath(process.skimanalysis)

# Customization

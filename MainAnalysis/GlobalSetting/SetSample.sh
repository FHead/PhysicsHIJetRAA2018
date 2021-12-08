#!/bin/bash

EOSHI=/eos/cms/store/group/phys_heavyions/chenyi
EOSHIOps=/eos/cms/store/group/phys_heavyions_ops/chenyi
EOSHI2017=${EOSHI}/pp2017/Forest/
EOSHI2018=${EOSHI}/PbPb2018/Forest/
EOSHIOps2017=${EOSHIOps}/pp2017/Forest/

for $ in 1 2 3 4 5 6 7 8 9
do
   # PbPb Data
   DHSet GlobalSetting.dh Sample PbPbData${R} string ${EOSHI2018}/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataHPForJetRAAHighThresholdJet100OnlyRetry2/211204_093116/

   # PbPb MC
   DHSet GlobalSetting.dh Sample PbPbMC${R} string ${EOSHI2018}/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//

   # PP NonUL Data
   # DHSet GlobalSetting.dh Sample PPData${R} string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/

   # PP Data UL
   DHSet GlobalSetting.dh Sample PPData${R} string ${EOSHI2017}/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold

   # PP NonUL MC
   # DHSet GlobalSetting.dh Sample PPMC${R} string ${EOSHI2017}/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//

   # PP MC UL
   DHSet GlobalSetting.dh Sample PPMC${R} string ${EOSHIOps2017}/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
done


# Old locations

# PbPb Data Split Nov 2021 version
# DHSet GlobalSetting.dh Sample PbPbData1 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12WithRhoGenBugFix/211106_162257/
# DHSet GlobalSetting.dh Sample PbPbData2 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12WithRhoGenBugFix/211106_162257/
# DHSet GlobalSetting.dh Sample PbPbData3 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
# DHSet GlobalSetting.dh Sample PbPbData4 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
# DHSet GlobalSetting.dh Sample PbPbData5 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
# DHSet GlobalSetting.dh Sample PbPbData6 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67WithRhoGenBugFixRetry/211120_101659/
# DHSet GlobalSetting.dh Sample PbPbData7 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67WithRhoGenBugFixRetry/211120_101659/
# DHSet GlobalSetting.dh Sample PbPbData8 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit8WithRhoGenBugFix/211106_162321/
# DHSet GlobalSetting.dh Sample PbPbData9 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit9WithRhoGenBugFix/211106_162329/
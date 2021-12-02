


default: DefaultSettings TAASettings SampleSettings

DefaultSettings:
	DHSet GlobalSetting.dh "Global" "JetR" string "1 2 3 4 5 6 7 8 9"
	DHSet GlobalSetting.dh "Global" "Centrality" string "0to10 10to30 30to50 50to90"
	# Initial naive Binning
	# DHSet GlobalSetting.dh "Binning" "GenPT" string "20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500"
	# DHSet GlobalSetting.dh "Binning" "RecoPT" string "20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500"
	# ATLAS Binning
	# DHSet GlobalSetting.dh "Binning" "GenPT" string "20,25,30,35,40,45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1100,1200,1300,1400,1500"
	# DHSet GlobalSetting.dh "Binning" "RecoPT" string "20,25,30,35,40,45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1100,1200,1300,1400,1500"
	# Binning to be used for MinPT = 40
	DHSet GlobalSetting.dh "Binning" "GenPT" string "45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1200,1500"
	DHSet GlobalSetting.dh "Binning" "RecoPT" string "45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1200,1500"
	DHSet GlobalSetting.dh "Binning" "GenMin" float 40
	DHSet GlobalSetting.dh "Binning" "RecoMin" float 40
	DHSet GlobalSetting.dh "Binning" "PTUnderflow" int 13
	DHSet GlobalSetting.dh "Binning" "PTOverflow" int 0
	DHSet GlobalSetting.dh "Binning" "JetExclusion" string "-0.5,1.5,0.0,1.0,-2.0,-1.0,-1.8,-0.9"
	DHSet GlobalSetting.dh "JetR" "1" float 0.15
	DHSet GlobalSetting.dh "JetR" "2" float 0.20
	DHSet GlobalSetting.dh "JetR" "3" float 0.30
	DHSet GlobalSetting.dh "JetR" "4" float 0.40
	DHSet GlobalSetting.dh "JetR" "5" float 0.50
	DHSet GlobalSetting.dh "JetR" "6" float 0.60
	DHSet GlobalSetting.dh "JetR" "7" float 0.80
	DHSet GlobalSetting.dh "JetR" "8" float 1.00
	DHSet GlobalSetting.dh "JetR" "9" float 1.20
	DHSet GlobalSetting.dh "JetRMatch" "1" float 0.07
	DHSet GlobalSetting.dh "JetRMatch" "2" float 0.10
	DHSet GlobalSetting.dh "JetRMatch" "3" float 0.15
	DHSet GlobalSetting.dh "JetRMatch" "4" float 0.20
	DHSet GlobalSetting.dh "JetRMatch" "5" float 0.25
	DHSet GlobalSetting.dh "JetRMatch" "6" float 0.30
	DHSet GlobalSetting.dh "JetRMatch" "7" float 0.40
	DHSet GlobalSetting.dh "JetRMatch" "8" float 0.50
	DHSet GlobalSetting.dh "JetRMatch" "9" float 0.60
	DHSet GlobalSetting.dh "CentralityMin" "0to10" float 0.00
	DHSet GlobalSetting.dh "CentralityMin" "10to30" float 0.10
	DHSet GlobalSetting.dh "CentralityMin" "30to50" float 0.30
	DHSet GlobalSetting.dh "CentralityMin" "50to90" float 0.50
	DHSet GlobalSetting.dh "CentralityMin" "Inclusive" float -999
	DHSet GlobalSetting.dh "CentralityMax" "0to10" float 0.10
	DHSet GlobalSetting.dh "CentralityMax" "10to30" float 0.30
	DHSet GlobalSetting.dh "CentralityMax" "30to50" float 0.50
	DHSet GlobalSetting.dh "CentralityMax" "50to90" float 0.90
	DHSet GlobalSetting.dh "CentralityMax" "Inclusive" float 999

EOSHI = /eos/cms/store/group/phys_heavyions/chenyi
EOSHIOps = /eos/cms/store/group/phys_heavyions_ops/chenyi
EOSHI2017 = $(EOSHI)/pp2017/Forest/
EOSHI2018 = $(EOSHI)/PbPb2018/Forest/
EOSHIOps2017 = $(EOSHIOps)/pp2017/Forest/

SampleSettings:
	# PbPb Data
	DHSet GlobalSetting.dh Sample PbPbData1 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12WithRhoGenBugFix/211106_162257/
	DHSet GlobalSetting.dh Sample PbPbData2 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12WithRhoGenBugFix/211106_162257/
	DHSet GlobalSetting.dh Sample PbPbData3 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
	DHSet GlobalSetting.dh Sample PbPbData4 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
	DHSet GlobalSetting.dh Sample PbPbData5 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
	DHSet GlobalSetting.dh Sample PbPbData6 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67WithRhoGenBugFixRetry/211120_101659/
	DHSet GlobalSetting.dh Sample PbPbData7 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67WithRhoGenBugFixRetry/211120_101659/
	DHSet GlobalSetting.dh Sample PbPbData8 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit8WithRhoGenBugFix/211106_162321/
	DHSet GlobalSetting.dh Sample PbPbData9 string $(EOSHI2018)/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit9WithRhoGenBugFix/211106_162329/
	# PbPb MC
	DHSet GlobalSetting.dh Sample PbPbMC1 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC2 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC3 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC4 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC5 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC6 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC7 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC8 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	DHSet GlobalSetting.dh Sample PbPbMC9 string $(EOSHI2018)/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
	# PP Data
	# DHSet GlobalSetting.dh Sample PPData1 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData2 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData3 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData4 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData5 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData6 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData7 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData8 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# DHSet GlobalSetting.dh Sample PPData9 string $(EOSHI2017)/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20211115FullRunHighEGJetNoTrackTree/211115_214540/
	# PP Data UL
	DHSet GlobalSetting.dh Sample PPData1 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData2 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData3 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData4 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData5 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData6 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData7 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData8 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	DHSet GlobalSetting.dh Sample PPData9 string $(EOSHI2017)/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold
	# PP MC
	# DHSet GlobalSetting.dh Sample PPMC1 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC2 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC3 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC4 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC5 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC6 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC7 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC8 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# DHSet GlobalSetting.dh Sample PPMC9 string $(EOSHI2017)/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
	# PP MC UL
	DHSet GlobalSetting.dh Sample PPMC1 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC2 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC3 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC4 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC5 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC6 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC7 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC8 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest
	DHSet GlobalSetting.dh Sample PPMC9 string $(EOSHIOps2017)/RunIISummer20UL17pp5TeV/anstahll-QCD_pThat-15_Dijet_TuneCP5_5p02TeV-pythia8_MINIAOD_20211122-4230e9eff0736cf0d162fef5ca3cfbe4/USER/RunIISummer20UL17pp5TeV/2021122PrivateDijetJECForest

TAASettings:
	# These values from previous RAA paper
	DHSet GlobalSetting.dh "TAA" "0to10" float 23.2
	DHSet GlobalSetting.dh "TAAErrorUp" "0to10" float 0.4
	DHSet GlobalSetting.dh "TAAErrorDown" "0to10" float 0.7
	DHSet GlobalSetting.dh "TAA" "10to30" float 11.5
	DHSet GlobalSetting.dh "TAAErrorUp" "10to30" float 0.3
	DHSet GlobalSetting.dh "TAAErrorDown" "10to30" float 0.4
	DHSet GlobalSetting.dh "TAA" "30to50" float 3.82
	DHSet GlobalSetting.dh "TAAErrorUp" "30to50" float 0.21
	DHSet GlobalSetting.dh "TAAErrorDown" "30to50" float 0.21
	DHSet GlobalSetting.dh "TAA" "50to90" float 0.440
	DHSet GlobalSetting.dh "TAAErrorUp" "50to90" float 0.049
	DHSet GlobalSetting.dh "TAAErrorDown" "50to90" float 0.032
	# These values from 1710.07098
	DHSet GlobalSetting.dh "TAA" "0to5" float 26.1
	DHSet GlobalSetting.dh "TAAErrorUp" "0to5" float 2.2
	DHSet GlobalSetting.dh "TAAErrorDown" "0to5" float 2.2
	DHSet GlobalSetting.dh "TAA" "5to10" float 20.4
	DHSet GlobalSetting.dh "TAAErrorUp" "5to10" float 1.7
	DHSet GlobalSetting.dh "TAAErrorDown" "5to10" float 1.7
	DHSet GlobalSetting.dh "TAA" "10to15" float 16.1
	DHSet GlobalSetting.dh "TAAErrorUp" "10to15" float 1.4
	DHSet GlobalSetting.dh "TAAErrorDown" "10to15" float 1.4
	DHSet GlobalSetting.dh "TAA" "15to20" float 12.7
	DHSet GlobalSetting.dh "TAAErrorUp" "15to20" float 1.2
	DHSet GlobalSetting.dh "TAAErrorDown" "15to20" float 1.2
	DHSet GlobalSetting.dh "TAA" "20to25" float 9.88
	DHSet GlobalSetting.dh "TAAErrorUp" "20to25" float 1.1
	DHSet GlobalSetting.dh "TAAErrorDown" "20to25" float 1.1
	DHSet GlobalSetting.dh "TAA" "25to30" float 7.63
	DHSet GlobalSetting.dh "TAAErrorUp" "25to30" float 0.95
	DHSet GlobalSetting.dh "TAAErrorDown" "25to30" float 0.95
	DHSet GlobalSetting.dh "TAA" "30to35" float 5.81
	DHSet GlobalSetting.dh "TAAErrorUp" "30to35" float 0.84
	DHSet GlobalSetting.dh "TAAErrorDown" "30to35" float 0.84
	DHSet GlobalSetting.dh "TAA" "35to40" float 4.36
	DHSet GlobalSetting.dh "TAAErrorUp" "35to40" float 0.74
	DHSet GlobalSetting.dh "TAAErrorDown" "35to40" float 0.74
	DHSet GlobalSetting.dh "TAA" "40to45" float 3.2
	DHSet GlobalSetting.dh "TAAErrorUp" "40to45" float 0.64
	DHSet GlobalSetting.dh "TAAErrorDown" "40to45" float 0.64
	DHSet GlobalSetting.dh "TAA" "45to50" float 2.3
	DHSet GlobalSetting.dh "TAAErrorUp" "45to50" float 0.54
	DHSet GlobalSetting.dh "TAAErrorDown" "45to50" float 0.54
	DHSet GlobalSetting.dh "TAA" "50to55" float 1.62
	DHSet GlobalSetting.dh "TAAErrorUp" "50to55" float 0.45
	DHSet GlobalSetting.dh "TAAErrorDown" "50to55" float 0.45
	DHSet GlobalSetting.dh "TAA" "55to60" float 1.11
	DHSet GlobalSetting.dh "TAAErrorUp" "55to60" float 0.36
	DHSet GlobalSetting.dh "TAAErrorDown" "55to60" float 0.36
	DHSet GlobalSetting.dh "TAA" "60to65" float 0.738
	DHSet GlobalSetting.dh "TAAErrorUp" "60to65" float 0.28
	DHSet GlobalSetting.dh "TAAErrorDown" "60to65" float 0.28
	DHSet GlobalSetting.dh "TAA" "65to70" float 0.479
	DHSet GlobalSetting.dh "TAAErrorUp" "65to70" float 0.22
	DHSet GlobalSetting.dh "TAAErrorDown" "65to70" float 0.22
	DHSet GlobalSetting.dh "TAA" "70to75" float 0.304
	DHSet GlobalSetting.dh "TAAErrorUp" "70to75" float 0.16
	DHSet GlobalSetting.dh "TAAErrorDown" "70to75" float 0.16
	DHSet GlobalSetting.dh "TAA" "75to80" float 0.19
	DHSet GlobalSetting.dh "TAAErrorUp" "75to80" float 0.12
	DHSet GlobalSetting.dh "TAAErrorDown" "75to80" float 0.12
	DHSet GlobalSetting.dh "TAA" "80to85" float 0.118
	DHSet GlobalSetting.dh "TAAErrorUp" "80to85" float 0.086
	DHSet GlobalSetting.dh "TAAErrorDown" "80to85" float 0.086
	DHSet GlobalSetting.dh "TAA" "85to90" float 0.0752
	DHSet GlobalSetting.dh "TAAErrorUp" "85to90" float 0.06
	DHSet GlobalSetting.dh "TAAErrorDown" "85to90" float 0.06
	DHSet GlobalSetting.dh "TAA" "90to95" float 0.0484
	DHSet GlobalSetting.dh "TAAErrorUp" "90to95" float 0.041
	DHSet GlobalSetting.dh "TAAErrorDown" "90to95" float 0.041
	DHSet GlobalSetting.dh "TAA" "95to100" float 0.0301
	DHSet GlobalSetting.dh "TAAErrorUp" "95to100" float 0.025
	DHSet GlobalSetting.dh "TAAErrorDown" "95to100" float 0.025





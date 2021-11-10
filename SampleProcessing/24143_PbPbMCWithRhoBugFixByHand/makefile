
GetFileList:
	dasgoclient -query 'file dataset=/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM' | head -n200 > filelist.txt

PrepareSubmission:
	bash CreateCondor.sh


GetFileList:
	dasgoclient -query 'file dataset=/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD' | head -n25 > filelist.txt

PrepareSubmission:
	bash CreateCondor.sh

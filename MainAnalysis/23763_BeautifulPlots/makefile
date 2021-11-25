default: RunJetPT RunJetPTClosure

Prepare:
	rm -f OriginalInput Input Systematics HEPData
	ln -sf ../23762_UnfoldPreparation/Output OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23763_Systematics/Output Systematics
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ../24113_HEPData/ HEPData
	mkdir -p Plots Root

Clean:
	rm -f Plots/*pdf
	rm -f Root/*root

Deploy:
	mkdir -p ../FinalResult/Unfolded/
	cp Plots/*.pdf ../FinalResult/Unfolded/

RunJetPT: Execute
	bash RunFile.sh PbPbData "" 0
	bash RunFile.sh PPData   "" 1

RunJetPTClosure: Execute
	bash RunFile.sh PbPbMCRho Toy 0
	bash RunFile.sh PPMC      Toy 1

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute

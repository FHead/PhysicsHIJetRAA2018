default: RunTestRunJetPT RunTestRunJetPTClosure

Prepare:
	rm -f OriginalInput Input Systematics
	ln -sf ../23762_UnfoldPreparation/Output OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23763_Systematics/Output Systematics
	ln -sf ../GlobalSetting/GlobalSetting.dh
	mkdir -p Plots

Deploy:
	mkdir -p ../FinalResult/Unfolded/
	cp Plots/*.pdf ../FinalResult/Unfolded/

RunTestRunJetPT: Execute
	bash RunFile.sh TestRunData "" 0
	bash RunFile.sh TestRunPPData "" 1

RunTestRunJetPTClosure: Execute
	bash RunFile.sh TestRunMC Toy 0
	bash RunFile.sh TestRunPPMC Toy 1

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute

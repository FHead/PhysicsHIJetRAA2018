default: RunJetPT

Prepare:
	rm -f OriginalInput Input Systematics HEPData CombinedSystematics
	ln -sf ../23762_UnfoldPreparation/Output OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23763_Systematics/Output Systematics
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ../24114_PPRatioHEPData/ HEPData
	ln -sf ../24165_SystematicsCombination/Output/ CombinedSystematics
	mkdir -p Plots

Clean:
	rm -f Plots/*

RunJetPT: Execute
	bash RunJetPT.sh

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute

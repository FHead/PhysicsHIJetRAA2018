default: RunJetPT

Prepare:
	rm -f OriginalInput Input Systematics HEPData CombinedSystematics
	ln -sf $(ProjectBase)/MainAnalysis/24236_RebinUnfoldInput//Output OriginalInput
	ln -sf $(ProjectBase)/MainAnalysis/23762_ActualUnfold/Output Input
	ln -sf $(ProjectBase)/MainAnalysis/23763_Systematics/Output Systematics
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh
	ln -sf $(ProjectBase)/MainAnalysis/24114_PPRatioHEPData/ HEPData
	ln -sf $(ProjectBase)/MainAnalysis/24165_SystematicsCombination/Output/ CombinedSystematics
	mkdir -p Plots

Clean:
	rm -f Plots/*

RunJetPT: Execute
	bash RunJetPT.sh

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute

Deploy:
	mkdir -p $(DeployBase)/Result/PPRatio/
	cp Plots/* $(DeployBase)/Result/PPRatio/



default: Prepare RunTestRunData

Prepare:
	rm -f Input BinMapping OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23762_UnfoldPreparation/Output BinMapping
	ln -sf ../GlobalSetting/GlobalSetting.dh
	mkdir -p Output Plot

RunTestRunData: Execute
	bash RunFile.sh TestRunData 0
	bash RunFile.sh TestRunPPData 1

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot






default: Prepare RunTestRunData

Prepare:
	rm -f Input BinMapping OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23762_UnfoldPreparation/Output BinMapping
	ln -sf ../GlobalSetting/GlobalSetting.dh
	mkdir -p Output Plot

RunData: Execute
	bash RunFile.sh PbPbData 0
	bash RunFile.sh PPData 1

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot






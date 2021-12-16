default: Prepare TestIteration

Prepare:
	rm -f Input BinMapping OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23762_UnfoldPreparation/Output BinMapping
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ../GlobalSetting/GlobalSystematics.dh
	mkdir -p Output Plot

Clean:
	rm -f Output/*root
	rm -f Plot/*pdf

RunData: Execute ExecutePlot ExecuteIteration
	bash RunFile.sh PbPbData 0
	bash RunFile.sh PPData 1

Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot

ExecuteIteration: FindIteration.cpp
	g++ FindIteration.cpp  -o ExecuteIteration \
		`root-config --cflags --glibs` \
		-I${RootMacrosBase}

TestIteration: ExecuteIteration
	./ExecuteIteration --Input Input/PPData_R4_CentralityInclusive_Nominal_Power50Prior.root \
		--Mode Next --Iteration 11
	./ExecuteIteration --Input Input/PPData_R4_CentralityInclusive_Nominal_Power50Prior.root \
		--Mode Previous --Iteration 11



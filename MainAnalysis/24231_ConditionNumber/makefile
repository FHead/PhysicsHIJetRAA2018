
default: TestRun

Prepare:
	rm -f Input
	ln -fs $(ProjectBase)/MainAnalysis/23762_UnfoldPreparation/Output Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .

Execute: EvaluateConditionNumber.cpp
	CompileRootMacro EvaluateConditionNumber.cpp Execute

ExecutePlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp ExecutePlot

TestRun: Execute
	./Execute --Input Input/PbPbData_R4_Centrality50to90_Nominal.root --Response HResponse --DHFile Condition.dh

RunAll: RunNominal RunNominalPlot RunOther

RunNominal: Execute
	bash RunNominal.sh

RunNominalPlot: ExecutePlot
	./ExecutePlot --DHFile Condition.dh --Output ConditionMC.pdf --PPBase PPMC --AABase PbPbMCRho
	./ExecutePlot --DHFile Condition.dh --Output ConditionData.pdf --PPBase PPData --AABase PbPbData

RunOther: Execute
	bash RunOther.sh

Deploy:
	mkdir -p $(DeployBase)/Check/ConditionNumber/
	cp Condition*pdf $(DeployBase)/Check/ConditionNumber/



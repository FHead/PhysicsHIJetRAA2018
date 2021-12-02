
default: TestRunPlot

RunAll: Execute ExecutePlot
	bash RunAll.sh

TestRun: Execute
	./Execute --Input PPMC_R4_CentralityInclusive.root --GenBin 50 --MinStats 10000 \
		--FractionEachSide 0.025 --Output PPMC_R4_CentralityInclusive.pdf --GenPTMin 30 \
		--DHFile PPMC_R4_CentralityInclusive.dh

TestRunPlot: ExecutePlot
	./ExecutePlot --Input PPMC_R4_CentralityInclusive.dh --Output PPMC_R4_CentralityInclusive_Summary.pdf

Execute: CalculateJER.cpp
	CompileRootMacro CalculateJER.cpp Execute

ExecutePlot: PlotSummary.cpp
	CompileRootMacro PlotSummary.cpp ExecutePlot


default: TestRun

RunAll: Execute ExecutePlot
	bash RunAll.sh

TestRun: Execute ExecutePlot
	./Execute --Input ROOT/PbPbMCRho_R4_Centrality0to10.root --GenBin 50 --MinStats 10000 \
		--FractionEachSide 0.025 --Output PbPbMCRho_R4_Centrality0to10.pdf --GenPTMin 30 \
		--DHFile PbPbMCRho_R4_Centrality0to10.dh
	./ExecutePlot --Input PbPbMCRho_R4_Centrality0to10.dh \
		--Output PbPbMCRho_R4_Centrality0to10_Summary.pdf

TestRunPP: Execute
	./Execute --Input PPMC_R4_CentralityInclusive.root --GenBin 50 --MinStats 10000 \
		--FractionEachSide 0.025 --Output PPMC_R4_CentralityInclusive.pdf --GenPTMin 30 \
		--DHFile PPMC_R4_CentralityInclusive.dh

TestRunPlot: ExecutePlot
	./ExecutePlot --Input PPMC_R4_CentralityInclusive.dh --Output PPMC_R4_CentralityInclusive_Summary.pdf

Execute: CalculateJER.cpp
	CompileRootMacro CalculateJER.cpp Execute

ExecutePlot: PlotSummary.cpp
	CompileRootMacro PlotSummary.cpp ExecutePlot

default: TestRun

Prepare:
	rm -f MBInput HPInput
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh
	ln -sf $(ProjectBase)/DataPerformance/24261_TriggerTurnOnBatchRun/Output MBInput
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output HPInput

ExecuteFit: FitDip.cpp
	CompileRootMacro FitDip.cpp ExecuteFit

ExecuteDipPlot: VisualizeDipSize.cpp
	CompileRootMacro VisualizeDipSize.cpp ExecuteDipPlot

Execute: CheckUEBug.cpp
	CompileRootMacro CheckUEBug.cpp Execute

TestRunFit: ExecuteFit
	./ExecuteFit --Input MBInput/PbPbMBData_R4_CentralityInclusive.root \
		--PTMin 150 --PhiMin 2 --PhiMax -2 \
		--DHFile Dip.dh --DHState R4_CentralityAll_PT150

TestRunDipPlot: ExecuteDipPlot
	./ExecuteDipPlot

TestRun: Execute
	./Execute --Input HPInput/PbPbData_R4_Centrality0to10.root \
		--PTMin 200 --PTMax 1500 \
		--DHFile Dip.dh --DHState R4_CentralityAll_PT160
	./Execute --Input HPInput/PbPbData_R4_Centrality0to10.root \
		--PTMin 200 --PTMax 1500 \
		--DHFile Dip.dh --DHState R4_CentralityAll_PT200

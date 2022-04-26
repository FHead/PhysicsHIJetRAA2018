
# default: FitAll #TestRunMatch TestRunFit
default: RunVisualize

Prepare:
	rm -f GlobalSetting.dh Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .
	ln -sf /eos/user/c/chenyi//BatchOutput/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23752_CopyJetFromForest// Input

TestRun: Execute
	./Execute --Data Input/PbPbData_R1_Centrality50to90.root \
		--MC Input/PbPbMC_R1_CentralityInclusive.root \
		--JetMinPT 131.387 --Output root/Output_R1_Centrality50to90.root

TestRunMatch: ExecuteMatch
	./ExecuteMatch --Input root/Output_R1_Centrality50to90.root \
		--Output pdf/Output_R1_Centrality50to90.pdf \
		--RootOutput graph/Output_R1_Centrality50to90.root \
		--BinCount 100 --BinMagnification 25 --SkipFinalBin true

Execute: StripTree.cpp
	CompileRootMacro StripTree.cpp Execute

ExecuteMatch: MatchUE.cpp
	CompileRootMacro MatchUE.cpp ExecuteMatch

RunAll: Execute
	bash RunFile.sh

ExecuteFit: FitRatio.cpp
	CompileRootMacro FitRatio.cpp ExecuteFit

TestRunFit: ExecuteFit
	./ExecuteFit --Input graph/Output_R1_Centrality50to90.root \
		--Output pdf/Fit_R1_Centrality50to90.pdf \
		--DHFile GlobalSetting.dh --Key R1_Centrality50to90 --Order1 8 --Order2 0

FitAll: ExecuteMatch ExecuteFit
	bash BinFile.sh
	bash FitFile.sh

ExecuteVisualize: VisualizeDifference.cpp
	CompileRootMacro VisualizeDifference.cpp ExecuteVisualize

RunVisualize: ExecuteVisualize
	./ExecuteVisualize --DHFile GlobalSetting.dh --DHFileNew GlobalSettingTemp.dh --Output RhoWeightComparison.pdf


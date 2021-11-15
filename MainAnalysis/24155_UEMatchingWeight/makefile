
default: TestRunFit

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
		--BinCount 100 --BinMagnification 20 --SkipFinalBin true

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
		--DHFile GlobalSetting.dh --Key R1_Centrality50to90 --Order1 3 --Order2 4

FitAll: ExecuteFit
	bash RunFit.sh


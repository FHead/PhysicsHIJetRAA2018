


default: TestRun

Prepare:
	rm -f Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .
	# ln -sf $(ProjectBase)/MainAnalysis/23762_ActualUnfold/Output/ Input
	ln -sf $(ProjectBase)/MainAnalysis/23762_UnfoldPreparation/Output/ Input

TestRun: Execute
	./Execute --DHFile GlobalSetting.dh --Base R1_Centrality50to90 \
		--NominalFile Input/PbPbData_R1_Centrality50to90_Nominal.root \
		--MaxPT 1500 \
		--DoRecoStat true --RecoStatLimit 5 \
		--DoRecoStatResolution false --RecoStatResolutionShift 1 --ResolutionFile NONE

RunAll: Execute
	bash RunAll.sh

Execute: GetUpperBound.cpp
	CompileRootMacro GetUpperBound.cpp Execute -I$(ProjectBase)/CommonCode/include

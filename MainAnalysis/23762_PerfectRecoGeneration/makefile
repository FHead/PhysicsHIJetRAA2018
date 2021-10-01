
default: Prepare

Prepare:
	mkdir -p Output
	rm -f Input UnfoldedInput
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_ActualUnfold/Output UnfoldedInput

TestRun: Execute
	./Execute --MC Input/TestRunMC.root --Yield Input/TestRunData.root \
		--Gen Input/TestRunMC.root --GenHistogram HMCGen \
		--Output Output/PerfectRecoTestRunMC.root
	./Execute --MC Input/TestRunMC0to10.root --Yield Input/TestRunData0to10.root \
		--Gen Input/TestRunMC0to10.root --GenHistogram HMCGen \
		--Output Output/PerfectRecoTestRunMC0to10.root
	./Execute --MC Input/TestRunMC50to90.root --Yield Input/TestRunData50to90.root \
		--Gen Input/TestRunMC50to90.root --GenHistogram HMCGen \
		--Output Output/PerfectRecoTestRunMC50to90.root

Execute: GeneratePerfectData.cpp
	CompileRootMacro GeneratePerfectData.cpp Execute

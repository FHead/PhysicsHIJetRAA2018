
default: Prepare

Prepare:
	mkdir -p Output
	rm -f Input UnfoldedInput
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_ActualUnfold/Output UnfoldedInput
	ln -sf ../GlobalSetting/GlobalSetting.dh

TestRun: Execute
	bash RunFile.sh TestRunMC Nominal 0
	bash RunFile.sh TestRunPPMC Nominal 1

TestRunData: Execute
	bash RunFile.sh TestRunData Nominal 0 TestRunMC
	bash RunFile.sh TestRunPPData Nominal 1 TestRunPPMC

Execute: GeneratePerfectData.cpp
	CompileRootMacro GeneratePerfectData.cpp Execute

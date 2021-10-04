
default: Prepare

Prepare:
	mkdir -p Output
	rm -f Input UnfoldedInput
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_ActualUnfold/Output UnfoldedInput
	ln -sf ../GlobalSetting/GlobalSetting.dh

TestRun: Execute
	bash RunFile.sh TestRunMC Nominal

Execute: GeneratePerfectData.cpp
	CompileRootMacro GeneratePerfectData.cpp Execute

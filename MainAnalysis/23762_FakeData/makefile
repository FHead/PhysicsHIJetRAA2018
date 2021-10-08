
default: Prepare

Prepare:
	rm -f PerfectInput Input
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_PerfectRecoGeneration/Output PerfectInput
	ln -sf ../GlobalSetting/GlobalSetting.dh
	mkdir -p Output

TestRun: Execute
	bash RunFile.sh TestRunMC Nominal TestRunData Nominal 1.00 0
	bash RunFile.sh TestRunPPMC Nominal TestRunPPData Nominal 1.00 1

TestRunData: Execute
	bash RunFile.sh TestRunData Nominal TestRunData Nominal 1.00 0
	bash RunFile.sh TestRunPPData Nominal TestRunPPData Nominal 1.00 1

Execute: GenerateFakeData.cpp
	CXXFLAGS="-mmacosx-version-min=11.2" CompileRootMacro GenerateFakeData.cpp Execute 

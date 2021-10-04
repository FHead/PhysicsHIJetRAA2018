
default: Prepare

Prepare:
	rm -f PerfectInput Input
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_PerfectRecoGeneration/Output PerfectInput
	ln -sf ../GlobalSetting/GlobalSetting.dh
	mkdir -p Output

TestRun: Execute
	bash RunFile.sh TestRunMC Nominal TestRunData Nominal 1.00

Execute: GenerateFakeData.cpp
	CXXFLAGS="-mmacosx-version-min=11.2" CompileRootMacro GenerateFakeData.cpp Execute 

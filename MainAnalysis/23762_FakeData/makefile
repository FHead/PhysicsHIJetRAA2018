
default: Prepare

Prepare:
	rm -f PerfectInput Input
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_PerfectRecoGeneration/Output PerfectInput
	ln -sf ../GlobalSetting/GlobalSetting.dh
	mkdir -p Output

RunMC: Execute
	bash RunFile.sh PbPbMCRho Nominal PbPbData Nominal 1.00 0
	bash RunFile.sh PPMC Nominal PPData Nominal 1.00 1

RunData: Execute
	bash RunFile.sh PbPbData Nominal PbPbData Nominal 1.00 0
	bash RunFile.sh PPData Nominal PPData Nominal 1.00 1

Execute: GenerateFakeData.cpp
	CXXFLAGS="-mmacosx-version-min=11.2" CompileRootMacro GenerateFakeData.cpp Execute 

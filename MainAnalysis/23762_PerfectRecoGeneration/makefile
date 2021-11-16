
default: Prepare

Prepare:
	mkdir -p Output
	rm -f Input UnfoldedInput
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_ActualUnfold/Output UnfoldedInput
	ln -sf ../GlobalSetting/GlobalSetting.dh

RunMC: Execute
	bash RunFile.sh PbPbMCRho Nominal 0
	bash RunFile.sh PPMC Nominal 1

RunData: Execute
	bash RunFile.sh PbPbData Nominal 0 PbPbMCRho
	bash RunFile.sh PPData Nominal 1 PPMC

Execute: GeneratePerfectData.cpp
	CompileRootMacro GeneratePerfectData.cpp Execute

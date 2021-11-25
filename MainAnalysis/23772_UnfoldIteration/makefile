
default: TestRun TestRunData

Prepare:
	rm -f Input
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	mkdir -p Output

Clean:
	rm -f Output/*pdf

SetDefault:
	bash SetDefaultPriorChoice.sh

RunMC: Execute
	bash RunFile.sh PbPbMCRho Nominal_Toy Nominal Nominal 0
	bash RunFile.sh PPMC      Nominal_Toy Nominal Nominal 1

RunData: Execute
	bash RunFile.sh PbPbData Nominal_Power50Prior_Toy Nominal Nominal 0
	bash RunFile.sh PbPbData Nominal_Power50Prior_Toy Nominal Alternate 0
	bash RunFile.sh PPData Nominal_Power50Prior_Toy Nominal Nominal 1
	bash RunFile.sh PPData Nominal_Power50Prior_Toy Nominal Alternate 1

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute



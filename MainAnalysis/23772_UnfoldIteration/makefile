
default: TestRun TestRunData

Prepare:
	rm -f Input
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	mkdir -p Output

RunMC: Execute
	bash RunFile.sh PbPbMCRho Nominal_Toy 0
	bash RunFile.sh PPMC Nominal_Toy 1

RunData: Execute
	bash RunFile.sh PbPbData Nominal_Toy 0
	bash RunFile.sh PPData Nominal_Toy 1

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute



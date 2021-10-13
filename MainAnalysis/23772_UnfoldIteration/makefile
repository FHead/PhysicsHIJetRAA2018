
default: TestRun TestRunData

Prepare:
	rm -f Input
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	mkdir -p Output

TestRun: Execute
	bash RunFile.sh TestRunMC Nominal_Toy 0
	bash RunFile.sh TestRunPPMC Nominal_Toy 1

TestRunData: Execute
	bash RunFile.sh TestRunData Nominal_Toy 0
	bash RunFile.sh TestRunPPData Nominal_Toy 1

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute



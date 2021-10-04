
default: TestRun

Prepare:
	rm -f Input ToyInput
	ln -sf ../23762_UnfoldPreparation/Output/ Input
	ln -sf ../23762_FakeData/Output/ ToyInput
	ln -sf ../GlobalSetting/GlobalSetting.dh

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

TestRun: Execute
	bash RunFile.sh Input TestRunMC Nominal
	bash RunFile.sh ToyInput TestRunMC Nominal_Toy
	bash RunFile.sh Input TestRunData Nominal
	bash RunFile.sh Input TestRunData JECUp
	bash RunFile.sh Input TestRunData JECDown




default: TestRun TestRunPP

Prepare:
	rm -f Input ToyInput
	ln -sf ../23762_UnfoldPreparation/Output/ Input
	ln -sf ../23762_FakeData/Output/ ToyInput
	ln -sf ../GlobalSetting/GlobalSetting.dh

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

TestRun: Execute
	bash RunFile.sh Input TestRunMC Nominal 0
	bash RunFile.sh ToyInput TestRunMC Nominal_Toy 0
	bash RunFile.sh Input TestRunData Nominal 0
	bash RunFile.sh Input TestRunData JECUp 0
	bash RunFile.sh Input TestRunData JECDown 0
	
TestRunPP: Execute
	bash RunFile.sh Input TestRunPPMC Nominal 1
	bash RunFile.sh ToyInput TestRunPPMC Nominal_Toy 1
	bash RunFile.sh Input TestRunPPData Nominal 1
	bash RunFile.sh Input TestRunPPData JECUp 1
	bash RunFile.sh Input TestRunPPData JECDown 1



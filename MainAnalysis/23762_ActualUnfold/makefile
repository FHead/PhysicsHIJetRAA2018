
default: TestRun

Prepare:
	rm -f Input ToyInput
	ln -sf ../23762_UnfoldPreparation/Output/ Input
	ln -sf ../23762_FakeData/Output/ ToyInput

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

TestRun: Execute
	./Execute --Input Input/TestRunMC.root --Output Output/TestRunMC.root
	./Execute --Input Input/TestRunData.root --Output Output/TestRunData.root
	./Execute --Input Input/TestRunDataJECUp.root --Output Output/TestRunDataJECUp.root
	./Execute --Input Input/TestRunDataJECDown.root --Output Output/TestRunDataJECDown.root
	./Execute --Input ToyInput/ToyTestRunMC.root --Output Output/ToyTestRunMC.root
	./Execute --Input Input/TestRunMC0to10.root --Output Output/TestRunMC0to10.root
	./Execute --Input Input/TestRunData0to10.root --Output Output/TestRunData0to10.root
	./Execute --Input Input/TestRunData0to10JECUp.root --Output Output/TestRunData0to10JECUp.root
	./Execute --Input Input/TestRunData0to10JECDown.root --Output Output/TestRunData0to10JECDown.root
	./Execute --Input ToyInput/ToyTestRunMC0to10.root --Output Output/ToyTestRunMC0to10.root
	./Execute --Input Input/TestRunMC50to90.root --Output Output/TestRunMC50to90.root
	./Execute --Input Input/TestRunData50to90.root --Output Output/TestRunData50to90.root
	./Execute --Input Input/TestRunData50to90JECUp.root --Output Output/TestRunData50to90JECUp.root
	./Execute --Input Input/TestRunData50to90JECDown.root --Output Output/TestRunData50to90JECDown.root
	./Execute --Input ToyInput/ToyTestRunMC50to90.root --Output Output/ToyTestRunMC50to90.root



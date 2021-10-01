
default: Prepare

Prepare:
	rm -f PerfectInput Input
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../23762_PerfectRecoGeneration/Output PerfectInput
	mkdir -p Output

TestRun: Execute
	./Execute --MC Input/TestRunMC.root \
		--Shape PerfectInput/PerfectRecoTestRunMC.root \
		--Yield Input/TestRunData.root \
		--Fraction 100 \
		--Output Output/ToyTestRunMC.root
	./Execute --MC Input/TestRunMC0to10.root \
		--Shape PerfectInput/PerfectRecoTestRunMC0to10.root \
		--Yield Input/TestRunData0to10.root \
		--Fraction 100 \
		--Output Output/ToyTestRunMC0to10.root
	./Execute --MC Input/TestRunMC50to90.root \
		--Shape PerfectInput/PerfectRecoTestRunMC50to90.root \
		--Yield Input/TestRunData50to90.root \
		--Fraction 100 \
		--Output Output/ToyTestRunMC50to90.root

Execute: GenerateFakeData.cpp
	CXXFLAGS="-mmacosx-version-min=11.2" CompileRootMacro GenerateFakeData.cpp Execute 

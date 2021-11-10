
default: TestRun


Prepare:
	rm -f Input
	ln -sf /eos/user/c/chenyi//BatchOutput/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23752_CopyJetFromForest/// Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .

Execute: CheckJets.cpp
	CompileRootMacro CheckJets.cpp Execute -I$(ProjectBase)/CommonCode/include

TestRun: Execute
	./Execute --Input Input/TestRunPPMC_R4_CentralityInclusive.root --Fraction 0.001 \
		--Output Result.pdf

Run: Execute Run.sh
	bash Run.sh

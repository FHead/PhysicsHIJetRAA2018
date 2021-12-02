
default: Prepare TestRun

Prepare:
	rm -f Input Output
	ln -sf /afs/cern.ch/user/c/chenyi/EOSHI/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23752_CopyJetFromForest// Input
	ln -sf  /eos/user/c/chenyi/BatchOutput/PhysicsWorkspace/HIJetRAA2018/JetEnergyResolution/24174_ReduceBranches Output

TestRun: Execute
	./Execute --Input Input/MeowTestRunMC_R4_CentralityInclusive.root \
		--Output Meow.root --JetR 0.4 --Match 0.2

RunPP: Execute
	./Execute --Input Input/PPMC_R1_CentralityInclusive.root \
		--Output Output/PPMC_R1_CentralityInclusive.root \
		--JetR 0.15 --Match 0.08
	./Execute --Input Input/PPMC_R2_CentralityInclusive.root \
		--Output Output/PPMC_R2_CentralityInclusive.root \
		--JetR 0.20 --Match 0.10
	./Execute --Input Input/PPMC_R3_CentralityInclusive.root \
		--Output Output/PPMC_R3_CentralityInclusive.root \
		--JetR 0.30 --Match 0.15
	./Execute --Input Input/PPMC_R4_CentralityInclusive.root \
		--Output Output/PPMC_R4_CentralityInclusive.root \
		--JetR 0.40 --Match 0.20
	./Execute --Input Input/PPMC_R5_CentralityInclusive.root \
		--Output Output/PPMC_R5_CentralityInclusive.root \
		--JetR 0.50 --Match 0.25
	./Execute --Input Input/PPMC_R6_CentralityInclusive.root \
		--Output Output/PPMC_R6_CentralityInclusive.root \
		--JetR 0.60 --Match 0.30
	./Execute --Input Input/PPMC_R7_CentralityInclusive.root \
		--Output Output/PPMC_R7_CentralityInclusive.root \
		--JetR 0.80 --Match 0.40
	./Execute --Input Input/PPMC_R8_CentralityInclusive.root \
		--Output Output/PPMC_R8_CentralityInclusive.root \
		--JetR 1.00 --Match 0.50
	./Execute --Input Input/PPMC_R9_CentralityInclusive.root \
		--Output Output/PPMC_R9_CentralityInclusive.root \
		--JetR 1.20 --Match 0.60

Execute: ReduceSize.cpp
	CompileRootMacro ReduceSize.cpp Execute





default: TestRunJER

Prepare:
	rm -f Input Output
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output Input
	ln -sf $(EOSHI)/PhysicsWorkspace/HIJetRAA2018/DataPerformance/24264_DijetBalance Output

TestRun: Execute
	# ./Execute --Input Input/PbPbData_R4_Centrality50to90.root  --Output Output/PbPbData.root --Fraction 1 --IsMC 0
	# ./Execute --Input Input/PbPbMC_R4_Centrality50to90.root    --Output Output/PbPbMC.root --Fraction 1 --IsMC 1
	# ./Execute --Input Input/PPDataEOY_R4_CentralityInclusive.root --Output Output/PPData.root --Fraction 1 --IsMC 0
	./Execute --Input Input/PPMCEOY_R4_CentralityInclusive.root   --Output Output/PPMC.root   --Fraction 1 --IsMC 1

TestRunJER: ExecuteJER
	# ./ExecuteJER --Data Output/PPData.root --MC Output/PPMC.root --OutputBase PPR4 \
	# 	--PTMin 150 --DPhiMin 2.8 --AlphaMax 0.30
	./ExecuteJER --Data Output/PPDataEOYR1.root --MC Output/PPMCEOYR1.root --OutputBase Result/PPEOYR1 \
		--PTMin 150 --DPhiMin 2.8 --AlphaMax 0.30

ProcessAll: Execute
	bash ProcessFiles.sh

Execute: LeadingDijet.cpp
	CompileRootMacro LeadingDijet.cpp Execute

ExecuteJER: CheckJER.cpp
	CompileRootMacro CheckJER.cpp ExecuteJER

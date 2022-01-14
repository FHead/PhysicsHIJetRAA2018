

default: RunSummary

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

ExecuteSummary: JERSummary.cpp
	CompileRootMacro JERSummary.cpp ExecuteSummary

RunSummary: ExecuteSummary
	./ExecuteSummary \
		--Input Result/PPEOYR1.root,Result/PPEOYR2.root,Result/PPEOYR3.root,Result/PPEOYR4.root,Result/PPEOYR5.root,Result/PPEOYR6.root,Result/PPEOYR7.root,Result/PPEOYR8.root,Result/PPEOYR9.root \
		--R 0.15,0.20,0.30,0.40,0.50,0.60,0.80,1.00,1.20 \
		--Output PPEOY.pdf
	./ExecuteSummary \
		--Input Result/PPULR1.root,Result/PPULR2.root,Result/PPULR3.root,Result/PPULR4.root,Result/PPULR5.root,Result/PPULR6.root,Result/PPULR7.root,Result/PPULR8.root,Result/PPULR9.root \
		--R 0.15,0.20,0.30,0.40,0.50,0.60,0.80,1.00,1.20 \
		--Output PPUL.pdf
	./ExecuteSummary \
		--Input Result/PbPbR1.root,Result/PbPbR2.root,Result/PbPbR3.root,Result/PbPbR4.root,Result/PbPbR5.root,Result/PbPbR6.root,Result/PbPbR7.root,Result/PbPbR8.root,Result/PbPbR9.root \
		--R 0.15,0.20,0.30,0.40,0.50,0.60,0.80,1.00,1.20 \
		--Output PbPb.pdf --Max 1.50
	./ExecuteSummary \
		--Input Result/PbPb2R1.root,Result/PbPb2R2.root,Result/PbPb2R3.root,Result/PbPb2R4.root,Result/PbPb2R5.root,Result/PbPb2R6.root,Result/PbPb2R7.root,Result/PbPb2R8.root,Result/PbPb2R9.root \
		--R 0.15,0.20,0.30,0.40,0.50,0.60,0.80,1.00,1.20 \
		--Output PbPb2.pdf --Max 2.00





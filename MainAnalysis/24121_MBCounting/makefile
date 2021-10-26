
default: Prepare MergeMB TestRun

Prepare:
	rm -f Input MBInput
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ~/EOSHI/PbPb2018/MBCount/HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias0/CountMB0_20211018/211018_182616/0000/ MBInput

MergeMB:
	# hadd -f MergedMB0.root MBInput2/MBCounter*root
	hadd -f MergedMB1.root MB1Input/MBCounter*root

Execute: GetMB.cpp
	CompileRootMacro GetMB.cpp Execute

RunAA: Execute
	for i in Input/TestRunData_R*Nominal_JSON.txt; do bash CheckJSON.sh $$i; done

TestRun: Execute
	./Execute --JSON Input/TestRunData_R9_Centrality50to90_Nominal_JSON.txt \
		--MB1 MergedMB0.root \
		--HLTMatch1 "HLT_HIMinimumBias_","part0" \
		--L1Match1 "L1_MinimumBiasHF1_AND_BptxAND" \
		--MB2 MergedMB1.root \
		--HLTMatch2 "HLT_HIMinimumBias_","part1" \
		--L1Match2 "L1_MinimumBiasHF1_AND_BptxAND" \
		--MB3 MergedMB1.root \
		--HLTMatch3 "HLT_HIMinimumBias_","part2" \
		--L1Match3 "L1_MinimumBiasHF1_AND_BptxAND" \
		--DHFile GlobalSetting.dh --State MBCount --Tag TestRunData_R9_Centrality50to90 --CentralityTag 50to90
	./Execute --JSON Input/TestRunData_R9_Centrality50to90_Nominal_JSON.txt \
		--MB1 MergedMB1.root \
		--HLTMatch1 "HLT_HIMinimumBias_","part1" \
		--L1Match1 "L1_MinimumBiasHF1_AND_BptxAND" \
		--MB2 MergedMB1.root \
		--HLTMatch2 "HLT_HIMinimumBias_","part2" \
		--L1Match2 "L1_MinimumBiasHF1_AND_BptxAND" \
		--MB3 MergedMB0.root \
		--HLTMatch3 "HLT_HIMinimumBias_","part0" \
		--L1Match3 "L1_MinimumBiasHF1_AND_BptxAND" \
		--DHFile GlobalSetting2.dh --State MBCount --Tag TestRunData_R9_Centrality50to90 --CentralityTag 50to90




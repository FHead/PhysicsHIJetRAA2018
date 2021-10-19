
default: Prepare MergeMB TestRun

Prepare:
	rm -f Input MBInput
	ln -sf ../23762_UnfoldPreparation/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ~/EOSHI/PbPb2018/MBCount/HIMinimumBias0/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias0/CountMB0_20211018/211018_182616/0000/ MBInput

MergeMB:
	hadd -f MergedMB.root MBInput/MBCounter*root

Execute: GetMB.cpp
	CompileRootMacro GetMB.cpp Execute

RunAA: Execute
	for i in Input/TestRunData_R*Nominal_JSON.txt; do bash CheckJSON.sh $$i; done

TestRun: Execute
	./Execute --JSON Input/TestRunData_R9_Centrality50to90_Nominal_JSON.txt \
		--MB MergedMB.root \
		--HLTMatch "HLT_HIMinimumBias_","part0" \
		--L1Match "L1_MinimumBiasHF1_AND_BptxAND" \
		--DHFile GlobalSetting.dh --State MBCount --Tag TestRunData_R9_Centrality50to90 --CentralityTag 50to90




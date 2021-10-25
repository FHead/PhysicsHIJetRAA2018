

default: Prepare TestRun

Prepare:
	rm -rf HPInput
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/MBCount/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/CountHP_20211018/211020_104631/0000// HPInput

Execute: AveragePS.cpp
	CompileRootMacro AveragePS.cpp Execute

TestRun: Execute
	./Execute --Input HPInput/TriggerCounter.root \
		--HLT "HLT_HIPuAK4CaloJet80Eta5p1" \
		--L1 "L1_SingleJet44_BptxAND"
	./Execute --Input HPInput/TriggerCounter.root \
		--HLT "HLT_HIPuAK4CaloJet100Eta5p1" \
		--L1 "L1_SingleJet56_BptxAND"


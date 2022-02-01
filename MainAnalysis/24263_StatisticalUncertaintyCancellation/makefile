
default: TestRunSummary

Prepare:
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .
	mkdir -p pdf

ExampleFile = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest//DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116/

TestRun: Execute
	./Execute --Input `find $(ExampleFile) | grep root | head -n5 | tr '\n' ','` \
		--Tree1 akCs4PFJetAnalyzer/t \
		--Tree2 akCs4PFJetAnalyzer/t \
		--DHFile GlobalSetting.dh \
		--MatchAngle 0.15 \
		--EtaMin -2 --EtaMax 2 \
		--Output TestOutput.pdf \
		--NSample 100000 \
		--DHOutput Rho.dh --DHState PbPbR4R4

Execute: Uncertainty.cpp
	CompileRootMacro Uncertainty.cpp Execute -I../../CommonCode/include/ ../../CommonCode/library/Messenger.o

RunAll: Execute
	bash RunAll.sh

ExecuteSummary: SummaryPlots.cpp
	CompileRootMacro SummaryPlots.cpp ExecuteSummary

TestRunSummary: ExecuteSummary
	./ExecuteSummary



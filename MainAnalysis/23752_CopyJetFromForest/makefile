
Fraction = 1.00

default: TestRun

Prepare:
	echo $(ProjectBase)
	ln -sf $(ProjectBase)/Samples/Example SampleExample
	mkdir -p Output/

TestRun: Execute
	./Execute --Input SampleExample/HiForestMiniAOD_QCDFile.root --Output Output/TestRunMC.root \
		--JetR 0.4 --Jet "akCs4PFJetAnalyzer/t" --Fraction $(Fraction) \
		--UseStoredGen true \
		--CheckCentrality true --CentralityMin 0 --CentralityMax 0.90
	./Execute --Input SampleExample/HiForestMiniAOD_DataHardProbes.root --Output Output/TestRunData.root \
		--JetR 0.4 --Jet "akCs4PFJetAnalyzer/t" --Fraction $(Fraction) \
		--UseStoredGen true --Trigger HLT_HIPuAK4CaloJet100Eta5p1 \
		--CheckCentrality true --CentralityMin 0 --CentralityMax 0.90
	./Execute --Input SampleExample/HiForestMiniAOD_QCDFile.root --Output Output/TestRunMC0to10.root \
		--JetR 0.4 --Jet "akCs4PFJetAnalyzer/t" --Fraction $(Fraction) \
		--UseStoredGen true \
		--CheckCentrality true --CentralityMin 0 --CentralityMax 0.10
	./Execute --Input SampleExample/HiForestMiniAOD_DataHardProbes.root --Output Output/TestRunData0to10.root \
		--JetR 0.4 --Jet "akCs4PFJetAnalyzer/t" --Fraction $(Fraction) \
		--UseStoredGen true --Trigger HLT_HIPuAK4CaloJet100Eta5p1 \
		--CheckCentrality true --CentralityMin 0 --CentralityMax 0.10
	./Execute --Input SampleExample/HiForestMiniAOD_QCDFile.root --Output Output/TestRunMC50to90.root \
		--JetR 0.4 --Jet "akCs4PFJetAnalyzer/t" --Fraction $(Fraction) \
		--UseStoredGen true \
		--CheckCentrality true --CentralityMin 0.50 --CentralityMax 0.90
	./Execute --Input SampleExample/HiForestMiniAOD_DataHardProbes.root --Output Output/TestRunData50to90.root \
		--JetR 0.4 --Jet "akCs4PFJetAnalyzer/t" --Fraction $(Fraction) \
		--UseStoredGen true --Trigger HLT_HIPuAK4CaloJet100Eta5p1 \
		--CheckCentrality true --CentralityMin 0.50 --CentralityMax 0.90

Execute: ProcessJets.cpp
	CompileRootMacro ProcessJets.cpp Execute \
		-I$(ProjectBase)/CommonCode/include \
		$(ProjectBase)/CommonCode/library/*.o




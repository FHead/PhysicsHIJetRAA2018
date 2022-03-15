default: TestRun

Prepare:
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output Input
	ln -sf $(EOSHI)/PhysicsWorkspace/HIJetRAA2018/JetEnergyCorrection/24332_SoftFraction Output

Execute: PlotSlope.cpp
	CompileRootMacro PlotSlope.cpp Execute

TestRun: Execute
	./Execute --Input Input/PPMCEOY_R4_CentralityInclusive.root --Output PPR4.pdf \
		--Root Output/PPMCEOY_R4_CentralityInclusive.root \
		--DRMax 0.2 --Fraction 0.05






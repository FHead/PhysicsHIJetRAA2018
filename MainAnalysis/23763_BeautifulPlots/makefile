default: RunTestRunJetPT RunTestRunJetPTClosure

Prepare:
	rm -f OriginalInput Input Systematics
	ln -sf ../23762_UnfoldPreparation/Output OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23763_Systematics/Output Systematics
	mkdir -p Plots

Deploy:
	mkdir -p ../FinalResult/Unfolded/
	cp Plots/*.pdf ../FinalResult/Unfolded/

RunTestRunJetPT: Execute
	./Execute --Input Input/TestRunData.root \
		--Systematic Systematics/TestRunData.root \
		--Output Plots/TestRunDataPlots.pdf --FinalOutput Plots/TestRunData.pdf \
		--MCFile "Input/TestRunData.root" \
		--MCHistogram "HMCTruth" \
		--MCLabel "MC (normalized to data)" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false \
		--WorldXMin 150 --WorldXMax 1000 --WorldYMin 0.0005 --WorldYMax 500 --WorldRMin 0.51 --WorldRMax 1.49 \
		--LogX true --LogY true \
		--XLabel "Jet p_{T} (GeV)" --YLabel "dN / d(Jet p_{T})" --Binning None \
		--LegendX 0.45 --LegendY 0.55 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Anti-k_{T} jet R = 0.4",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"Centrality 0-90%" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/TestRunData0to10.root \
		--Systematic Systematics/TestRunData0to10.root \
		--Output Plots/TestRunData0to10Plots.pdf --FinalOutput Plots/TestRunData0to10.pdf \
		--MCFile "Input/TestRunData0to10.root" \
		--MCHistogram "HMCTruth" \
		--MCLabel "MC (normalized to data)" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false \
		--WorldXMin 150 --WorldXMax 1000 --WorldYMin 0.0005 --WorldYMax 500 --WorldRMin 0.51 --WorldRMax 1.49 \
		--LogX true --LogY true \
		--XLabel "Jet p_{T} (GeV)" --YLabel "dN / d(Jet p_{T})" --Binning None \
		--LegendX 0.45 --LegendY 0.55 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Anti-k_{T} jet R = 0.4",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"Centrality 0-10%" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/TestRunData50to90.root \
		--Systematic Systematics/TestRunData50to90.root \
		--Output Plots/TestRunData50to90Plots.pdf --FinalOutput Plots/TestRunData50to90.pdf \
		--MCFile "Input/TestRunData50to90.root" \
		--MCHistogram "HMCTruth" \
		--MCLabel "MC (normalized to data)" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false \
		--WorldXMin 150 --WorldXMax 1000 --WorldYMin 0.0005 --WorldYMax 500 --WorldRMin 0.51 --WorldRMax 1.49 \
		--LogX true --LogY true \
		--XLabel "Jet p_{T} (GeV)" --YLabel "dN / d(Jet p_{T})" --Binning None \
		--LegendX 0.45 --LegendY 0.55 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Anti-k_{T} jet R = 0.4",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"Centrality 50-90%" \
		--IgnoreGroup 0 --Row 1 --Column 1
		
RunTestRunJetPTClosure: Execute
	./Execute --Input Input/ToyTestRunMC.root \
		--Systematic None \
		--Output Plots/ToyTestRunMCPlots.pdf --FinalOutput Plots/ToyTestRunMC.pdf \
		--MCFile Input/TestRunMC.root,Input/ToyTestRunMC.root \
		--MCHistogram HMCTruth,HInput \
		--MCLabel MC,"Reco" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false \
		--WorldXMin 20 --WorldXMax 1000 --WorldYMin 0.01 --WorldYMax 1000000 --WorldRMin 0.01 --WorldRMax 1.99 \
		--LogX true --LogY true \
		--XLabel "Jet p_{T} (GeV)" --YLabel "dN / d(Jet p_{T})" --Binning None \
		--LegendX 0.65 --LegendY 0.55 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Anti-k_{T} jet R = 0.4",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"Centrality 0-90%" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/ToyTestRunMC0to10.root \
		--Systematic None \
		--Output Plots/ToyTestRunMC0to10Plots.pdf --FinalOutput Plots/ToyTestRunMC0to10.pdf \
		--MCFile Input/TestRunMC0to10.root,Input/ToyTestRunMC0to10.root \
		--MCHistogram HMCTruth,HInput \
		--MCLabel MC,"Reco" \
		--PrimaryName HUnfoldedBayes5 \
		--DoSelfNormalize false \
		--WorldXMin 20 --WorldXMax 1000 --WorldYMin 0.01 --WorldYMax 1000000 --WorldRMin 0.01 --WorldRMax 1.99 \
		--LogX true --LogY true \
		--XLabel "Jet p_{T} (GeV)" --YLabel "dN / d(Jet p_{T})" --Binning None \
		--LegendX 0.65 --LegendY 0.55 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Anti-k_{T} jet R = 0.4",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"Centrality 0-10%" \
		--IgnoreGroup 0 --Row 1 --Column 1
	./Execute --Input Input/ToyTestRunMC50to90.root \
		--Systematic None \
		--Output Plots/ToyTestRunMC50to90Plots.pdf --FinalOutput Plots/ToyTestRunMC50to90.pdf \
		--MCFile Input/TestRunMC50to90.root,Input/ToyTestRunMC50to90.root \
		--MCHistogram HMCTruth,HInput \
		--MCLabel MC,"Reco" \
		--PrimaryName HUnfoldedBayes15 \
		--DoSelfNormalize false \
		--WorldXMin 20 --WorldXMax 1000 --WorldYMin 0.01 --WorldYMax 1000000 --WorldRMin 0.01 --WorldRMax 1.99 \
		--LogX true --LogY true \
		--XLabel "Jet p_{T} (GeV)" --YLabel "dN / d(Jet p_{T})" --Binning None \
		--LegendX 0.65 --LegendY 0.55 --LegendSize 0.04 \
		--XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
		--Texts 0,0.65,0.9,"Anti-k_{T} jet R = 0.4",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"Centrality 50-90%" \
		--IgnoreGroup 0 --Row 1 --Column 1

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute

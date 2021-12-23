


default: RunRAA RunRRAA RunRCP Deploy

Prepare:
	rm -f SpectraRoot CombinedSystematics
	ln -sf $(ProjectBase)/MainAnalysis/23763_BeautifulPlots/Root SpectraRoot
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .
	ln -sf $(ProjectBase)/MainAnalysis/24165_SystematicsCombination/Output/ CombinedSystematics
	mkdir -p Plots Root

Clean:
	rm -f Plots/*pdf Root/*root

RunRAA: Execute
	bash RunFile.sh PPData Nominal PbPbData Nominal

RunRAACheck: RunRAAVariationCheck RunRAARecoCheck

RunRAAVariationCheck: Execute
	bash RunFile.sh PPData Nominal PbPbData JERUp
	bash RunFile.sh PPData Nominal PbPbData JERDown
	bash RunFile.sh PPData Nominal PbPbData FlatJER
	bash RunFile.sh PPData Nominal PbPbData NoJER
	bash RunFile.sh PPData Nominal PbPbData JECUp
	bash RunFile.sh PPData Nominal PbPbData JECDown
	bash RunFile.sh PPData Nominal PbPbData JECQuench
	bash RunFile.sh PPData Nominal PbPbData JECNoResidual
	bash RunFile.sh PPData Nominal PbPbData JECNoPhi
	bash RunFile.sh PPData Nominal PbPbData CentralityUp
	bash RunFile.sh PPData Nominal PbPbData CentralityDown
	bash RunFile.sh PPData Nominal PbPbData MCCentrality
	bash RunFile.sh PPData Nominal PbPbData NominalEarthquake 
	bash RunFile.sh PPData Nominal PbPbData NominalCleaned
	bash RunFile.sh PPData Nominal PbPbData NominalCleanedStrong
	bash RunFile.sh PPData Nominal PbPbData NominalBinBiasUp
	bash RunFile.sh PPData Nominal PbPbData NominalBinBiasDown

RunRAARecoCheck: Execute
	bash RunFile.sh PPData Nominal_Reco PbPbData Nominal_Reco
	bash RunFile.sh PPData Nominal_InputReco PbPbData Nominal_InputReco
	bash RunFile.sh PPData Nominal_InputReco PbPbData JECNoResidual_InputReco
	bash RunFile.sh PPData Nominal_InputReco PbPbData JECNoPhi_InputReco
	bash RunFile.sh PPData Nominal PbPbData Nominal_InputRecoGenBin
	bash RunFile.sh PPData Nominal_InputRecoGenBin PbPbData Nominal_InputRecoGenBin
	bash RunFile.sh PPData Nominal_InputRecoGenBin PbPbData JECNoResidual_InputRecoGenBin
	bash RunFile.sh PPData Nominal_InputRecoGenBin PbPbData JECNoPhi_InputRecoGenBin

RunRCP: Execute
	bash RunRCP.sh PPData Nominal PbPbData Nominal

RunRRAA: Execute
	bash RunRRAA.sh PPData Nominal PbPbData Nominal

Execute: PlotRAA.cpp
	CompileRootMacro PlotRAA.cpp Execute

Deploy:
	mkdir -p $(DeployBase)/Result/RAA
	cp Plots/RAA*_PPNominal_AANominal.pdf $(DeployBase)/Result/RAA/
	mkdir -p $(DeployBase)/Result/RCP
	cp Plots/RCP*_AANominal.pdf $(DeployBase)/Result/RCP/
	mkdir -p $(DeployBase)/Result/RRAA
	cp Plots/RRAA*_PPNominal_AANominal.pdf $(DeployBase)/Result/RRAA/
	mkdir -p $(DeployBase)/Check/RAA/JERVariation
	cp Plots/RAA*_PPNominal_AAJERUp.pdf $(DeployBase)/Check/RAA/JERVariation/
	cp Plots/RAA*_PPNominal_AAJERDown.pdf $(DeployBase)/Check/RAA/JERVariation/
	mkdir -p $(DeployBase)/Check/RAA/JERExtremeCheck
	cp Plots/RAA*_PPNominal_AAFlatJER.pdf $(DeployBase)/Check/RAA/JERExtremeCheck/
	cp Plots/RAA*_PPNominal_AANoJER.pdf $(DeployBase)/Check/RAA/JERExtremeCheck/
	mkdir -p $(DeployBase)/Check/RAA/JECVariation
	cp Plots/RAA*_PPNominal_AAJECUp.pdf $(DeployBase)/Check/RAA/JECVariation/
	cp Plots/RAA*_PPNominal_AAJECDown.pdf $(DeployBase)/Check/RAA/JECVariation/
	cp Plots/RAA*_PPNominal_AAJECQuench.pdf $(DeployBase)/Check/RAA/JECVariation/
	mkdir -p $(DeployBase)/Check/RAA/JECExtremeCheck
	cp Plots/RAA*_PPNominal_AAJECNoPhi.pdf $(DeployBase)/Check/RAA/JECExtremeCheck/
	cp Plots/RAA*_PPNominal_AAJECNoResidual.pdf $(DeployBase)/Check/RAA/JECExtremeCheck/
	mkdir -p $(DeployBase)/Check/RAA/CentralityVariation
	cp Plots/RAA*_PPNominal_AACentralityUp.pdf $(DeployBase)/Check/RAA/CentralityVariation/
	cp Plots/RAA*_PPNominal_AACentralityDown.pdf $(DeployBase)/Check/RAA/CentralityVariation/
	mkdir -p $(DeployBase)/Check/RAA/CentralityFromMC
	cp Plots/RAA*_PPNominal_AAMCCentrality.pdf $(DeployBase)/Check/RAA/CentralityFromMC/
	mkdir -p $(DeployBase)/Check/RAA/Cleaning
	cp Plots/RAA*_PPNominal_AANominalCleaned.pdf $(DeployBase)/Check/RAA/Cleaning/
	cp Plots/RAA*_PPNominal_AANominalCleanedStrong.pdf $(DeployBase)/Check/RAA/Cleaning/
	mkdir -p $(DeployBase)/Check/RAA/BinBias
	cp Plots/RAA*_PPNominal_AANominalBinBiasUp.pdf $(DeployBase)/Check/RAA/BinBias/
	cp Plots/RAA*_PPNominal_AANominalBinBiasDown.pdf $(DeployBase)/Check/RAA/BinBias/
	mkdir -p $(DeployBase)/Check/RAA/Earthquake
	cp Plots/RAA*_PPNominal_AANominalEarthquake.pdf $(DeployBase)/Check/RAA/Earthquake/
	mkdir -p $(DeployBase)/Check/RAA/Refolded
	cp Plots/RAA*_PPNominal_Reco_AANominal_Reco.pdf $(DeployBase)/Check/RAA/Refolded/
	mkdir -p $(DeployBase)/Check/RAA/RecoLevel
	# cp Plots/RAA*_PPNominal_InputReco_AANominal_InputReco.pdf $(DeployBase)/Check/RAA/RecoLevel/
	# cp Plots/RAA*_PPNominal_InputReco_AAJECNoPhi_InputReco.pdf $(DeployBase)/Check/RAA/RecoLevel/
	# cp Plots/RAA*_PPNominal_InputReco_AAJECNoResidual_InputReco.pdf $(DeployBase)/Check/RAA/RecoLevel/
	cp Plots/RAA*_PPNominal_InputRecoGenBin_AANominal_InputRecoGenBin.pdf $(DeployBase)/Check/RAA/RecoLevel/
	cp Plots/RAA*_PPNominal_AANominal_InputRecoGenBin.pdf $(DeployBase)/Check/RAA/RecoLevel/
	cp Plots/RAA*_PPNominal_InputRecoGenBin_AAJECNoPhi_InputRecoGenBin.pdf $(DeployBase)/Check/RAA/RecoLevel/
	cp Plots/RAA*_PPNominal_InputRecoGenBin_AAJECNoResidual_InputRecoGenBin.pdf $(DeployBase)/Check/RAA/RecoLevel/



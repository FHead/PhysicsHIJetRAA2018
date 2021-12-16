


default: RunRAA RunRRAA RunRCP Deploy

Prepare:
	rm -f SpectraRoot CombinedSystematics
	ln -sf ../23763_BeautifulPlots/Root SpectraRoot
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	ln -sf ../24165_SystematicsCombination/Output/ CombinedSystematics
	mkdir -p Plots Root

Clean:
	rm -f Plots/*pdf Root/*root

RunRAA: Execute
	bash RunFile.sh PPData Nominal PbPbData Nominal

RunRAACheck: Execute
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
	mkdir -p $(DeployBase)/Check/RAA/CentralityVariation
	cp Plots/RAA*_PPNominal_AACentralityUp.pdf $(DeployBase)/Check/RAA/CentralityVariation/
	cp Plots/RAA*_PPNominal_AACentralityDown.pdf $(DeployBase)/Check/RAA/CentralityVariation/
	mkdir -p $(DeployBase)/Check/RAA/CentralityFromMC
	cp Plots/RAA*_PPNominal_AAMCCentrality.pdf $(DeployBase)/Check/RAA/CentralityFromMC/



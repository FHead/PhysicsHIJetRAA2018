


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
	mkdir -p $(DeployBase)/Check/RAA
	cp Plots/RAA*_PPNominal_AAJERUp.pdf $(DeployBase)/Check/RAA/
	cp Plots/RAA*_PPNominal_AAJERDown.pdf $(DeployBase)/Check/RAA/
	cp Plots/RAA*_PPNominal_AAFlatJER.pdf $(DeployBase)/Check/RAA/
	cp Plots/RAA*_PPNominal_AANoJER.pdf $(DeployBase)/Check/RAA/
	cp Plots/RAA*_PPNominal_AAJECUp.pdf $(DeployBase)/Check/RAA/
	cp Plots/RAA*_PPNominal_AAJECDown.pdf $(DeployBase)/Check/RAA/
	cp Plots/RAA*_PPNominal_AAJECQuench.pdf $(DeployBase)/Check/RAA/



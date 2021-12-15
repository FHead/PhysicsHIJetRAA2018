


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
	bash RunFile.sh

RunRCP: Execute
	bash RunRCP.sh

RunRRAA: Execute
	bash RunRRAA.sh

Execute: PlotRAA.cpp
	CompileRootMacro PlotRAA.cpp Execute

Deploy:
	mkdir -p $(DeployBase)/Result/RAA
	cp Plots/RAA*pdf $(DeployBase)/Result/RAA/
	mkdir -p $(DeployBase)/Result/RCP
	cp Plots/RCP*pdf $(DeployBase)/Result/RCP/
	mkdir -p $(DeployBase)/Result/RRAA
	cp Plots/RRAA*pdf $(DeployBase)/Result/RRAA/






default: Run

Prepare:
	rm -f SpectraRoot CombinedSystematics
	ln -sf ../23763_BeautifulPlots/Root SpectraRoot
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	ln -sf ../24165_SystematicsCombination/Output/ CombinedSystematics
	mkdir -p Plots

Clean:
	rm -f Plots/*pdf

Run: Execute
	bash RunFile.sh

Execute: PlotRAA.cpp
	CompileRootMacro PlotRAA.cpp Execute

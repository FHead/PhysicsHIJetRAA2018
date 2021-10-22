


default: TestRun

Prepare:
	rm -f SpectraRoot
	ln -sf ../23763_BeautifulPlots/Root SpectraRoot
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	mkdir -p Plots

TestRun: Execute
	bash RunFile.sh

Execute: PlotRAA.cpp
	CompileRootMacro PlotRAA.cpp Execute

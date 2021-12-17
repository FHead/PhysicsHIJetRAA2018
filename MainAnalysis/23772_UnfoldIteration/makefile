
default: TestRun

Prepare:
	rm -f Input
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	mkdir -p Output

Clean:
	rm -f Output/*pdf

SetDefault:
	bash SetInitialPriorChoice.sh

# RunFile.sh parameters
#    Prefix Suffix StateSuffix PriorChoice IsPP

RunMC: Execute
	bash RunFile.sh PbPbMCRho Nominal_Toy Nominal DefaultStep1 0
	bash RunFile.sh PPMC      Nominal_Toy Nominal DefaultStep1 1

RunDataStep1: Execute
	bash RunFile.sh PbPbData  Nominal_DefaultStep1Prior_Toy Nominal DefaultStep1 0
	bash RunFile.sh PPData    Nominal_DefaultStep1Prior_Toy Nominal DefaultStep1 1
	bash SetDataPriorExtra.sh

RunDataStep2: Execute
	bash RunFile.sh PbPbData  Nominal_DefaultStep2Prior_Toy Nominal DefaultStep2 0
	bash RunFile.sh PPData    Nominal_DefaultStep2Prior_Toy Nominal DefaultStep2 1

RunData: Execute
	bash RunFile.sh PbPbData Nominal_Power50Prior_Toy Nominal Nominal 0
	bash RunFile.sh PbPbData Nominal_Power50Prior_Toy Nominal Alternate 0
	bash RunFile.sh PPData Nominal_Power50Prior_Toy Nominal Nominal 1
	bash RunFile.sh PPData Nominal_Power50Prior_Toy Nominal Alternate 1

TestRun: ExecuteLCurve
	./ExecuteLCurve --Input Input/PPData_R4_CentralityInclusive_Nominal_Power50Prior_Toy_Power50Prior.root \
		--Output PPData_R4_CentralityInclusive_Nominal_Power50Prior_Toy_Power50Prior.pdf \
		--Ignore 10 --IgnoreReco 0

Execute: PlotIteration.cpp
	CompileRootMacro PlotIteration.cpp Execute

ExecuteLCurve: PlotLCurve.cpp
	CompileRootMacro PlotLCurve.cpp ExecuteLCurve -I../../CommonCode/include

ExecutePlot: MakeSummaryPlot.cpp
	CompileRootMacro MakeSummaryPlot.cpp ExecutePlot

RunPlot: ExecutePlot
	./ExecutePlot --DHFile GlobalSetting.dh --Output IterationMC.pdf --PPBase PPMC --AABase PbPbMCRho
	./ExecutePlot --DHFile GlobalSetting.dh --Output IterationData.pdf --PPBase PPData --AABase PbPbData

Deploy:
	mkdir -p $(DeployBase)/Check/Iterations/
	cp Iteration*pdf $(DeployBase)/Check/Iterations/




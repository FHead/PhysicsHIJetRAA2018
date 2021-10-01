default: Prepare RunTestRunData RunTestRunDataPlot

Prepare:
	rm -f Input BinMapping OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23762_UnfoldPreparation/Output BinMapping
	mkdir -p Output Plot

RunTestRunData: Execute
	./Execute \
		--BaseInput Input/TestRunData.root,Input/TestRunData.root \
		--Input Input/TestRunDataJECUp.root,Input/TestRunDataJECDown.root \
		--BaseHistogram HUnfoldedBayes30,HUnfoldedBayes30 \
		--Histogram HUnfoldedBayes30,HUnfoldedBayes30 \
		--Label JECUp,JECDown \
		--Group 1,1 \
		--Bridging 0,0 \
		--ExtraScaling 1,1 \
		--BinMapping BinMapping/TestRunData.root \
		--DoSelfNormalize false \
		--Output Output/TestRunData.root
	./Execute \
		--BaseInput Input/TestRunData0to10.root,Input/TestRunData0to10.root \
		--Input Input/TestRunData0to10JECUp.root,Input/TestRunData0to10JECDown.root \
		--BaseHistogram HUnfoldedBayes30,HUnfoldedBayes30 \
		--Histogram HUnfoldedBayes30,HUnfoldedBayes30 \
		--Label JECUp,JECDown \
		--Group 1,1 \
		--Bridging 0,0 \
		--ExtraScaling 1,1 \
		--BinMapping BinMapping/TestRunData0to10.root \
		--DoSelfNormalize false \
		--Output Output/TestRunData0to10.root
	./Execute \
		--BaseInput Input/TestRunData50to90.root,Input/TestRunData50to90.root \
		--Input Input/TestRunData50to90JECUp.root,Input/TestRunData50to90JECDown.root \
		--BaseHistogram HUnfoldedBayes30,HUnfoldedBayes30 \
		--Histogram HUnfoldedBayes30,HUnfoldedBayes30 \
		--Label JECUp,JECDown \
		--Group 1,1 \
		--Bridging 0,0 \
		--ExtraScaling 1,1 \
		--BinMapping BinMapping/TestRunData50to90.root \
		--DoSelfNormalize false \
		--Output Output/TestRunData50to90.root

RunTestRunDataPlot: ExecutePlot
	./ExecutePlot --Input Output/TestRunData.root --Output Plot/TestRunData.pdf \
		--Variations HJECUp,HJECDown \
		--Labels "JEC Up","JEC Down"
		
Execute: Harvest.cpp
	CompileRootMacro Harvest.cpp Execute

ExecutePlot: MakeSystematicSummaryPlot.cpp
	CompileRootMacro MakeSystematicSummaryPlot.cpp ExecutePlot






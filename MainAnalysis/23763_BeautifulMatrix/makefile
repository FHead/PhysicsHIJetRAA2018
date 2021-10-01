default: Prepare TestRun

Prepare:
	rm -f Input
	ln -sf ../23762_ActualUnfold/Output Input
	mkdir -p Plots

Deploy:
	mkdir -p ../FinalResult/SmearingMatrix
	cp Plots/*png ../FinalResult/SmearingMatrix

TestRun: Execute
	./Execute --Input Input/TestRunData.root \
		--Output Plots/TestRunMC.pdf --FinalOutput Plots/MatrixTestRunMC.pdf \
		--WorldXMin 0 --WorldXMax 1000 --WorldYMin 0 --WorldYMax 1000 --WorldZMin 0.0001 --WorldZMax 0.1 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin 0 --GenPrimaryMax 1000 --RecoPrimaryMin 0 --RecoPrimaryMax 1000 \
		--Primary "Jet p_{T} (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX 1 --GroupY 1 --Row 1 --Column 1
	./Execute --Input Input/TestRunData0to10.root \
		--Output Plots/TestRunMC0to10.pdf --FinalOutput Plots/MatrixTestRunMC0to10.pdf \
		--WorldXMin 0 --WorldXMax 1000 --WorldYMin 0 --WorldYMax 1000 --WorldZMin 0.0001 --WorldZMax 0.1 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin 0 --GenPrimaryMax 1000 --RecoPrimaryMin 0 --RecoPrimaryMax 1000 \
		--Primary "Jet p_{T} (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX 1 --GroupY 1 --Row 1 --Column 1
	./Execute --Input Input/TestRunData50to90.root \
		--Output Plots/TestRunMC50to90.pdf --FinalOutput Plots/MatrixTestRunMC50to90.pdf \
		--WorldXMin 0 --WorldXMax 1000 --WorldYMin 0 --WorldYMax 1000 --WorldZMin 0.0001 --WorldZMax 0.1 --LogZ true \
		--UseActualZMax true \
		--GenPrimaryMin 0 --GenPrimaryMax 1000 --RecoPrimaryMin 0 --RecoPrimaryMax 1000 \
		--Primary "Jet p_{T} (GeV)" --Binning "None" --RowNormalize true \
		--XAxis 303 --YAxis 303 \
		--GroupX 1 --GroupY 1 --Row 1 --Column 1

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute



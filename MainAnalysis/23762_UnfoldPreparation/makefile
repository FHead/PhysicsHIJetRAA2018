
GenBins = 5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500
RecoBins = 5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500

default: TestRun

Prepare:
	ln -sf ../23752_CopyJetFromForest/Output Input

Execute: PrepareUnfold.cpp
	CompileRootMacro PrepareUnfold.cpp Execute

TestRun: Execute
	time ./Execute --MC Input/TestRunMC.root --Data Input/TestRunMC.root \
		--Output Output/TestRunMC.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC.root --Data Input/TestRunData.root \
		--Output Output/TestRunData.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC.root --Data Input/TestRunData.root \
		--Output Output/TestRunDataJECUp.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 1.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC.root --Data Input/TestRunData.root \
		--Output Output/TestRunDataJECDown.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift -1.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC0to10.root --Data Input/TestRunMC0to10.root \
		--Output Output/TestRunMC0to10.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC0to10.root --Data Input/TestRunData0to10.root \
		--Output Output/TestRunData0to10.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC0to10.root --Data Input/TestRunData0to10.root \
		--Output Output/TestRunData0to10JECUp.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 1.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC0to10.root --Data Input/TestRunData0to10.root \
		--Output Output/TestRunData0to10JECDown.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift -1.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC50to90.root --Data Input/TestRunMC50to90.root \
		--Output Output/TestRunMC50to90.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC50to90.root --Data Input/TestRunData50to90.root \
		--Output Output/TestRunData50to90.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 0.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC50to90.root --Data Input/TestRunData50to90.root \
		--Output Output/TestRunData50to90JECUp.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift 1.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false
	time ./Execute --MC Input/TestRunMC50to90.root --Data Input/TestRunData50to90.root \
		--Output Output/TestRunData50to90JECDown.root \
		--Observable JetPT --ObservableIndex -1 --Binning None --BinningIndex -1 \
		--ObservableGenBins $(GenBins) \
		--ObservableRecoBins $(RecoBins) \
		--BinningGenBins 0,1 --BinningRecoBins 0,1 \
		--ObservableUncertaintyShift -1.00 \
		--ObservableUncertaintySmear 1.00 \
		--Flooring false




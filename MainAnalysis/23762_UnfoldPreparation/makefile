
GenBins = 5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500
RecoBins = 5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500

default: TestRun

Prepare:
	ln -sf ../23752_CopyJetFromForest/Output Input

Execute: PrepareUnfold.cpp
	CompileRootMacro PrepareUnfold.cpp Execute

ExecutePreset: RunPreset.cpp
	CompileRootMacro RunPreset.cpp ExecutePreset

TestRun: Execute ExecutePreset
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunMC \
		--Prefix TestRunMC --Suffix Nominal \
		--Shift 0.0 --Smear 1.0 --Flooring false | grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix Nominal \
		--Shift 0.0 --Smear 1.0 --Flooring false | grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECUp \
		--Shift 1.0 --Smear 1.0 --Flooring false | grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECDown \
		--Shift -1.0 --Smear 1.0 --Flooring false | grep ^time`




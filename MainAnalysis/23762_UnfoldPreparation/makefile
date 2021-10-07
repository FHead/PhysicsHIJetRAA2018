
default: TestRunPP

Prepare:
	ln -sf ../23752_CopyJetFromForest/Output Input
	ln -sf ../GlobalSetting/GlobalSetting.dh

Execute: PrepareUnfold.cpp
	CompileRootMacro PrepareUnfold.cpp Execute

ExecutePreset: RunPreset.cpp
	CompileRootMacro RunPreset.cpp ExecutePreset

Debug:
	GenBins=`DHQuery GlobalSetting.dh Binning GenPT`; \
	RecoBins=`DHQuery GlobalSetting.dh Binning RecoPT`; \
	echo $$GenBins; \
	DHQuery GlobalSetting.dh Binning GenPT

TestRun: Execute ExecutePreset
	GenBins=`DHQuery GlobalSetting.dh Binning GenPT`; \
	RecoBins=`DHQuery GlobalSetting.dh Binning RecoPT`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunMC \
		--Prefix TestRunMC --Suffix Nominal --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 0.0 --Smear 1.0 --Flooring false | grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix Nominal --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 0.0 --Smear 1.0 --Flooring false | grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECUp --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 1.0 --Smear 1.0 --Flooring false | grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECDown --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift -1.0 --Smear 1.0 --Flooring false | grep ^time`;
	
TestRunPP: Execute ExecutePreset
	GenBins=`DHQuery GlobalSetting.dh Binning GenPT`; \
	RecoBins=`DHQuery GlobalSetting.dh Binning RecoPT`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPMC \
		--Prefix TestRunPPMC --Suffix Nominal --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 0.0 --Smear 1.0 --Flooring false | grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix Nominal --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins  \
		--Shift 0.0 --Smear 1.0 --Flooring false | grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix JECUp --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins  \
		--Shift 1.0 --Smear 1.0 --Flooring false | grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix JECDown --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins  \
		--Shift -1.0 --Smear 1.0 --Flooring false | grep ^time`;




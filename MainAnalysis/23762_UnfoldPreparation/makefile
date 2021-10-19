
MCFraction = 0.1
DataFraction = 1.0

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
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunMC \
		--Prefix TestRunMC --Suffix Nominal --GlobalSetting GlobalSetting.dh \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(MCFraction) \
		| grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix Nominal --GlobalSetting GlobalSetting.dh \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECUp --GlobalSetting GlobalSetting.dh \
		--Shift 1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECDown --GlobalSetting GlobalSetting.dh \
		--Shift -1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`

TestRunExternal: Execute ExecutePreset
	GenBins=`DHQuery GlobalSetting.dh Binning GenPT`; \
	RecoBins=`DHQuery GlobalSetting.dh Binning RecoPT`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunMC \
		--Prefix TestRunMC --Suffix Nominal --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(MCFraction) \
		| grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix Nominal --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECUp --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunMC --DataTag Input/TestRunData \
		--Prefix TestRunData --Suffix JECDown --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift -1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`;
	
TestRunPP: Execute ExecutePreset
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPMC \
		--Prefix TestRunPPMC --Suffix Nominal --Centrality "Inclusive" --GlobalSetting GlobalSetting.dh \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(MCFraction) \
		| grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix Nominal --Centrality "Inclusive" --GlobalSetting GlobalSetting.dh \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix JECUp --Centrality "Inclusive" --GlobalSetting GlobalSetting.dh \
		--Shift 1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix JECDown --Centrality "Inclusive" --GlobalSetting GlobalSetting.dh  \
		--Shift -1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`

DebugRun: Execute ExecutePreset
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPMC \
		--Prefix TestRunPPMC --Suffix Nominal --Centrality "Inclusive" --GlobalSetting GlobalSetting.dh \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(MCFraction) \
		--JetR 1,2 \
		| grep ^time`
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix Nominal --Centrality "Inclusive" --GlobalSetting GlobalSetting.dh \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		--JetR 1,2 \
		| grep ^time`

TestRunPPExternal: Execute ExecutePreset
	GenBins=`DHQuery GlobalSetting.dh Binning GenPT`; \
	RecoBins=`DHQuery GlobalSetting.dh Binning RecoPT`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPMC \
		--Prefix TestRunPPMC --Suffix Nominal --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(MCFraction) \
		| grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix Nominal --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins  \
		--Shift 0.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix JECUp --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins  \
		--Shift 1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`; \
	eval `./ExecutePreset --MCTag Input/TestRunPPMC --DataTag Input/TestRunPPData \
		--Prefix TestRunPPData --Suffix JECDown --Centrality "Inclusive" --GenBins $$GenBins --RecoBins $$RecoBins  \
		--Shift -1.0 --Smear 1.0 --Flooring false --MCFraction $(MCFraction) --DataFraction $(DataFraction) \
		| grep ^time`;




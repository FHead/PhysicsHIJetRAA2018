default: RunJetPT

Prepare:
	rm -f OriginalInput Input Systematics HEPData CombinedSystematics
	ln -sf ../23762_UnfoldPreparation/Output OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23763_Systematics/Output Systematics
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ../24114_PPRatioHEPData/ HEPData
	ln -sf ../24165_SystematicsCombination/Output/ CombinedSystematics
	mkdir -p Plots

RunJetPT: Execute
	./Execute --Output Base1.2.pdf \
		--BaseFileName Input/PPData_R9_CentralityInclusive_Nominal.root \
		--BaseRLabel 9 \
		--FileName Input/PPData_R1_CentralityInclusive_Nominal.root,Input/PPData_R2_CentralityInclusive_Nominal.root,Input/PPData_R3_CentralityInclusive_Nominal.root,Input/PPData_R4_CentralityInclusive_Nominal.root,Input/PPData_R5_CentralityInclusive_Nominal.root,Input/PPData_R6_CentralityInclusive_Nominal.root,Input/PPData_R7_CentralityInclusive_Nominal.root,Input/PPData_R8_CentralityInclusive_Nominal.root \
		--Systematics CombinedSystematics/PPDataRatio_R1R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R2R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R3R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R4R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R5R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R6R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R7R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R8R9_CentralityInclusive.root \
		--RLabel 1,2,3,4,5,6,7,8 \
		--Color 0,1,2,3,4,5,6,7 \
		--XMin 199 --XMax 1200
	./Execute --Output Base1.0.pdf \
		--BaseFileName Input/PPData_R8_CentralityInclusive_Nominal.root \
		--BaseRLabel 8 \
		--FileName Input/PPData_R3_CentralityInclusive_Nominal.root,Input/PPData_R4_CentralityInclusive_Nominal.root,Input/PPData_R5_CentralityInclusive_Nominal.root,Input/PPData_R6_CentralityInclusive_Nominal.root,Input/PPData_R7_CentralityInclusive_Nominal.root \
		--Systematics CombinedSystematics/PPDataRatio_R3R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R4R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R5R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R6R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R7R9_CentralityInclusive.root \
		--RLabel 3,4,5,6,7 \
		--Color 1,2,5,3,4 \
		--XMin 199 --XMax 1200
	./Execute --Output Validation.pdf \
		--BaseFileName Input/PPData_R8_CentralityInclusive_Nominal.root \
		--BaseRLabel 8 \
		--FileName Input/PPData_R2_CentralityInclusive_Nominal.root,Input/PPData_R3_CentralityInclusive_Nominal.root,Input/PPData_R4_CentralityInclusive_Nominal.root,Input/PPData_R6_CentralityInclusive_Nominal.root,Input/PPData_R7_CentralityInclusive_Nominal.root \
		--Systematics CombinedSystematics/PPDataRatio_R2R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R3R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R4R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R6R9_CentralityInclusive.root,CombinedSystematics/PPDataRatio_R7R9_CentralityInclusive.root \
		--RLabel 2,3,4,6,7 \
		--Color 0,1,2,3,4 \
		--XMin 199 --XMax 1000 \
		--AddHIN18014 true

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute

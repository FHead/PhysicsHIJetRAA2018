default: RunTestRunJetPT

Prepare:
	rm -f OriginalInput Input Systematics HEPData
	ln -sf ../23762_UnfoldPreparation/Output OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23763_Systematics/Output Systematics
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ../24114_PPRatioHEPData/ HEPData
	mkdir -p Plots

RunTestRunJetPT: Execute
	./Execute --Output Base1.2.pdf \
		--BaseFileName Input/TestRunPPData_R9_CentralityInclusive_Nominal.root \
		--BaseRLabel 9 \
		--FileName Input/TestRunPPData_R3_CentralityInclusive_Nominal.root,Input/TestRunPPData_R4_CentralityInclusive_Nominal.root,Input/TestRunPPData_R5_CentralityInclusive_Nominal.root,Input/TestRunPPData_R6_CentralityInclusive_Nominal.root,Input/TestRunPPData_R7_CentralityInclusive_Nominal.root,Input/TestRunPPData_R8_CentralityInclusive_Nominal.root \
		--RLabel 3,4,5,6,7,8 \
		--Color 0,1,2,3,4,5,6 \
		--XMin 141 --XMax 1000
	./Execute --Output Base1.0.pdf \
		--BaseFileName Input/TestRunPPData_R8_CentralityInclusive_Nominal.root \
		--BaseRLabel 8 \
		--FileName Input/TestRunPPData_R3_CentralityInclusive_Nominal.root,Input/TestRunPPData_R4_CentralityInclusive_Nominal.root,Input/TestRunPPData_R5_CentralityInclusive_Nominal.root,Input/TestRunPPData_R6_CentralityInclusive_Nominal.root,Input/TestRunPPData_R7_CentralityInclusive_Nominal.root \
		--RLabel 3,4,5,6,7 \
		--Color 1,2,5,3,4 \
		--XMin 141 --XMax 1000
	./Execute --Output Validation.pdf \
		--BaseFileName Input/TestRunPPData_R8_CentralityInclusive_Nominal.root \
		--BaseRLabel 8 \
		--FileName Input/TestRunPPData_R2_CentralityInclusive_Nominal.root,Input/TestRunPPData_R3_CentralityInclusive_Nominal.root,Input/TestRunPPData_R4_CentralityInclusive_Nominal.root,Input/TestRunPPData_R6_CentralityInclusive_Nominal.root,Input/TestRunPPData_R7_CentralityInclusive_Nominal.root \
		--RLabel 2,3,4,6,7 \
		--Color 0,1,2,3,4 \
		--XMin 199 --XMax 1000 \
		--AddHIN18014 true

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute

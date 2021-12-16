default: RunJetPT RunJetPTClosure

Prepare:
	rm -f OriginalInput Input Systematics HEPData
	ln -sf ../23762_UnfoldPreparation/Output OriginalInput
	ln -sf ../23762_ActualUnfold/Output Input
	ln -sf ../23763_Systematics/Output Systematics
	ln -sf ../GlobalSetting/GlobalSetting.dh
	ln -sf ../24113_HEPData/ HEPData
	mkdir -p Plots Root

Clean:
	rm -f Plots/*pdf
	rm -f Root/*root

RunJetPT: Execute
	bash RunFile.sh PbPbData Nominal "" 0
	bash RunFile.sh PPData   Nominal "" 1

RunCheck: Execute
	bash RunFile.sh PbPbData JERUp          "" 0
	bash RunFile.sh PbPbData JERDown        "" 0
	bash RunFile.sh PbPbData FlatJER        "" 0
	bash RunFile.sh PbPbData NoJER          "" 0
	bash RunFile.sh PbPbData JECUp          "" 0
	bash RunFile.sh PbPbData JECDown        "" 0
	bash RunFile.sh PbPbData JECQuench      "" 0
	bash RunFile.sh PbPbData JECNoResidual  "" 0
	bash RunFile.sh PbPbData JECNoPhi       "" 0
	bash RunFile.sh PbPbData CentralityUp   "" 0
	bash RunFile.sh PbPbData CentralityDown "" 0
	bash RunFile.sh PbPbData MCCentrality   "" 0

RunJetPTClosure: Execute
	bash RunFile.sh PbPbMCRho Nominal Toy 0
	bash RunFile.sh PPMC      Nominal Toy 1

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute

Deploy:
	mkdir -p $(DeployBase)/Result/Spectra/
	cp Plots/PbPbData*Nominal.pdf $(DeployBase)/Result/Spectra
	cp Plots/PPData*Nominal.pdf $(DeployBase)/Result/Spectra


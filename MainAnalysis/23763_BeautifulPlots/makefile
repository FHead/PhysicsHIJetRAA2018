default: RunJetPT RunJetPTClosure

Prepare:
	rm -f OriginalInput Input Systematics HEPData
	ln -sf $(ProjectBase)/MainAnalysis/24236_RebinUnfoldInput//Output OriginalInput
	ln -sf $(ProjectBase)/MainAnalysis/23762_ActualUnfold/Output Input
	ln -sf $(ProjectBase)/MainAnalysis/23763_Systematics/Output Systematics
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh
	ln -sf $(ProjectBase)/MainAnalysis/24113_HEPData/ HEPData
	mkdir -p Plots Root

Clean:
	rm -f Plots/*pdf
	rm -f Root/*root

RunJetPT: Execute
	bash RunFile.sh PbPbData Nominal "" 0 Gen
	bash RunFile.sh PPData   Nominal "" 1 Gen

RunJetPTReco: Execute
	bash RunFile.sh PbPbData  Nominal ""  0 Reco
	bash RunFile.sh PPData    Nominal ""  1 Reco
	bash RunFile.sh PbPbMCRho Nominal Toy 0 Reco
	bash RunFile.sh PPMC      Nominal Toy 1 Reco
	bash RunFile.sh PbPbData  Nominal ""  0 InputReco
	bash RunFile.sh PPData    Nominal ""  1 InputReco
	bash RunFile.sh PbPbMCRho Nominal Toy 0 InputReco
	bash RunFile.sh PPMC      Nominal Toy 1 InputReco
	bash RunFile.sh PbPbData  Nominal ""  0 InputRecoGenBin
	bash RunFile.sh PPData    Nominal ""  1 InputRecoGenBin
	bash RunFile.sh PbPbMCRho Nominal Toy 0 InputRecoGenBin
	bash RunFile.sh PPMC      Nominal Toy 1 InputRecoGenBin

RunCheck: Execute
	bash RunFile.sh PbPbData JERUp              "" 0 Gen
	bash RunFile.sh PbPbData JERDown            "" 0 Gen
	bash RunFile.sh PbPbData FlatJER            "" 0 Gen
	bash RunFile.sh PbPbData NoJER              "" 0 Gen
	bash RunFile.sh PbPbData JECUp              "" 0 Gen
	bash RunFile.sh PbPbData JECDown            "" 0 Gen
	bash RunFile.sh PbPbData JECQuench          "" 0 Gen
	bash RunFile.sh PbPbData JECNoResidual      "" 0 Gen
	bash RunFile.sh PbPbData JECNoPhi           "" 0 Gen
	bash RunFile.sh PbPbData CentralityUp       "" 0 Gen
	bash RunFile.sh PbPbData CentralityDown     "" 0 Gen
	bash RunFile.sh PbPbData MCCentrality       "" 0 Gen
	bash RunFile.sh PbPbData NominalEarthquake  "" 0 Gen
	bash RunFile.sh PbPbData NominalBinBiasUp   "" 0 Gen
	bash RunFile.sh PbPbData NominalBinBiasDown "" 0 Gen
	bash RunFile.sh PbPbData NominalCleaned     "" 0 Gen
	bash RunFile.sh PbPbData NominalCleanedStrong "" 0 Gen
	bash RunFile.sh PbPbData JECNoResidual      "" 0 InputReco
	bash RunFile.sh PbPbData JECNoPhi           "" 0 InputReco
	bash RunFile.sh PbPbData JECNoResidual      "" 0 InputRecoGenBin
	bash RunFile.sh PbPbData JECNoPhi           "" 0 InputRecoGenBin

RunJetPTClosure: Execute
	bash RunFile.sh PbPbMCRho Nominal Toy 0 Gen
	bash RunFile.sh PPMC      Nominal Toy 1 Gen

Execute: MakePaperPlot.cpp
	CompileRootMacro MakePaperPlot.cpp Execute

Deploy:
	mkdir -p $(DeployBase)/Result/Spectra/
	cp Plots/PbPbData*Nominal.pdf $(DeployBase)/Result/Spectra/
	cp Plots/PPData*Nominal.pdf $(DeployBase)/Result/Spectra/
	mkdir -p $(DeployBase)/Check/RefoldCheck/
	cp Plots/PbPbData*Nominal_Reco.pdf $(DeployBase)/Check/RefoldCheck/
	cp Plots/PPData*Nominal_Reco.pdf $(DeployBase)/Check/RefoldCheck/
	mkdir -p $(DeployBase)/Check/ToyRefoldCheck/
	cp Plots/PbPbMCRho*Toy_Reco.pdf $(DeployBase)/Check/ToyRefoldCheck/
	cp Plots/PPMC*Toy_Reco.pdf $(DeployBase)/Check/ToyRefoldCheck/
	mkdir -p $(DeployBase)/Check/Spectra/MatrixCheck
	cp Plots/PbPbData*NominalEarthquake.pdf  $(DeployBase)/Check/Spectra/MatrixCheck/
	cp Plots/PbPbData*NominalBinBiasUp.pdf   $(DeployBase)/Check/Spectra/MatrixCheck/
	cp Plots/PbPbData*NominalBinBiasDown.pdf $(DeployBase)/Check/Spectra/MatrixCheck/
	cp Plots/PbPbData*NominalCleaned.pdf     $(DeployBase)/Check/Spectra/MatrixCheck/


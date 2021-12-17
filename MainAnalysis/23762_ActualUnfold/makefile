
default: RunTest

Prepare:
	rm -f Input ToyInput
	ln -sf ../23762_UnfoldPreparation/Output/ Input
	ln -sf ../23762_FakeData/Output/ ToyInput
	ln -sf ../GlobalSetting/GlobalSetting.dh
	mkdir -p Output Plots

Clean:
	rm -f Output/*root
	rm -f Plots/*pdf

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute -lUnfold

ExecutePlot: Visualize.cpp
	CompileRootMacro Visualize.cpp ExecutePlot

RunAA: Execute ExecutePlot
	bash RunFile.sh Input    PbPbMCRho Nominal        0 Nominal
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy    0 Nominal
	bash RunFile.sh Input    PbPbData  Nominal        0 Nominal
	bash RunFile.sh Input    PbPbData  Nominal        0 Alternate
	bash RunFile.sh Input    PbPbData  JECUp          0 Nominal
	bash RunFile.sh Input    PbPbData  JECDown        0 Nominal
	bash RunFile.sh Input    PbPbData  JECQuench      0 Nominal
	bash RunFile.sh Input    PbPbData  JERUp          0 Nominal
	bash RunFile.sh Input    PbPbData  JERDown        0 Nominal
	bash RunFile.sh Input    PbPbData  FlatJER        0 Nominal
	bash RunFile.sh Input    PbPbData  NoJER          0 Nominal
	bash RunFile.sh Input    PbPbData  CentralityUp   0 Nominal
	bash RunFile.sh Input    PbPbData  CentralityDown 0 Nominal
	bash RunFile.sh Input    PbPbData  MCCentrality   0 Nominal
	bash RunFile.sh Input    PbPbData  JECNoResidual  0 Nominal
	bash RunFile.sh Input    PbPbData  JECNoPhi       0 Nominal
	
RunPP: Execute ExecutePlot
	bash RunFile.sh Input    PPMC      Nominal     1 Nominal
	bash RunFile.sh ToyInput PPMC      Nominal_Toy 1 Nominal
	bash RunFile.sh Input    PPData    Nominal     1 Nominal
	bash RunFile.sh Input    PPData    Nominal     1 Alternate
	bash RunFile.sh Input    PPData    JECUp       1 Nominal
	bash RunFile.sh Input    PPData    JECDown     1 Nominal
	bash RunFile.sh Input    PPData    JERUp       1 Nominal
	bash RunFile.sh Input    PPData    JERDown     1 Nominal

RunDataToy: Execute ExecutePlot
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 Nominal
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 Alternate
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 Nominal
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 Alternate

RunAAMCToyChoice: Execute ExecutePlot
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 ExternalMC
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Power40
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Power50
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Power60
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Flat
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Original

RunPPMCToyChoice: Execute ExecutePlot
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 ExternalMC
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Power40
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Power50
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Power60
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Flat
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Original

RunAADataToyChoice: Execute ExecutePlot
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 ExternalMC
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 Power40
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 Power50
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 Power60
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 Flat
	bash RunFile.sh ToyInput PbPbData  Nominal_Power50Prior_Toy 0 Original

RunPPDataToyChoice: Execute ExecutePlot
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 ExternalMC
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 Power40
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 Power50
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 Power60
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 Flat
	bash RunFile.sh ToyInput PPData    Nominal_Power50Prior_Toy 1 Original

RunTest: Execute ExecutePlot
	# ./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestMCPrior.root \
	# 	--Prior ExternalMC --ExternalPriorFile Input/PPMC_R4_CentralityInclusive_Nominal.root
	# ./ExecutePlot --Input TestMCPrior.root --Output TestMCPrior.pdf --Ignore 14
	# ./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestOriginalPrior.root \
	# 	--Prior Original
	# ./ExecutePlot --Input TestOriginalPrior.root --Output TestOriginalPrior.pdf --Ignore 14
	./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestPower5Prior.root \
		--Prior Power --PriorK -5 --DoBayes true --DoSVD false --DoInvert false --DoTUnfold true
	# ./ExecutePlot --Input TestPower5Prior.root --Output TestPower5Prior.pdf --Ignore 14
	# ./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestPower6Prior.root \
	# 	--Prior Power --PriorK -6
	# ./ExecutePlot --Input TestPower6Prior.root --Output TestPower6Prior.pdf --Ignore 14
	# ./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestPower7Prior.root \
	# 	--Prior Power --PriorK -7 --DoFoldNormalize true --Ignore 14
	# ./ExecutePlot --Input TestPower7Prior.root --Output TestPower7Prior.pdf --Ignore 14
	# ./Execute --Input Input/PPData_R4_CentralityInclusive_Nominal.root --Output Meow.root \
	# 	--Prior Flat
	# ./ExecutePlot --Input Meow.root --Output Meow.pdf --Ignore 10



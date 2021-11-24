
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
	CompileRootMacro Unfold1D.cpp Execute

ExecutePlot: Visualize.cpp
	CompileRootMacro Visualize.cpp ExecutePlot

RunAA: Execute ExecutePlot
	bash RunFile.sh Input    PbPbMCRho Nominal     0 MC
	bash RunFile.sh Input    PbPbMCRho Nominal     0 Flat
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 ExternalMC
	bash RunFile.sh Input    PbPbData  Nominal     0 MC
	bash RunFile.sh Input    PbPbData  Nominal     0 Flat
	bash RunFile.sh Input    PbPbData  JECUp       0 MC
	bash RunFile.sh Input    PbPbData  JECDown     0 MC
	bash RunFile.sh Input    PbPbData  JERUp       0 MC
	bash RunFile.sh Input    PbPbData  JERDown     0 MC
	
RunPP: Execute ExecutePlot
	bash RunFile.sh Input    PPMC      Nominal     1 MC
	bash RunFile.sh Input    PPMC      Nominal     1 Flat
	bash RunFile.sh ToyInput PPMC      Nominal_Toy 1 ExternalMC
	bash RunFile.sh Input    PPData    Nominal     1 MC
	bash RunFile.sh Input    PPData    Nominal     1 Flat
	bash RunFile.sh Input    PPData    JECUp       1 MC
	bash RunFile.sh Input    PPData    JECDown     1 MC
	bash RunFile.sh Input    PPData    JERUp       1 MC
	bash RunFile.sh Input    PPData    JERDown     1 MC

RunDataToy: Execute ExecutePlot
	bash RunFile.sh ToyInput PbPbData  Nominal_Toy 0 Power50
	bash RunFile.sh ToyInput PPData    Nominal_Toy 1 Power50

RunMCToyChoice: Execute ExecutePlot
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 ExternalMC
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Power40
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Power50
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Power60
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Flat
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0 Original
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 ExternalMC
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Power40
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Power50
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Power60
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Flat
	bash RunFile.sh ToyInput PPMC    Nominal_Toy 1 Original

RunDataToyChoice: Execute ExecutePlot
	# bash RunFile.sh ToyInput PbPbData  Nominal_Toy 0 ExternalMC
	# bash RunFile.sh ToyInput PbPbData  Nominal_Toy 0 Power40
	# bash RunFile.sh ToyInput PbPbData  Nominal_Toy 0 Power50
	# bash RunFile.sh ToyInput PbPbData  Nominal_Toy 0 Power60
	bash RunFile.sh ToyInput PbPbData  Nominal_Toy 0 Flat
	bash RunFile.sh ToyInput PbPbData  Nominal_Toy 0 Original
	# bash RunFile.sh ToyInput PPData    Nominal_Toy 1 ExternalMC
	# bash RunFile.sh ToyInput PPData    Nominal_Toy 1 Power40
	# bash RunFile.sh ToyInput PPData    Nominal_Toy 1 Power50
	# bash RunFile.sh ToyInput PPData    Nominal_Toy 1 Power60
	bash RunFile.sh ToyInput PPData    Nominal_Toy 1 Flat
	bash RunFile.sh ToyInput PPData    Nominal_Toy 1 Original

RunTest: Execute ExecutePlot
	./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestMCPrior.root \
		--Prior ExternalMC --ExternalPriorFile Input/PPMC_R4_CentralityInclusive_Nominal.root
	./ExecutePlot --Input TestMCPrior.root --Output TestMCPrior.pdf --Ignore 14
	./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestOriginalPrior.root \
		--Prior Original
	./ExecutePlot --Input TestOriginalPrior.root --Output TestOriginalPrior.pdf --Ignore 14
	./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestPower5Prior.root \
		--Prior Power --PriorK -5
	./ExecutePlot --Input TestPower5Prior.root --Output TestPower5Prior.pdf --Ignore 14
	./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestPower6Prior.root \
		--Prior Power --PriorK -6
	./ExecutePlot --Input TestPower6Prior.root --Output TestPower6Prior.pdf --Ignore 14
	./Execute --Input ToyInput/PPMC_R4_CentralityInclusive_Nominal_Toy.root --Output TestPower7Prior.root \
		--Prior Power --PriorK -7
	./ExecutePlot --Input TestPower7Prior.root --Output TestPower7Prior.pdf --Ignore 14



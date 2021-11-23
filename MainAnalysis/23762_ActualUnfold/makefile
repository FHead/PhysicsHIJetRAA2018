
default: RunAA RunPP

Prepare:
	rm -f Input ToyInput
	ln -sf ../23762_UnfoldPreparation/Output/ Input
	ln -sf ../23762_FakeData/Output/ ToyInput
	ln -sf ../GlobalSetting/GlobalSetting.dh

Execute: Unfold1D.cpp
	CompileRootMacro Unfold1D.cpp Execute

RunAA: Execute
	bash RunFile.sh Input PbPbMCRho Nominal 0
	bash RunFile.sh ToyInput PbPbMCRho Nominal_Toy 0
	bash RunFile.sh Input PbPbData Nominal 0
	bash RunFile.sh Input PbPbData JECUp 0
	bash RunFile.sh Input PbPbData JECDown 0
	bash RunFile.sh Input PbPbData JERUp 0
	bash RunFile.sh Input PbPbData JERDown 0
	
RunPP: Execute
	bash RunFile.sh Input PPMC Nominal 1
	bash RunFile.sh ToyInput PPMC Nominal_Toy 1
	bash RunFile.sh Input PPData Nominal 1
	bash RunFile.sh Input PPData JECUp 1
	bash RunFile.sh Input PPData JECDown 1
	bash RunFile.sh Input PPData JERUp 1
	bash RunFile.sh Input PPData JERDown 1

RunDataToy: Execute
	bash RunFile.sh ToyInput PbPbData Nominal_Toy 0
	bash RunFile.sh ToyInput PPData Nominal_Toy 1





default: TestRun

Prepare:
	rm -f Input Root
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output/ Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .
	mkdir -p ~/EOSHI/PhysicsWorkspace/HIJetRAA2018/JetEnergyCorrection/24242_PhiResidualCorrection
	ln -sf ~/EOSHI/PhysicsWorkspace/HIJetRAA2018/JetEnergyCorrection/24242_PhiResidualCorrection Root
	mkdir -p Txt Pdf

TestRun: Execute
	./Execute --Input `ls Input/TestRunPbPbMCPart*_R4_* | head -n10000 | tr '\n' ','` --Output Meow_R4.pdf \
		--Eta -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0 --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
		--NPT 8 --NRho 8 --NPhi 100 --JetR 0.4 \
		--Correction PhiCorrection_AK4PF.txt --BinnedCorrection true

Execute: ProcessJets.cpp
	CompileRootMacro ProcessJets.cpp Execute

ExecuteJEC: DeriveResidual.cpp
	CompileRootMacro DeriveResidual.cpp ExecuteJEC

ExecuteText: CreateTextFile.cpp
	CompileRootMacro CreateTextFile.cpp ExecuteText

ExecutePlot: CheckJets.cpp
	CompileRootMacro CheckJets.cpp ExecutePlot -I$(ProjectBase)/CommonCode/include

RunProduction: Execute
	bash ProcessAll.sh

RunDerivation: ExecuteJEC
	bash RunAll.sh

RunText: ExecuteText
	bash TextAll.sh

RunClosure: ExecutePlot
	bash PlotAll.sh



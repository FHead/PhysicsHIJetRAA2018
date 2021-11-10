

default: TestRun

Prepare:
	rm -f Input
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output/ Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .

TestRun: Execute
	./Execute --Input `ls Input/TestRunPbPbMCPart*_R4_* | head -n10000 | tr '\n' ','` --Output Meow_R4.pdf \
		--Eta -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0 --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
		--NPT 8 --NRho 8 --NPhi 100 --JetR 0.4 \
		--Correction PhiCorrection_AK4PF.txt --BinnedCorrection true

Execute: DeriveResidual.cpp
	CompileRootMacro DeriveResidual.cpp Execute

Production: Execute RunAll.sh
	bash RunAll.sh

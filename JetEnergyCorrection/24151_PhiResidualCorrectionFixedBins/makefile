

default: TestRun

Prepare:
	rm -f Input
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output/ Input

TestRun: Execute
	./Execute --Input `ls Input/TestRunPbPbMCPart*_R4_* | tr '\n' ','` --Output Meow_R4.pdf \
		--Eta -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0 --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
		--PT 50,100,200,300,500,750,1000 \
		--Rho 0,25,50,75,100,125,150,175,200,250 \
		--NPhi 100 \
		--JetR 0.4

Execute: DeriveResidual.cpp
	CompileRootMacro DeriveResidual.cpp Execute


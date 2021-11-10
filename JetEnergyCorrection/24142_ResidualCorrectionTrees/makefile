
FastJet = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

Fraction = 1.00

default: TestRun

Prepare:
	echo $(ProjectBase)
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .
	# ln -sf $(ProjectBase)/Samples/Example SampleExample
	# mkdir -p Output/
	ln -sf /afs/cern.ch/user/c/chenyi/EOSHI/PhysicsWorkspace/HIJetRAA2018/JetEnergyCorrection/24142_ResidualCorrectionTrees/ Output

TestRun: Execute
	# arguments = file tag trigger MC? PP? Recluster?
	bash RunFile.sh ExamplePbPbInput/OutputMerged.root Tree None 1 0 0

Execute: ProcessJets.cpp
	CompileRootMacro ProcessJets.cpp Execute \
		-I$(ProjectBase)/CommonCode/include \
		$(ProjectBase)/CommonCode/library/*.o \
		`$(FastJet) --cxxflags --libs` \
		-L$(FJContrib)/lib -I$(FJContrib)/include -lConstituentSubtractor




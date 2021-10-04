
FastJet = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

Fraction = 1.00

default: TestRun

Prepare:
	echo $(ProjectBase)
	# ln -sf $(ProjectBase)/Samples/Example SampleExample
	# mkdir -p Output/

TestRun: Execute
	bash RunFile.sh Samples/HiForestMiniAOD_MC.root TestRunMC None 0
	bash RunFile.sh Samples/HiForestMiniAOD_Data.root TestRunData HLT_HIPuAK4CaloJet100Eta5p1 0

Execute: ProcessJets.cpp
	CompileRootMacro ProcessJets.cpp Execute \
		-I$(ProjectBase)/CommonCode/include \
		$(ProjectBase)/CommonCode/library/*.o \
		`$(FastJet) --cxxflags --libs` \
		-L$(FJContrib)/lib -I$(FJContrib)/include -lConstituentSubtractor




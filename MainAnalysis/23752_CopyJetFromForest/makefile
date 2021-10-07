
FastJet = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

Fraction = 1.00

default: TestRun

Prepare:
	echo $(ProjectBase)
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	# ln -sf $(ProjectBase)/Samples/Example SampleExample
	# mkdir -p Output/

TestRun: Execute
	# arguments = file tag trigger MC? PP? Recluster?
	bash RunFile.sh ExamplePbPbMC/OutputAll.root TestRunMC None 1 0 0
	bash RunFile.sh ExamplePbPbData/OutputAll.root TestRunData HLT_HIPuAK4CaloJet100Eta5p1 0 0 0
	# bash RunFile.sh `ls PPMC/*.root | head -n3 | tr '\n' ','`   TestRunPPMC   None             1 1 1
	# bash RunFile.sh `ls PPData/*.root | head -n3 | tr '\n' ','` TestRunPPData HLT_HIAK4PFJet80 0 1 1

Execute: ProcessJets.cpp
	CompileRootMacro ProcessJets.cpp Execute \
		-I$(ProjectBase)/CommonCode/include \
		$(ProjectBase)/CommonCode/library/*.o \
		`$(FastJet) --cxxflags --libs` \
		-L$(FJContrib)/lib -I$(FJContrib)/include -lConstituentSubtractor




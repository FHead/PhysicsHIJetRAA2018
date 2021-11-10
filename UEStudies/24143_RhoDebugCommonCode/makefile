FastJetConfig = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

default: TestRun

TestRun: Execute
	./Execute --input HiForestMiniAOD.root

Execute: RunRhoReproduction.cpp
	rm -f Execute
	CompileRootMacro RunRhoReproduction.cpp Execute \
		-I../../CommonCode/include ../../CommonCode/library/*.o \
		`$(FastJetConfig) --cxxflags --libs` -I$(FJContrib)/include \
		-L$(FJContrib)/lib -lConstituentSubtractor -g


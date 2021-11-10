FastJetConfig = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

default: Run

RunCMSSW:
	cmsRun runForestAOD_pponAA_MIX_103X.py

Run: Execute
	./Execute --input HiForestMiniAOD.root --R 0.3 | tee Meow1
	./Execute --input HiForestMiniAOD2.root --R 0.3 | tee Meow2

Execute: DoJetSubtraction.cpp
	CompileRootMacro DoJetSubtraction.cpp Execute \
		-I../../CommonCode/include -I../../CommonCode ../../CommonCode/library/* \
		`$(FastJetConfig) --cxxflags --libs` -L$(FJContrib)/lib -I$(FJContrib)/include -lConstituentSubtractor



FastJet = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

Fraction = 1.00

default: TestRun

Prepare:
	echo $(ProjectBase)
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	# mkdir -p Output/

TestRun: Execute
	time ./Execute --Data ExamplePbPbData/OutputAll.root --MC ExamplePbPbMC/OutputAll.root \
		--Output Result.root

Execute: DeriveWeight.cpp
	CompileRootMacro DeriveWeight.cpp Execute \
		-I$(ProjectBase)/CommonCode/include \
		$(ProjectBase)/CommonCode/library/*.o \
		`$(FastJet) --cxxflags --libs` \
		-L$(FJContrib)/lib -I$(FJContrib)/include -lConstituentSubtractor




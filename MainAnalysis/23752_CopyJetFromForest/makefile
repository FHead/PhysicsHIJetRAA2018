
FastJet = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

Fraction = 1.00

default: TestRun

Prepare:
	echo $(ProjectBase)
	ln -sf ../GlobalSetting/GlobalSetting.dh .
	# ln -sf $(ProjectBase)/Samples/Example SampleExample
	# mkdir -p Output/

PbPbData4=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest//HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/0000/

TestRun: Execute
	# arguments = file tag trigger MC? PP? Recluster?
	# bash RunFile.sh `ls ExamplePbPbMC/Output*.root | head -n10 | tr '\n' ','` MeowTestRunMC None 1 0 0
	# bash RunFile.sh ExamplePbPbData/OutputAll.root MeowTestRunData HLT_HIPuAK4CaloJet100Eta5p1 0 0 0
	# bash RunFile.sh `ls PPMC/*.root | head -n3 | tr '\n' ','`   MeowTestRunPPMC   None             1 1 1
	# bash RunFile.sh `ls PPData/*.root | head -n1 | tr '\n' ','` MeowTestRunPPData HLT_HIAK4PFJet80 0 1 1
	# bash RunFileOneR.sh `ls ExamplePbPbMC/Output*.root | head -n10 | tr '\n' ','` MeowTestRunMC None 1 0 0 4 1 1 Inclusive
	bash RunFileOneR.sh `ls $(PbPbData4)/*.root | head -n2 | tr '\n' ','` MeowTestRunMC None 1 0 0 4 1 1 rho

Execute: ProcessJets.cpp
	CompileRootMacro ProcessJets.cpp Execute \
		-I$(ProjectBase)/CommonCode/include \
		$(ProjectBase)/CommonCode/library/*.o \
		`$(FastJet) --cxxflags --libs` \
		-L$(FJContrib)/lib -I$(FJContrib)/include -lConstituentSubtractor

SubmitBeforeRho:
	bash GenerateSubmissionOneR.sh "PbPbData PPMC PPData PbPbMCJEC PbPbMCInclusive" "1 2 3 4 5 6 7 8 9"
	# condor_submit Submit.condor

SubmitAfterRho:
	bash GenerateSubmissionOneR.sh "PbPbMCRho" "1 2 3 4 5 6 7 8 9"
	# condor_submit Submit.condor

MergeFiles:
	bash MergeParts.sh

CleanAndMergeFiles:
	# Will clean out the temporary root files in the Parts/ directory!  Wait 10 seconds for safety...
	sleep 10
	rm Output/Parts/*root
	bash MergeParts.sh




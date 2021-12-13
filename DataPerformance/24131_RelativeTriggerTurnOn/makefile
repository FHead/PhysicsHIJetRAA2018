
FastJet   = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet/3.3.4-ghbfee/bin/fastjet-config
FJContrib = /cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/fastjet-contrib/1.044-ghbfee/

PbPbData1 = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12/211020_104744/0000/
JECBase   = $(ProjectBase)/CommonCode/jec/
JECTag    = Autumn18_HI_RAAV2_MC

default: Prepare TestRun

Prepare:
	rm -f PbPbData1
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12/211020_104744/0000/ PbPbData1
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .

Execute: MakeTurnOn.cpp
	CompileRootMacro MakeTurnOn.cpp Execute \
		-I$(ProjectBase)/CommonCode/include \
		$(ProjectBase)/CommonCode/library/*.o \
		`$(FastJet) --cxxflags --libs` \
		-L$(FJContrib)/lib -I$(FJContrib)/include -lConstituentSubtractor

ExecuteFit: FitTurnOn.cpp
	CompileRootMacro FitTurnOn.cpp ExecuteFit

TestRun: Execute
	time ./Execute --Input `ls $(PbPbData1)/*root | head -n10 | tr '\n' ','` \
		--Base HLT_HIPuAK4CaloJet80Eta5p1 \
		--Trigger HLT_HIPuAK4CaloJet100Eta5p1 \
		--Jet "akCs1PFJetAnalyzer/t" \
		--CentralityMin 0.0 --CentralityMax 0.1 \
		--EtaMin -2.0 --EtaMax 2.0 \
		--DoBaselineCutAA true --DoBaselineCutPP false \
		--JEC "$(JECBase)/$(JECTag)/$(JECTag)_L2Relative_AK1PF.txt","$(JECBase)/$(JECTag)/$(JECTag)_L2L3Residual_AK1PF.txt"

ProcessAll: Execute
	bash Run.sh

TestFit: ExecuteFit
	./ExecuteFit --Input Result_R1_Centrality0to10.root --Output Plots_R1_Centrality0to10.pdf \
		--DHFile GlobalSettingTest.dh --State PbPbTriggerTurnOn --KeyPrefix R1_Centrality0to10

ExecuteSummary: PlotPercentage.cpp
	CompileRootMacro PlotPercentage.cpp ExecuteSummary

Harvest: ExecuteSummary ExecuteFit
	-bash RunFit.sh
	./ExecuteSummary --DHFile GlobalSettingTemp.dh
	# MAKE SURE THAT YOU COPY GlobalSettingTemp.dh into GlobalSetting.dh

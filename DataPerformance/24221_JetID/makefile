
PPJECVersion = Summer20UL17_ppRef5TeV_RAAV1_DATA
PPJECBase    = $(ProjectBase)/CommonCode/jec/$(PPJECVersion)/$(PPJECVersion)
PPR4JEC      = $(PPJECBase)_L2Relative_AK4PF.txt,$(PPJECBase)_L2L3Residual_AK4PF.txt

default: TestRun

Prepare:
	rm -f PPData
	ln -sf ~/EOSHI/pp2017/Forest/HighEGJet/Run2017G-UL2017_MiniAODv2-v1/MINIAOD/HighEGJet/20211201FullRunULHighEGJetHighTreshold/211201_130333/0000/ PPData

TestRun: Execute
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_NHFMinCut float -999
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_NHFMaxCut float 0.9
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_NEFMinCut float -999
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_NEFMaxCut float 0.9
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_CHFMinCut float 0
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_CHFMaxCut float 999
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_CEFMinCut float -999
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_CEFMaxCut float 0.8
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_MUFMinCut float -999
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_MUFMaxCut float 0.8
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_MultiplicityMinCut int 1
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_MultiplicityMaxCut int 99999
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_ChargedMultiplicityMinCut int 0
	DHSet JetIDCut.dh JetID PPData_R4_CentralityInclusive_ChargedMultiplicityMaxCut int 99999
	./Execute --Input `find PPData/ | grep root$ | head -n1 | tr '\n' ','` --Output PPR4.pdf \
		--Trigger HLT_HIAK4PFJet80 --DoBaselineCutAA false --DoBaselineCutPP true \
		--Tree "ak4PFJetAnalyzer/t" \
		--JEC $(PPR4JEC) \
		--MinPT 150 --JetR 0.4 \
		--Fraction 0.10 \
		--DHFile JetIDCut.dh --State JetID --KeyBase PPData_R4_CentralityInclusive
	cp PPR4.pdf ~/public/html/

Execute: JetIDPlots.cpp
	CompileRootMacro JetIDPlots.cpp Execute \
		-I$(ProjectBase)/CommonCode/include $(ProjectBase)/CommonCode/library/Messenger.o





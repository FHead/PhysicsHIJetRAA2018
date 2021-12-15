
PPJECVersion = Summer20UL17_ppRef5TeV_RAAV1_DATA
PPJECBase    = $(ProjectBase)/CommonCode/jec/$(PPJECVersion)/$(PPJECVersion)
PPR4JEC      = $(PPJECBase)_L2Relative_AK4PF.txt,$(PPJECBase)_L2L3Residual_AK4PF.txt

default: TestRun

Prepare:
	mkdir -p PDF

RunAAData: Execute
	bash RunAAData.sh

RunAAMC: Execute
	bash RunAAMC.sh

RunPP: Execute
	bash RunPP.sh

TestRun: Execute
	bash SetID.sh
	./Execute --Input `find PPData/ | grep root$ | head -n1 | tr '\n' ','` --Output PPR4.pdf \
		--Trigger HLT_HIAK4PFJet80 --DoBaselineCutAA false --DoBaselineCutPP true \
		--Tree "ak4PFJetAnalyzer/t" \
		--JEC $(PPR4JEC) \
		--MinPT 150 --JetR 0.4 \
		--Fraction 1.00 \
		--DHFile JetIDCut.dh --State JetID --KeyBase PPData_R4_CentralityInclusive

Execute: JetIDPlots.cpp
	CompileRootMacro JetIDPlots.cpp Execute \
		-I$(ProjectBase)/CommonCode/include $(ProjectBase)/CommonCode/library/Messenger.o






default: TestRun

Prepare:
	rm -f Input
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output Input
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh .

Execute: RunCentrality.cpp
	CompileRootMacro RunCentrality.cpp Execute

TestRun: Execute
	./Execute --Input `ls Input/PbPbData_R4_*root | grep -v 70 | tr '\n' ','` --Output R4.pdf \
		--DHFile GlobalSetting.dh
	./Execute --Input `ls Input/PbPbDataStoredCentrality_R4_*root | grep -v 70 | tr '\n' ','` --Output R4Stored.pdf \
		--DHFile GlobalSetting.dh
	./Execute --Input `ls Input/PbPbDataCentralityDown_R4_*root | grep -v 70 | tr '\n' ','` --Output R4Up.pdf \
		--DHFile GlobalSetting.dh
	./Execute --Input `ls Input/PbPbDataCentralityUp_R4_*root | grep -v 70 | tr '\n' ','` --Output R4Down.pdf \
		--DHFile GlobalSetting.dh



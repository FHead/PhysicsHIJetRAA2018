

Prepare:
	rm -f MBInput HPInput
	ln -sf $(ProjectBase)/MainAnalysis/GlobalSetting/GlobalSetting.dh
	ln -sf $(ProjectBase)/DataPerformance/24261_TriggerTurnOnBatchRun/Output MBInput
	ln -sf $(ProjectBase)/MainAnalysis/23752_CopyJetFromForest/Output HPInput

Execute: CheckUEBug.cpp
	CompileRootMacro CheckUEBug.cpp Execute

TestRun: Execute
	./Execute



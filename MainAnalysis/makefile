
default: Prepare TestRunPart2

Prepare:
	(cd GlobalSetting && make)

TestRunPart1:
	(cd 23752_CopyJetFromForest && make Prepare TestRun)
	(cd 23775_CentralityWeights && make Prepare TestRun)
	(cd 23762_UnfoldPreparation && make Prepare TestRun)

TestRunPart2:
	(cd 23762_PerfectRecoGeneration && make Prepare TestRun)
	(cd 23762_FakeData && make Prepare TestRun)
	(cd 23762_ActualUnfold && make Prepare TestRun TestRunPP)
	(cd 23763_Systematics && make Prepare RunTestRunData)
	(cd 23763_BeautifulPlots && make Prepare RunTestRunJetPT RunTestRunJetPTClosure)
	(cd 23763_BeautifulMatrix && make Prepare TestRun)

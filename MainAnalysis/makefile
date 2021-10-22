
default: Prepare TestRunPart2

Prepare:
	(cd GlobalSetting && make)

TestRunPart1:
	(cd 23752_CopyJetFromForest && make Prepare TestRun)
	(cd 23775_CentralityWeights && make Prepare TestRun)
	(cd 23762_UnfoldPreparation && make Prepare TestRun)
	(cd 24112_BrilCalc          && make Prepare RunPP RunAA)
	(cd 24121_MBCounting        && make Prepare MergeMB RunAA)

TestRunPart2:
	(cd 23762_PerfectRecoGeneration && make Prepare TestRun)
	(cd 23762_FakeData              && make Prepare TestRun)
	(cd 23762_ActualUnfold          && make Prepare TestRun TestRunPP)
	(cd 23772_UnfoldIteration       && make Prepare TestRun)
	(cd 23762_PerfectRecoGeneration && make Prepare TestRunData)
	(cd 23762_FakeData              && make Prepare TestRunData)
	(cd 23762_ActualUnfold          && make Prepare TestRunDataToy)
	(cd 23772_UnfoldIteration       && make Prepare TestRunData)
	(cd 23763_Systematics           && make Prepare RunTestRunData)
	(cd 24113_HEPData               && make default)
	(cd 23763_BeautifulPlots        && make Prepare RunTestRunJetPT RunTestRunJetPTClosure)
	(cd 23763_BeautifulMatrix       && make Prepare TestRunPP TestRun)
	(cd 24114_PPRatioHEPData        && make default)
	(cd 24114_BeautifulPPRatioPlots && make RunTestRunJetPT)



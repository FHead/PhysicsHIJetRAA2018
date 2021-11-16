
default: Prepare TestRunPart2

Prepare:
	(cd GlobalSetting && make)

Sleep:
	SleepUntilDone.sh

TestRunPart1: TestRunPart1A TestRunPart1B TestRunPart1C

TestRunPart1A:
	(cd 23752_CopyJetFromForest && make Prepare SubmitBeforeRho)
	SleepUntilDone.sh

TestRunPart1B:
	# (cd 23775_CentralityWeights && make Prepare TestRun)
	(cd 24155_UEMatchingWeight  && make Prepare RunAll FitAll)
	(cd 23752_CopyJetFromForest && make Prepare DeleteAndMerge SubmitAfterRho)
	SleepUntilDone.sh

TestRunPart1C:
	(cd 23752_CopyJetFromForest && make Prepare DeleteAndMerge)
	(cd 23762_UnfoldPreparation && make Prepare RunPP RunAA)
	(cd 24112_BrilCalc          && make Prepare RunPP RunAA)
	(cd 24121_MBCounting        && make Prepare MergeMB RunAA)
	(cd $(ProjectBase)/DataPerformance/24131_RelativeTriggerTurnOn && make Prepare ProcessAll)

TestRunPart2:
	# Copy over the following from lxplus
	#    1. trigger output files
	#    2. unfold preparation output files
	#    3. GlobalSetting.dh
	sleep 5
	(cd $(ProjectBase)/DataPerformance/24131_RelativeTriggerTurnOn && make Harvest)
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
	(cd 24122_RAA                   && make Prepare TestRun)



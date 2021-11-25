
default: Prepare RunPart2

Prepare:
	(cd GlobalSetting && make)

Sleep:
	SleepUntilDone.sh

RunPart1: RunPart1A RunPart1B RunPart1C

RunPart1A:
	(cd 23752_CopyJetFromForest && make Prepare SubmitBeforeRho)
	SleepUntilDone.sh

RunPart1B:
	(cd 23752_CopyJetFromForest && make Prepare DeleteAndMerge)
	(cd $(ProjectBase)/DataPerformance/24131_RelativeTriggerTurnOn && make Prepare ProcessAll)
	(cd $(ProjectBase)/DataPerformance/24131_RelativeTriggerTurnOn && make Harvest)
	# (cd 23775_CentralityWeights && make Prepare TestRun)
	(cd 24155_UEMatchingWeight  && make Prepare RunAll FitAll)
	(cd 23752_CopyJetFromForest && make Prepare SubmitAfterRho)
	SleepUntilDone.sh

RunPart1C:
	(cd 23752_CopyJetFromForest && make Prepare DeleteAndMerge)
	(cd 23762_UnfoldPreparation && make Prepare RunPP RunAA)
	(cd 24112_BrilCalc          && make Prepare RunPP RunAA)
	(cd 24121_MBCounting        && make Prepare MergeMB RunAA)

CleanPart2:
	#############################################
	# Clean all local output files?             #
	# Waiting 10 seconds in case it's a mistake #
	#############################################
	sleep 10
	(cd 23762_PerfectRecoGeneration    && make Clean)
	(cd 23762_FakeData                 && make Clean)
	(cd 23762_ActualUnfold             && make Clean)
	(cd 23772_UnfoldIteration          && make Clean)
	(cd 23763_Systematics              && make Clean)
	(cd 24165_SystematicsCombination   && make Clean)
	(cd 24113_HEPData                  && make Clean)
	(cd 23763_BeautifulPlots           && make Clean)
	(cd 23763_BeautifulMatrix          && make Clean)
	(cd 24114_PPRatioHEPData           && make Clean)
	(cd 24114_BeautifulPPRatioPlots    && make Clean)
	(cd 24171_BeautifulSystematicsPlot && make Clean)
	(cd 24122_RAA                      && make Clean)

RunPart2:
	#########################################################################
	# Make sure to copy over the following from lxplus before continuing... #
	#    1. unfold preparation output files                                 #
	#    2. GlobalSetting.dh                                                #
	# Also make sure that the ProjectBase is set correctly!                 #
	#########################################################################
	sleep 10
	(cd 24165_PUBugCorrection          && make Prepare PlaceHolder)
	(cd 23772_UnfoldIteration          && make SetDefault)
	(cd 23762_PerfectRecoGeneration    && make Prepare RunMC)
	(cd 23762_FakeData                 && make Prepare RunMC)
	(cd 23762_ActualUnfold             && make Prepare RunAA RunPP)
	(cd 23772_UnfoldIteration          && make Prepare RunMC)
	(cd 23762_PerfectRecoGeneration    && make Prepare RunData)
	(cd 23762_FakeData                 && make Prepare RunData)
	(cd 23762_ActualUnfold             && make Prepare RunDataToy)
	(cd 23772_UnfoldIteration          && make Prepare RunData)
	(cd 23763_Systematics              && make Prepare RunData)
	(cd 24165_SystematicsCombination   && make Prepare SetDHFile RunAll)
	(cd 24113_HEPData                  && make default)
	(cd 23763_BeautifulPlots           && make Prepare RunJetPT RunJetPTClosure)
	(cd 23763_BeautifulMatrix          && make Prepare RunPP RunAA)
	(cd 24114_PPRatioHEPData           && make default)
	(cd 24114_BeautifulPPRatioPlots    && make RunJetPT)
	(cd 24171_BeautifulSystematicsPlot && make Prepare RunAll)
	(cd 24122_RAA                      && make Prepare Run)



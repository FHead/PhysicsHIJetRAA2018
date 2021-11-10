#!/bin/bash

File=Submit.condor
rm -f ${File}

PPMCBase=/eos/cms/store/group/phys_heavyions/chenyi///pp2017/Forest/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
PPDataBase=/eos/cms/store/group/phys_heavyions/chenyi///pp2017/Forest/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20201111FirstRun/201111_162524/0000//
PbPbMCBase=/eos/cms/store/group/phys_heavyions/chenyi///PbPb2018/Forest/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAAWithRhoGenBugFix/211104_112116//
PbPbDataBase=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAARetry3/211015_104302/

declare -A Location=()
for i in `seq 1 9`
do
   Location[PPMC$i]=$PPMCBase
   Location[PPData$i]=$PPDataBase
   Location[PbPbMC$i]=$PbPbMCBase
done

Location[PbPbData1]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12WithRhoGenBugFix/211106_162257/
Location[PbPbData2]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12WithRhoGenBugFix/211106_162257/
Location[PbPbData3]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
Location[PbPbData4]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
Location[PbPbData5]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35WithRhoGenBugFix/211106_221601/
Location[PbPbData6]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67/211020_104804/0000/
Location[PbPbData7]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67/211020_104804/0000/
Location[PbPbData8]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit8WithRhoGenBugFix/211106_162321/
Location[PbPbData9]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit9WithRhoGenBugFix/211106_162329/

ToRunList="PbPbMC"
ToRunR="1 2 3 4 5 6 7 8 9"

echo "Setting up submission to run on the following list"
echo "$ToRunList"
echo "with the following jet radius tags"
echo "$ToRunR"

echo "Universe              = vanilla" >> ${File}
echo "Executable            = /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23752_CopyJetFromForest/JobWrapperOneR.sh" >> ${File}
echo "should_transfer_files = NO" >> ${File}
echo "+JobFlavour           = \"longlunch\"" >> ${File}
echo "" >> ${File}
echo "" >> ${File}

for i in ${ToRunList}
do
   Count=0
   for RTag in ${ToRunR}
   do
      LocationKey=$i
      if [[ "$i" == "PbPbMCJEC" ]]; then
         LocationKey="PbPbMC"
      fi

      for j in `find ${Location[${LocationKey}$RTag]}/ | grep root$ | Reformat 25 | tr ' ' ',' | sed "s/[ ,]*$//g"`
      do
         # echo $j
         Count=`echo $Count | AddConst 1`

         ExtraArguments="None 1 1 1 $RTag"
         if [[ "$i" == "PPMC" ]]; then
            ExtraArguments="None 1 1 1 $RTag 0 0"
         elif [[ "$i" == "PPData" ]]; then
            ExtraArguments="HLT_HIAK4PFJet80 0 1 1 $RTag 0 0"
         elif [[ "$i" == "PbPbMC" ]]; then
            ExtraArguments="None 1 0 0 $RTag 1 1"
         elif [[ "$i" == "PbPbMCJEC" ]]; then
            ExtraArguments="None 1 0 0 $RTag 0 0"
         elif [[ "$i" == "PbPbData" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 1 1"
         fi

         echo "Arguments = $j TestRun${i}Part${Count} $ExtraArguments" >> ${File}
         echo "Output    = Log/${i}${RTag}Part${Count}.out" >> ${File}
         echo "Error     = Log/${i}${RTag}Part${Count}.err" >> ${File}
         echo "Log       = Log/${i}${RTag}Part${Count}.log" >> ${File}
         echo "Queue" >> ${File}
         echo "" >> ${File}
      done

      echo "" >> ${File}
      echo "" >> ${File}
   done
done



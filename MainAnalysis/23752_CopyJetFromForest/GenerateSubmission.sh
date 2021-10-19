#!/bin/bash

File=Submit.condor
rm -f ${File}

PPMC=/eos/cms/store/group/phys_heavyions/chenyi///pp2017/Forest/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
PPData=/eos/cms/store/group/phys_heavyions/chenyi///pp2017/Forest/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20201111FirstRun/201111_162524/0000//
PbPbData=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAARetry3/211015_104302/
PbPbMC=/eos/cms/store/group/phys_heavyions/chenyi////PbPb2018/Forest/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAARetry/211009_142235/0000/

echo "Universe              = vanilla" >> ${File}
echo "Executable            = /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23752_CopyJetFromForest/JobWrapper.sh" >> ${File}
echo "should_transfer_files = NO" >> ${File}
echo "+JobFlavour           = \"longlunch\"" >> ${File}
echo "" >> ${File}
echo "PPMC = ${PPMC}" >> ${File}
echo "PPData = ${PPData}" >> ${File}
echo "PbPbMC = ${PbPbMC}" >> ${File}
echo "PbPbData = ${PbPbData}" >> ${File}
echo "" >> ${File}
echo "" >> ${File}

for i in PbPbData #PPMC PPData PbPbMC PbPbData
do
   Count=0
   for j in `find ${i}/ | grep root$ | Reformat 2 | tr ' ' ',' | sed "s/$i/$\($i)/g" | sed "s/[ ,]*$//g"`
   do
      echo $j
      Count=`echo $Count | AddConst 1`

      ExtraArguments="None 1 1 1"
      if [[ "$i" == "PPMC" ]]; then
         ExtraArguments="None 1 1 1"
      elif [[ "$i" == "PPData" ]]; then
         ExtraArguments="HLT_HIAK4PFJet80 0 1 1"
      elif [[ "$i" == "PbPbMC" ]]; then
         ExtraArguments="None 1 0 0"
      elif [[ "$i" == "PbPbData" ]]; then
         ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0"
      fi

      echo "Arguments = $j TestRun${i}Part${Count} $ExtraArguments" >> ${File}
      echo "Output    = Log/${i}Part${Count}.out" >> ${File}
      echo "Error     = Log/${i}Part${Count}.err" >> ${File}
      echo "Log       = Log/${i}Part${Count}.log" >> ${File}
      echo "Queue" >> ${File}
      echo "" >> ${File}
   done
   
   echo "" >> ${File}
   echo "" >> ${File}
done



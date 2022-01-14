#!/bin/bash

File=Submit.condor
rm -f ${File}

ToRun="PPData PPDataEOY"
ToRunR="1 2 3 5 6 7 8 9"
# ToRunR="4"
Group=40

echo "Setting up submission to run on the following list"
echo "$ToRun"
echo "with the following jet radius tags"
echo "$ToRunR"
echo "and number of forest files per job"
echo "$Group"

echo "Universe              = vanilla" >> ${File}
echo "Executable            = /afs/cern.ch/user/c/chenyi/PhysicsWorkspace/HIJetRAA2018/DataPerformance/24261_TriggerTurnOnBatchRun/Run.sh" >> ${File}
echo "should_transfer_files = NO" >> ${File}
echo "+JobFlavour           = \"longlunch\"" >> ${File}
echo "" >> ${File}
echo "" >> ${File}

Count=0

for Type in $ToRun
do
   Centrality=
   if [[ "$Type" == "PbPbData" ]]; then
      Centrality="0to10 10to30 30to50 50to70 70to90 50to90"
   elif [[ "$Type" == "PbPbMBData" ]]; then
      Centrality="Inclusive"
   elif [[ "$Type" == "PPData" ]]; then
      Centrality="Inclusive"
   elif [[ "$Type" == "PPDataEOY" ]]; then
      Centrality="Inclusive"
   fi

   for R in $ToRunR
   do
      LocationBase=`DHQuery GlobalSetting.dh Sample $Type$R`

      for j in `find "${LocationBase}/" | grep root$ | Reformat $Group | tr ' ' ',' | sed "s/[ ,]*$//g"`
      do
         Count=`echo $Count | AddConst 1`

         # Arguments to Run.sh:
         #    FileList Tag IsPP IsMB TriggerBase Trigger JetR
         # Everything after the file list is in this extra arguments list

         ExtraArguments="Default 0 0 X X $R"
         if [[ "$Type" == "PbPbData" ]]; then
            ExtraArguments="PbPbData_Part$Count 0 0 HLT_HIPuAK4CaloJet80Eta5p1 HLT_HIPuAK4CaloJet100Eta5p1 $R"
         elif [[ "$Type" == "PbPbMBData" ]]; then
            ExtraArguments="PbPbMBData_Part$Count 0 0 HLT_HIPuAK4CaloJet40Eta5p1 HLT_HIPuAK4CaloJet100Eta5p1 $R"
         elif [[ "$Type" == "PPData" ]]; then
            ExtraArguments="PPData_Part$Count 1 0 HLT_HIAK4PFJet60 HLT_HIAK4PFJet80 $R"
         elif [[ "$Type" == "PPDataEOY" ]]; then
            ExtraArguments="PPDataEOY_Part$Count 2 0 HLT_HIAK4PFJet60 HLT_HIAK4PFJet80 $R"
         fi

         echo "Arguments = $j  $ExtraArguments" >> ${File}
         echo "Output    = Log/${Type}${R}Part${Count}.out" >> ${File}
         echo "Error     = Log/${Type}${R}Part${Count}.err" >> ${File}
         echo "Log       = Log/${Type}${R}Part${Count}.log" >> ${File}
         echo "Queue" >> ${File}
         echo "" >> ${File}
      done
      
      echo "" >> ${File}
      echo "" >> ${File}
   done
done


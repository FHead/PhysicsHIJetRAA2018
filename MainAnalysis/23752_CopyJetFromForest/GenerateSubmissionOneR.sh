#!/bin/bash

File=Submit.condor
rm -f ${File}

# Available arguments: PbPbMC PbPbData PPMC PPData PbPbMCJEC PbPbMCInclusive PbPbMCRho
# PbPbMCJEC       = don't apply phi correction
# PbPbMCInclusive = don't split centrality
# PbPbMCRho       = don't split centrality, but use rho to weight to data
# ToRunList="PbPbData"
# ToRunR="6 7"

ToRunList="$1"
ToRunR="$2"

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

mkdir -p Log/
rm -f Log/*

for i in ${ToRunList}
do
   Count=0
   for RTag in ${ToRunR}
   do
      LocationKey=$i
      if [[ "$i" == "PbPbMCJEC" ]]; then
         LocationKey="PbPbMC"
      elif [[ "$i" == "PbPbMCInclusive" ]]; then
         LocationKey="PbPbMC"
      elif [[ "$i" == "PbPbMCRho" ]]; then
         LocationKey="PbPbMC"
      fi

      LocationBase=`DHQuery GlobalSetting.dh Sample ${LocationKey}${RTag} | tr -d '"'`

      for j in `find "${LocationBase}/" | grep root$ | Reformat 25 | tr ' ' ',' | sed "s/[ ,]*$//g"`
      do
         # echo $j
         Count=`echo $Count | AddConst 1`

         # Arguments = InputFile Tag Trigger IsMC IsPP Recluster RTag DoPhiResidual DoExclusion Centrality
         # ExtraArguments start from the Trigger
         ExtraArguments="None 1 1 1 $RTag 0 0 default"
         if [[ "$i" == "PPMC" ]]; then
            ExtraArguments="None 1 1 1 $RTag 0 0 default"
         elif [[ "$i" == "PPData" ]]; then
            ExtraArguments="HLT_HIAK4PFJet80 0 1 1 $RTag 0 0 default"
         elif [[ "$i" == "PbPbMC" ]]; then
            ExtraArguments="None 1 0 0 $RTag 1 1 default"
         elif [[ "$i" == "PbPbMCInclusive" ]]; then
            ExtraArguments="None 1 0 0 $RTag 1 1 Inclusive"
         elif [[ "$i" == "PbPbMCRho" ]]; then
            ExtraArguments="None 1 0 0 $RTag 1 1 rho"
         elif [[ "$i" == "PbPbMCJEC" ]]; then
            ExtraArguments="None 1 0 0 $RTag 0 0 default"
         elif [[ "$i" == "PbPbData" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 1 1 default"
         fi

         echo "Arguments = $j Run_${i}_Part${Count} $ExtraArguments" >> ${File}
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



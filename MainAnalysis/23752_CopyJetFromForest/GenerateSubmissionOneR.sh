#!/bin/bash

File=Submit.condor
rm -f ${File}

ToRunList="$1"
ToRunR="$2"

# Available arguments: 
# PPMC                     = nominal PP MC (UL)
# PPData                   = nominal PP data (UL)
# PPMCEOY                  = nominal PP MC (EOY)
# PPDataEOY                = nominal PP data (EOY)
# PbPbMC                   = PbPb MC with MC centrality table
# PbPbMCInclusive          = don't split centrality
# PbPbMCRho                = use rho to weight to data
# PbPbMCRhoCentralityUp    = use rho to weight to data.  Use the centrality-shift table
# PbPbMCRhoCentralityDown  = use rho to weight to data.  Shift centrality down
# PbPbMCRhoNoPhiResidual   = don't apply phi correction, but use rho to weight to data.
# PbPbMCJEC                = don't apply phi correction.  PT down to 0.  This is for phi JEC derivation
# PbPbData                 = nominal data
# PbPbDataNoResidual       = don't apply data residual
# PbPbDataNoPhiResidual    = don't apply phi residual
# PbPbDataCentralityUp     = centrality variation
# PbPbDataCentralityDown   = centrality variation
# PbPbDataStoredCentrality = nominal data with stored centrality

# ToRunList="PbPbData PbPbDataStoredCentrality PbPbDataNoResidual PbPbDataNoPhiResidual PbPbDataCentralityUp PbPbDataCentralityDown"
# ToRunList="PbPbMCRho PbPbMCRhoCentralityUp PbPbMCRhoCentralityDown"
ToRunList="PPData"
# ToRunList="PbPbMCRhoNoPhiResidual"
# ToRunList="PbPbMC PbPbMCInclusive"
ToRunR="1 2 3 4 5 6 7 8 9"
Group=25

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
      if [[ "$i" == "PbPbMCJEC"* ]]; then
         LocationKey="PbPbMCJEC"
      elif [[ "$i" == "PbPbMC"* ]]; then
         LocationKey="PbPbMC"
      elif [[ "$i" == "PbPbData"* ]]; then
         LocationKey="PbPbData"
      fi

      LocationBase=`DHQuery GlobalSetting.dh Sample ${LocationKey}${RTag} | tr -d '"'`

      for j in `find "${LocationBase}/" | grep root$ | Reformat $Group | tr ' ' ',' | sed "s/[ ,]*$//g"`
      do
         # echo $j
         Count=`echo $Count | AddConst 1`

         # Arguments = InputFile Tag Trigger IsMC IsPP Recluster RTag MinPT SkipReco
         #    DoPhiResidual DoDataResidual DoExclusion Centrality CentralityTable
         # ExtraArguments start from the Trigger
         ExtraArguments="None 1 1 1 $RTag 40 0 0 0 0 default default"
         if [[ "$i" == "PPMC" ]]; then
            ExtraArguments="None 1 2 1 $RTag 0 0 0 0 0 default default"   # UL
         elif [[ "$i" == "PPData" ]]; then
            ExtraArguments="HLT_HIAK4PFJet80 0 2 0 $RTag 40 0 0 1 0 default default"   # if PP Data UL don't recluster
         elif [[ "$i" == "PPMCEOY" ]]; then
            ExtraArguments="None 1 1 1 $RTag 40 0 0 0 0 default default"   # NonUL
         elif [[ "$i" == "PPDataEOY" ]]; then
            ExtraArguments="HLT_HIAK4PFJet80 0 1 1 $RTag 40 0 1 0 default default"   # recluster
            # ExtraArguments="HLT_HIAK4PFJet80 0 1 0 $RTag 40 0 1 0 default default"   # don't recluster
         elif [[ "$i" == "PbPbMC" ]]; then
            ExtraArguments="None 1 0 0 $RTag 60 0 1 0 1 default MC"
         elif [[ "$i" == "PbPbMCInclusive" ]]; then
            ExtraArguments="None 1 0 0 $RTag 60 0 1 0 1 Inclusive default"
         elif [[ "$i" == "PbPbMCRho" ]]; then
            ExtraArguments="None 1 0 0 $RTag 60 0 1 0 1 rho default"
         elif [[ "$i" == "PbPbMCRhoCentralityUp" ]]; then
            ExtraArguments="None 1 0 0 $RTag 60 0 1 0 1 rhoup default"
         elif [[ "$i" == "PbPbMCRhoCentralityDown" ]]; then
            ExtraArguments="None 1 0 0 $RTag 60 0 1 0 1 rhodown default"
         elif [[ "$i" == "PbPbMCRhoNoPhiResidual" ]]; then
            ExtraArguments="None 1 0 0 $RTag 60 0 0 0 1 rho default"
         elif [[ "$i" == "PbPbMCJEC" ]]; then
            ExtraArguments="None 1 0 0 $RTag 0 1 0 0 0 Inclusive default"
         elif [[ "$i" == "PbPbData" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 60 0 1 1 1 default Data"
         elif [[ "$i" == "PbPbDataStoredCentrality" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 60 0 1 1 1 default default"
         elif [[ "$i" == "PbPbDataNoResidual" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 60 0 1 0 1 default Data"
         elif [[ "$i" == "PbPbDataNoPhiResidual" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 60 0 0 1 1 default Data"
         elif [[ "$i" == "PbPbDataCentralityUp" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 60 0 1 1 1 default DataUp"
         elif [[ "$i" == "PbPbDataCentralityDown" ]]; then
            ExtraArguments="HLT_HIPuAK4CaloJet100Eta5p1 0 0 0 $RTag 60 0 1 1 1 default DataDown"
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



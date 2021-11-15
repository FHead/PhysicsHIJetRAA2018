#!/bin/sh

mkdir -p pdf
mkdir -p root

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

for R in $JetR
do
   for C in $Centrality
   do
      TriggerPTMin=`DHQuery GlobalSetting.dh TriggerTurnOn R${R}_Centrality${C}_Cut`
      ./Execute --Data Input/PbPbData_R${R}_Centrality${C}.root \
         --MC Input/PbPbMC_R${R}_CentralityInclusive.root \
         --JetMinPT ${TriggerPTMin} --Output root/Output_R${R}_Centrality${C}.root
      
      # Skip=false
      # if [[ "$C" == "0to10" ]]; then Skip=true; fi

      # ./Execute --Data Input/PbPbData_R${R}_Centrality${C}.root \
      #    --MC Input/PbPbMC_R${R}_CentralityInclusive.root \
      #    --JetMinPT ${TriggerPTMin} --Output pdf/Output_R${R}_Centrality${C}.pdf \
      #    --RootOutput root/Output_R${R}_Centrality${C}.root \
		#    --BinCount 100 --BinMagnification 10 --SkipFinalBin $Skip
   done
done

#!/bin/sh

Prefix=$1
Suffix=$2
StateSuffix=$3
PriorChoice=$4
IsPP=$5

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

for R in $JetR
do
   for C in $Centrality
   do
      Ignore=`DHQuery GlobalSetting.dh Binning PTUnderflow_R${R}_Centrality${C}`

      Prior=$PriorChoice
      if [[ "$PriorChoice" == "Nominal" ]]; then
         Prior=`DHQuery GlobalSetting.dh DefaultPrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`
      elif [[ "$PriorChoice" == "Alternate" ]]; then
         Prior=`DHQuery GlobalSetting.dh AlternatePrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`
      fi
      Prior=${Prior}Prior

	   ./Execute --Input Input/${Prefix}_R${R}_Centrality${C}_${Suffix}_${Prior}.root \
         --Output Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_${Prior}.pdf \
         --Ignore ${Ignore} --Reference HMCTruth \
         --State Iterations --Key ${Prefix}_R${R}_Centrality${C}_${StateSuffix}_${Prior}
   done
done



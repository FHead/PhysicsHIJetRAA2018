#!/bin/sh

Prefix=$1
Suffix=$2
IsPP=$3

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

	   ./Execute --Input Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Output Output/${Prefix}_R${R}_Centrality${C}_${Suffix}.pdf \
         --Ignore ${Ignore} --Reference HMCTruth \
         --State ${Prefix} --Key BestIteration_R${R}_Centrality${C}
   done
done



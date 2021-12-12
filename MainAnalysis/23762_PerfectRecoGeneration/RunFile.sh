#!/bin/bash

Prefix=$1
Suffix=$2
IsPP=$3
IterationPrefix=$4
PriorChoice=$5

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

# echo $JetR

for R in $JetR
do
   for C in $Centrality
   do
      echo Running R $R and Centrality $C
      
      Prior=$PriorChoice
      if [[ $PriorChoice == "Nominal" ]]; then
         Prior=`DHQuery GlobalSetting.dh DefaultPrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`
      elif [[ $PriorChoice == "Alternate" ]]; then
         Prior=`DHQuery GlobalSetting.dh AlternatePrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`
      else
         Prior=$PriorChoice
      fi
      Prior=${Prior}Prior

      GenHistogram=HMCGen
      GenFile=
      OutputFile=
      if [[ "$IterationPrefix" == "" ]]; then
         GenHistogram=HMCGen
         GenFile=Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root
         OutputFile=Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_PerfectReco.root
      else
         Iteration=`DHQuery GlobalSetting.dh Iterations ${IterationPrefix}_R${R}_Centrality${C}_${Suffix}_${Prior}`
         GenHistogram=HUnfoldedBayes${Iteration}
         GenFile=UnfoldedInput/${Prefix}_R${R}_Centrality${C}_${Suffix}_${Prior}.root
         OutputFile=Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_${Prior}_PerfectReco.root
      fi

      # echo $C
      # echo GenHistogram = $GenHistogram
      # echo Input = Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root

      ./Execute \
         --MC           Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Yield        Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Gen          $GenFile \
         --GenHistogram $GenHistogram \
         --Output       $OutputFile
   done
done


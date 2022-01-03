#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR`
Centrality=`DHQuery GlobalSetting.dh Global Centrality`

for R in $JetR
do
   for C in $Centrality Inclusive
   do
      Prefix=
      if [[ "$C" == "Inclusive" ]]; then
         Prefix=PPMC
      else
         Prefix=PbPbMCRho
      fi
      JERFile=${ProjectBase}/CommonCode/jer/24215_JER/JER_${Prefix}_R${R}_Centrality${C}.txt
      if [[ "$C" == "50to70" ]] || [[ "$C" == "70to90" ]]; then
         JERFile=${ProjectBase}/CommonCode/jer/24215_JER/JER_${Prefix}_R${R}_Centrality50to90.txt
      fi

      TriggerBase=R${R}_Centrality${C}
      ./Execute --DHFile GlobalSetting.dh --Base R${R}_Centrality${C} \
         --MinPT 150 \
         --DoTrigger true --TriggerPercentage 0.99 --TriggerBase $TriggerBase \
         --DoTriggerResolution true --TriggerResolutionShift 2 --ResolutionFile $JERFile
   done
done

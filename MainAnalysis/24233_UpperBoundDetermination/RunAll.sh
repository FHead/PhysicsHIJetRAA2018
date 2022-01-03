#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR`
Centrality=`DHQuery GlobalSetting.dh Global Centrality`

for R in $JetR
do
   for C in $Centrality Inclusive
   do
      MCPrefix=
      DataPrefix=
      if [[ "$C" == "Inclusive" ]]; then
         MCPrefix=PPMC
         DataPrefix=PPData
      else
         MCPrefix=PbPbMCRho
         DataPrefix=PbPbData
      fi
      JERFile=${ProjectBase}/CommonCode/jer/24215_JER/JER_${MCPrefix}_R${R}_Centrality${C}.txt
      Nominal=Input/${DataPrefix}_R${R}_Centrality${C}_Nominal.root

      ./Execute --DHFile GlobalSetting.dh --Base R${R}_Centrality${C} --NominalFile ${Nominal} \
         --MaxPT 1500 \
         --DoRecoStat true --RecoStatLimit 2 \
         --DoRecoStatResolution true --RecoStatResolutionShift 0 --ResolutionFile $JERFile
   done
done



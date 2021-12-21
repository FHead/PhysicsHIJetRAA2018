#!/bin/bash

for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90 Inclusive
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



#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR`

PbPbBase=`DHQuery GlobalSetting.dh Sample PbPbMC1`
PPBase=`DHQuery GlobalSetting.dh Sample PPMC1`

NFile=25
NSample=250000

for R1 in $JetR
do
   for R2 in 1 2 8 9
   do
      R1Value=`DHQuery GlobalSetting.dh JetR $R1`
      R2Value=`DHQuery GlobalSetting.dh JetR $R2`
      echo "Running (R = $R1Value) / (R = $R2Value)"

      Match=`DHQuery GlobalSetting.dh JetRMatch $((R1 < R2 ? R1 : R2))`
      
      # Run PbPb
      ./Execute --Input `find $PbPbBase | grep root | head -n $NFile | tr '\n' ','` \
         --Tree1 akCs${R1}PFJetAnalyzer/t \
         --Tree2 akCs${R2}PFJetAnalyzer/t \
         --DHFile GlobalSetting.dh \
         --MatchAngle $Match \
         --EtaMin -2 --EtaMax 2 \
         --Output pdf/Rho_PbPbR${R1}R${R2}.pdf \
         --NSample $NSample \
         --DHOutput Rho.dh --DHState PbPbR${R1}R${R2}

      # Run pp
      # ./Execute --Input `find $PPBase | grep root | head -n $NFile | tr '\n' ','` \
      #    --Tree1 ak${R1}PFJetAnalyzer/t \
      #    --Tree2 ak${R2}PFJetAnalyzer/t \
      #    --DHFile GlobalSetting.dh \
      #    --MatchAngle $Match \
      #    --EtaMin -2 --EtaMax 2 \
      #    --Output pdf/Rho_PPR${R1}R${R2}.pdf \
      #    --NSample $NSample \
      #    --DHOutput Rho.dh --DHState PPR${R1}R${R2}
   done
done



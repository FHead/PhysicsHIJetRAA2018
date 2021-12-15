#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
   for j in 0to10 10to30 30to50 50to90
   do
      echo Running R$i C$j

      CentralityMin=`DHQuery GlobalSetting.dh CentralityMin $j`
      CentralityMax=`DHQuery GlobalSetting.dh CentralityMax $j`

      JECVersion=Autumn18_HI_RAAV2_MC
      JECBase=${ProjectBase}/CommonCode/jec/${JECVersion}/${JECVersion}
      JEC=${JECBase}_L2Relative_AK${i}PF.txt

      ./Execute --Input `find PbPbMC/ | grep root$ | head -n999 | tr '\n' ','` --Output PDF/PbPbMCR${i}C${j}.pdf \
         --Trigger "none" --DoBaselineCutAA false --DoBaselineCutPP false \
         --Tree "akCs${i}PFJetAnalyzer/t" \
         --JEC ${JEC} \
         --MinPT 150 --JetR 0.4 \
         --Fraction 1.00 \
         --CentralityMin $CentralityMin --CentralityMax $CentralityMax \
         --DHFile JetIDCut.dh --State JetID --KeyBase PbPbData_R${i}_Centrality${j}
   done
done



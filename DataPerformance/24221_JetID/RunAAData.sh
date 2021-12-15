#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
   for j in 0to10 10to30 30to50 50to90
   do
      echo Running R$i C$j

      CentralityMin=`DHQuery GlobalSetting.dh CentralityMin $j`
      CentralityMax=`DHQuery GlobalSetting.dh CentralityMax $j`

      JECVersion=Autumn18_HI_RAAV2_DATA
      JECBase=${ProjectBase}/CommonCode/jec/${JECVersion}/${JECVersion}
      JECPhi=${ProjectBase}/CommonCode/jec/Phi_24151/PhiCorrectionGen_AK${i}PF.txt
      JEC=${JECBase}_L2Relative_AK${i}PF.txt,${JECPhi},${JECBase}_L2L3Residual_AK${i}PF.txt

      ./Execute --Input `find PbPbData/ | grep root$ | head -n999 | tr '\n' ','` --Output PDF/PbPbR${i}C${j}.pdf \
         --Trigger HLT_HIPuAK4CaloJet100Eta5p1 --DoBaselineCutAA true --DoBaselineCutPP false \
         --Tree "akCs${i}PFJetAnalyzer/t" \
         --JEC ${JEC} \
         --MinPT 150 --JetR 0.4 \
         --Fraction 1.00 \
         --CentralityMin $CentralityMin --CentralityMax $CentralityMax \
         --DHFile JetIDCut.dh --State JetID --KeyBase PbPbData_R${i}_Centrality${j}
   done
done



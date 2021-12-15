#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
   echo Running R$i

   PPJECVersion=Summer20UL17_ppRef5TeV_RAAV1_DATA
   PPJECBase=${ProjectBase}/CommonCode/jec/${PPJECVersion}/${PPJECVersion}
   PPJEC=${PPJECBase}_L2Relative_AK${i}PF.txt,${PPJECBase}_L2L3Residual_AK${i}PF.txt
   
   ./Execute --Input `find PPData/ | grep root$ | head -n999 | tr '\n' ','` --Output PDF/PPR${i}.pdf \
      --Trigger HLT_HIAK4PFJet80 --DoBaselineCutAA false --DoBaselineCutPP true \
      --Tree "ak${i}PFJetAnalyzer/t" \
      --JEC ${PPJEC} \
      --MinPT 150 --JetR 0.4 \
      --Fraction 1.00 \
      --DHFile JetIDCut.dh --State JetID --KeyBase PPData_R${i}_CentralityInclusive
done



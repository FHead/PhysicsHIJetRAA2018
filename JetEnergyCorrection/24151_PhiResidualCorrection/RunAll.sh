#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

for R in $JetR
do
   RValue=`DHQuery GlobalSetting.dh JetR $R`
   # ./Execute --Input `ls Input/TestRunMCJEC_R${R}_* | head -n10 | tr '\n' ','` --Output Meow_R${R}.pdf \
   #    --Eta -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0 --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
   #    --NPT 9 --NRho 8 --NPhi 100 --JetR ${RValue} \
   #    --Correction PhiCorrection_AK${R}PF.txt --BinnedCorrection true \
   #    --BaseOnGen false
   # ./Execute --Input `ls Input/TestRunMCJEC_R${R}_* | head -n10 | tr '\n' ','` --Output MeowGen_R${R}.pdf \
   #    --Eta -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0 --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
   #    --NPT 9 --NRho 8 --NPhi 100 --JetR ${RValue} \
   #    --Correction PhiCorrectionGen_AK${R}PF.txt --BinnedCorrection true \
   #    --BaseOnGen true
   ./Execute --Input `ls Input/PbPbMCJEC_R${R}_* | head -n10 | tr '\n' ','` --Output MeowGenLow_R${R}.pdf \
      --Eta -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0 --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
      --NPT 14 --NRho 8 --NPhi 100 --JetR ${RValue} --MinPT 15 \
      --Correction PhiCorrectionGenLow_AK${R}PF.txt --BinnedCorrection true \
      --BaseOnGen true
done




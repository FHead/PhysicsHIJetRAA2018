#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

for R in $JetR
do
   RValue=`DHQuery GlobalSetting.dh JetR $R`
   ./ExecuteJEC --Input Root/MeowGenLowNoThreshold_R${R}.root \
      --Output Pdf/MeowGenLowNoThreshold_R${R}.pdf \
      --Eta -2.0,-1.5,-1.0,-0.5,0.0,0.5,1.0,1.5,2.0 --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
      --NPT 21 --NRho 10 --NPhi 80 --JetR ${RValue} --MinPT 15 --NMax 6 \
      --Correction Txt/PhiCorrectionGenLowNoThreshold_AK${R}PF.txt --BinnedCorrection true \
      --DHFile Correction.dh --DHState MeowGenLowNoThreshold_R${R} \
      --BaseOnGen true
done




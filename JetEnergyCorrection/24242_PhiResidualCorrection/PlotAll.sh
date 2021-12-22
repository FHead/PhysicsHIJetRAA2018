#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

for R in $JetR
do
   RValue=`DHQuery GlobalSetting.dh JetR $R`
   ./ExecutePlot --Input Root/MeowGenLow_R${R}.root --Output Pdf/Closure_R${R}.pdf \
      --OnTheFlyJEC true --JEC Txt/PhiCorrectionGenLow_AK${R}PF.txt --JetR $RValue
done




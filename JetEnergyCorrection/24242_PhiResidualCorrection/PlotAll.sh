#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Fraction=1.00

for R in $JetR
do
   RValue=`DHQuery GlobalSetting.dh JetR $R`
   ./ExecutePlot --Input Root/MeowGenLowNoThreshold_R${R}.root --Fraction $Fraction \
      --Output Pdf/Closure_R${R}.pdf \
      --OnTheFlyJEC true --JEC Txt/PhiCorrectionGenLowNoThreshold_AK${R}PF.txt --JetR $RValue
   ./ExecutePlot --Input Root/MeowGenLowNoThreshold_R${R}.root --Fraction $Fraction \
      --Output Pdf/ClosureScale_R${R}.pdf \
      --OnTheFlyJEC true --JEC Txt/PhiCorrectionGenLowNoThresholdScale_AK${R}PF.txt --JetR $RValue
   ./ExecutePlot --Input Root/MeowGenLowNoThreshold_R${R}.root --Fraction $Fraction \
      --Output Pdf/ClosureRaw_R${R}.pdf \
      --OnTheFlyJEC false --JEC Txt/PhiCorrectionGenLowNoThreshold_AK${R}PF.txt --JetR $RValue
   ./ExecutePlot --Input Root/MeowGenLow_R${R}.root --Fraction $Fraction \
      --Output Pdf/ClosureOldRaw_R${R}.pdf \
      --OnTheFlyJEC false --JEC Txt/PhiCorrectionGenLowNoThreshold_AK${R}PF.txt --JetR $RValue
done




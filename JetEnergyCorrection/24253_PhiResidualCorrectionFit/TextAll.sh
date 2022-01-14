#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

for R in 3 4 # $JetR
do
   ./ExecuteText --DHFile Correction.dh --DHState MeowGenLowNoThreshold_R${R} \
      --Output Txt/PhiCorrectionGenLowNoThreshold_AK${R}PF.txt --KeepScale false \
      --PDFOutput Pdf/PhiCorrectionGenLowNoThresholdFit_AK${R}PF.pdf
   ./ExecuteText --DHFile Correction.dh --DHState MeowGenLowNoThreshold_R${R} \
      --Output Txt/PhiCorrectionGenLowNoThresholdScale_AK${R}PF.txt --KeepScale true \
      --PDFOutput Pdf/PhiCorrectionGenLowNoThresholdScaleFit_AK${R}PF.pdf
done




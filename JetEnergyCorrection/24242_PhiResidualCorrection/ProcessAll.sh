#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

for R in $JetR
do
   RValue=`DHQuery GlobalSetting.dh JetR $R`
   ./Execute --Input `ls Input/PbPbMCJEC_R${R}_* | head -n10 | tr '\n' ','` \
      --Output Root/MeowGenLowNoThreshold_R${R}.root \
      --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
      --JetR ${RValue} --MinPT 15 --BaseOnGen true
done




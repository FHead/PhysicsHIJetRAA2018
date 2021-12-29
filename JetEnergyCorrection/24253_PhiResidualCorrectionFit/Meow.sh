#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

for R in 4
do
   RValue=`DHQuery GlobalSetting.dh JetR $R`
   ./Execute --Input /tmp/chenyi/PbPbMCJEC_R${R}_CentralityInclusive.root \
      --Output Root/MeowGenLowNoThreshold_R${R}.root \
      --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
      --JetR ${RValue} --MinPT 15 --BaseOnGen true
done




#!/bin/sh

mkdir -p pdf
mkdir -p root

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

for R in $JetR
do
   for C in $Centrality
   do
      Skip=false
      if [[ "$C" == "0to10" ]]; then Skip=true; fi

      ./Execute --Input root/Output_R${R}_Centrality${C}.root \
         --Output pdf/Output_R${R}_Centrality${C}.pdf \
         --RootOutput graph/Output_R${R}_Centrality${C}.root \
		   --BinCount 100 --BinMagnification 10 --SkipFinalBin $Skip
   done
done

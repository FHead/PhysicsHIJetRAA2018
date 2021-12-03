#!/bin/sh

mkdir -p pdf
mkdir -p graph

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

JetR="6 7"

OrderDHFile=Order.dh

# default for everyone
for R in $JetR
do
   for C in $Centrality
   do
      DHSet $OrderDHFile R${R}_C${C} BinCount int 100
      DHSet $OrderDHFile R${R}_C${C} Magnification int 25
      DHSet $OrderDHFile R${R}_C${C} Skip string true
   done
done

# special cases
DHSet $OrderDHFile R8_C0to10  BinCount      int    30
DHSet $OrderDHFile R8_C0to10  Magnification int    5
DHSet $OrderDHFile R8_C10to30 BinCount      int    50
DHSet $OrderDHFile R8_C10to30 Magnification int    3
DHSet $OrderDHFile R9_C0to10  BinCount      int    30
DHSet $OrderDHFile R9_C0to10  Magnification int    5
DHSet $OrderDHFile R9_C10to30 BinCount      int    50
DHSet $OrderDHFile R9_C10to30 Magnification int    3
DHSet $OrderDHFile R9_C10to30 Skip          string false


for R in $JetR
do
   for C in $Centrality
   do
      Skip=`DHQuery $OrderDHFile R${R}_C${C} Skip | tr -d '"'`
      BinCount=`DHQuery $OrderDHFile R${R}_C${C} BinCount`
      BinMagnification=`DHQuery $OrderDHFile R${R}_C${C} Magnification`

      ./ExecuteMatch --Input root/Output_R${R}_Centrality${C}.root \
         --Output pdf/Output_R${R}_Centrality${C}.pdf \
         --RootOutput graph/Output_R${R}_Centrality${C}.root \
		   --BinCount $BinCount --BinMagnification $BinMagnification --SkipFinalBin $Skip
   done
done

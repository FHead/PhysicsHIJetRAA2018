#!/bin/bash

# PPChoice=20211229_FlatAOD
# PPChoice=20211229_FlatMiniAOD
PPChoice=20211230_FlatEOY

for i in Input/$PPChoice/*root Input/$PPChoice/*txt
do
   j=`basename $i`
   cp $i Input/${j/EOY}
done

for i in Input/PP*Fine*root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake false --DoBias false
done

for i in Input/PbPb*Fine*root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake false --DoBias false
done

for i in Input/*NominalFine.root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine/Cleaned}` --DHFile GlobalSetting.dh \
      --DoZeroing true --ZeroMin 0.33 --ZeroMax 3.00 --DoEarthquake false --DoBias false
   ./Execute --Input $i --Output Output/`basename ${i/Fine/CleanedStrong}` --DHFile GlobalSetting.dh \
      --DoZeroing true --ZeroMin 0.50 --ZeroMax 2.00 --DoEarthquake false --DoBias false
done

for i in Input/*NominalFine.root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine/Earthquake}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake true --EarthquakeMagnitude 1.0 --DoBias false
done

for i in Input/*NominalFine.root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine/BinBiasUp}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake false --DoBias true --GenBiasPower 1.0 --RecoBiasPower 0.0
   ./Execute --Input $i --Output Output/`basename ${i/Fine/BinBiasDown}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake false --DoBias true --GenBiasPower -1.0 --RecoBiasPower 0.0
done



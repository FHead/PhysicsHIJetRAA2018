#!/bin/bash

# for i in Input/*Fine*root
# do
#    ./Execute --Input $i --Output Output/`basename ${i/Fine}` --DHFile GlobalSetting.dh \
#       --DoZeroing false --DoEarthquake false --DoBias false
# done

# for i in Input/*NominalFine.root
# do
#    ./Execute --Input $i --Output Output/`basename ${i/Fine/Cleaned}` --DHFile GlobalSetting.dh \
#       --DoZeroing true --ZeroMin 0.33 --ZeroMax 3.00 --DoEarthquake false --DoBias false
# done

# for i in Input/*NominalFine.root
# do
#    ./Execute --Input $i --Output Output/`basename ${i/Fine/Earthquake}` --DHFile GlobalSetting.dh \
#       --DoZeroing false --DoEarthquake true --EarthquakeMagnitude 1.0 --DoBias false
# done

for i in Input/*NominalFine.root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine/BinBiasUp}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake false --DoBias true --GenBiasPower 1.0 --RecoBiasPower 0.0
   ./Execute --Input $i --Output Output/`basename ${i/Fine/BinBiasDown}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake false --DoBias true --GenBiasPower -1.0 --RecoBiasPower 0.0
done



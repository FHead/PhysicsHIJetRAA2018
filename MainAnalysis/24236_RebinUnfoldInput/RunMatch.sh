#!/bin/bash

Match=$1

for i in Input/*${Match}*Fine*root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine}` --DHFile GlobalSetting.dh \
      --DoZeroing false --DoEarthquake false --DoBias false
done


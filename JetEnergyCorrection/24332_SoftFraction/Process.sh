#!/bin/bash

for R in 2 5 7 9 # 1 2 3 4 5 6 7 8 9
do
   AngleMax=`DHQuery GlobalSetting.dh JetRMatch $R`
   ./Execute --Input Input/PPMCEOY_R${R}_CentralityInclusive.root --Output PPR${R}.pdf \
      --Root Output/PPMCEOY_R${R}_CentralityInclusive.root \
      --DRMax $AngleMax --Fraction 1.00
done


#!/bin/bash

for R in 1 2 3
do
   for PT in 100 110 120 140 150 160 170 180 190 200
   do
      ./ExecuteFit --Input MBInput/PbPbMBData_R${R}_CentralityInclusive.root \
         --PTMin $PT --PhiMin 2 --PhiMax -2 \
         --DHFile Dip.dh --DHState R${R}_CentralityAll_PT$PT
   done

   for PT in 100 110 120 140 150 160 170 180 190 200
   do
      ./ExecuteFit --Input MBInput/PbPbMBData_R${R}_CentralityInclusive.root \
         --PTMin $PT --PhiMin 2 --PhiMax -2 --CentralityMax 0.1 \
         --DHFile Dip.dh --DHState R${R}_Centrality0to10_PT$PT
   done
done


#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR`
Centrality=`DHQuery GlobalSetting.dh Global Centrality`

DHRemove GlobalSetting.dh EventSelection
for R in $JetR
do
   for C in $Centrality
   do
      DHSet GlobalSetting.dh EventSelection PbPbData_R${R}_Centrality${C}   float 1.0256
   done
done

for R in $JetR
do
   DHSet GlobalSetting.dh EventSelection PPData_R${R}_CentralityInclusive float 1.00
done





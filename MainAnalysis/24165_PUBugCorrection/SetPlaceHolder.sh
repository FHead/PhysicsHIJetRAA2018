#!/bin/bash

DHRemove GlobalSetting.dh PUBugCorrection
for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      DHSet GlobalSetting.dh PUBugCorrection PbPbData_R${R}_Centrality${C}   float 1.04
   done
done

for R in 1 2 3 4 5 6 7 8 9
do
   DHSet GlobalSetting.dh PUBugCorrection PPData_R${R}_CentralityInclusive float 1.00
done





#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

for R in $JetR
do
   for C in $Centrality
   do
      DHSet GlobalSetting.dh PriorToUse PbPbMCRho_R${R}_Centrality${C}_Default   string DefaultStep1
      DHSet GlobalSetting.dh PriorToUse PbPbData_R${R}_Centrality${C}_Default    string DefaultStep2
      DHSet GlobalSetting.dh PriorToUse PbPbMCRho_R${R}_Centrality${C}_Alternate string DefaultStep1
      DHSet GlobalSetting.dh PriorToUse PbPbData_R${R}_Centrality${C}_Alternate  string DefaultStep2
   done
      
   DHSet GlobalSetting.dh PriorToUse PPMC_R${R}_CentralityInclusive_Default     string DefaultStep1
   DHSet GlobalSetting.dh PriorToUse PPData_R${R}_CentralityInclusive_Default   string DefaultStep2
   DHSet GlobalSetting.dh PriorToUse PPMC_R${R}_CentralityInclusive_Alternate   string DefaultStep1
   DHSet GlobalSetting.dh PriorToUse PPData_R${R}_CentralityInclusive_Alternate string DefaultStep2
done


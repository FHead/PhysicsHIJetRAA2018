#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

MCStep=$1
DataStep=$2

for R in $JetR
do
   for C in $Centrality
   do
      DHSet GlobalSetting.dh PriorToUse PbPbMCRho_R${R}_Centrality${C}_Default   string $MCStep
      DHSet GlobalSetting.dh PriorToUse PbPbData_R${R}_Centrality${C}_Default    string $DataStep
      DHSet GlobalSetting.dh PriorToUse PbPbMCRho_R${R}_Centrality${C}_Alternate string $MCStep
      DHSet GlobalSetting.dh PriorToUse PbPbData_R${R}_Centrality${C}_Alternate  string $DataStep
   done
      
   DHSet GlobalSetting.dh PriorToUse PPMC_R${R}_CentralityInclusive_Default     string $MCStep
   DHSet GlobalSetting.dh PriorToUse PPData_R${R}_CentralityInclusive_Default   string $DataStep
   DHSet GlobalSetting.dh PriorToUse PPMC_R${R}_CentralityInclusive_Alternate   string $MCStep
   DHSet GlobalSetting.dh PriorToUse PPData_R${R}_CentralityInclusive_Alternate string $DataStep
done


#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

for R in $JetR
do
   for C in $Centrality
   do
      DHSet GlobalSetting.dh DefaultPrior PbPbData_R${R}_Centrality${C} string Power50
      DHSet GlobalSetting.dh DefaultPrior PbPbMCRho_R${R}_Centrality${C} string Power50
      DHSet GlobalSetting.dh AlternatePrior PbPbData_R${R}_Centrality${C} string Power40
      DHSet GlobalSetting.dh AlternatePrior PbPbMCRho_R${R}_Centrality${C} string Power40
   done
   
   DHSet GlobalSetting.dh DefaultPrior PPData_R${R}_CentralityInclusive string Power50
   DHSet GlobalSetting.dh DefaultPrior PPMC_R${R}_CentralityInclusive string Power50
   DHSet GlobalSetting.dh AlternatePrior PPData_R${R}_CentralityInclusive string Power40
   DHSet GlobalSetting.dh AlternatePrior PPMC_R${R}_CentralityInclusive string Power40
done

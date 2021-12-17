#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

for R in $JetR
do
   for C in $Centrality
   do
      F="PbPbData_R${R}_Centrality${C}_Nominal_DefaultStep1Prior.root"
      I=`DHQuery GlobalSetting.dh Iterations PbPbData_R${R}_Centrality${C}_Nominal_DefaultStep1Prior`
      DHSet GlobalSetting.dh Prior PbPbData_R${R}_Centrality${C}_DefaultStep2 string External
      DHSet GlobalSetting.dh Prior PbPbData_R${R}_Centrality${C}_DefaultStep2_File string "$F"
      DHSet GlobalSetting.dh Prior PbPbData_R${R}_Centrality${C}_DefaultStep2_Histogram string HUnfoldedBayes$I
   done
      
   F="PPData_R${R}_CentralityInclusive_Nominal_DefaultStep1Prior.root"
   I=`DHQuery GlobalSetting.dh Iterations PPData_R${R}_CentralityInclusive_Nominal_DefaultStep1Prior`
   DHSet GlobalSetting.dh Prior PPData_R${R}_CentralityInclusive_DefaultStep2 string External
   DHSet GlobalSetting.dh Prior PPData_R${R}_CentralityInclusive_DefaultStep2_File string "$F"
   DHSet GlobalSetting.dh Prior PPData_R${R}_CentralityInclusive_DefaultStep2_Histogram string HUnfoldedBayes$I
done


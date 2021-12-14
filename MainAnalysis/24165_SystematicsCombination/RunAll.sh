#!/bin/bash

DH=CancellationSetting.dh

# pp spectrum ratio
echo Processing PPRatio plot with R = 1.2 as reference
for R in 1 2 3 4 5 6 7 8
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R9_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R9_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R9_CentralityInclusive \
      --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration \
      --Global GlobalSystematics.dh
done

# pp spectrum ratio
echo Processing PPRatio plot with R = 1.0 as reference
for R in 1 2 3 4 5 6 7 9
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R8_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R8_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R8_CentralityInclusive \
      --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration \
      --Global GlobalSystematics.dh
done

# RAA
echo Processing RAA
for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PPData_R${R}_CentralityInclusive.root \
         --Output Output/RAA_R${R}_Centrality${C}.root \
         --DHFile $DH --State RAA_R${R}_Centrality${C} \
         --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration,HCentralityUp,HCentralityDown,HJECQuench \
         --Global GlobalSystematics.dh
   done
done

# RCP
echo Processing RCP
for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PbPbData_R${R}_Centrality50to90.root \
         --Output Output/RCP_R${R}_Centrality${C}.root \
         --DHFile $DH --State RCP_R${R}_Centrality${C} \
         --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration,HCentralityUp,HCentralityDown,HJECQuench \
         --Global GlobalSystematics.dh
   done
done


# pp spectrum ratio, but based on the smallest radius
echo Processing PPRatio plot with R = 0.15 as reference
for R in 2 3 4 5 6 7 8 9
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R1_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R1_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R1_CentralityInclusive \
      --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration \
      --Global GlobalSystematics.dh
done

# PbPb spectrum ratio, based on the smallest radius
echo Processing PbPbRatio plot with R = 0.15 as reference
for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PbPbData_R1_Centrality${C}.root \
         --Output Output/PbPbDataRatio_R${R}R1_Centrality${C}.root \
         --DHFile $DH --State PbPbDataRatio_R${R}R1_Centrality${C} \
         --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration,HCentralityUp,HCentralityDown,HJECQuench \
         --Global GlobalSystematics.dh
   done
done

# R-RAA, which is the ratio between the two spectrum ratios
echo Processing RAA-ratio plot with R = 0.15 as reference
for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      ./Execute --File1 Output/PbPbDataRatio_R${R}R1_Centrality${C}.root \
         --File2 Output/PPDataRatio_R${R}R1_CentralityInclusive.root \
         --Output Output/RRAA_R${R}R1_Centrality${C}.root \
         --DHFile $DH --State RRAA_R${R}R1_Centrality${C} \
         --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration,HCentralityUp,HCentralityDown,HJECQuench \
         --Global GlobalSystematics.dh
   done
done

# pp spectrum ratio, but based on R2
echo Processing PPRatio plot with R = 0.20 as reference
for R in 1 3 4 5 6 7 8 9
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R2_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R2_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R2_CentralityInclusive \
      --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration \
      --Global GlobalSystematics.dh
done

# PbPb spectrum ratio, based on R2
echo Processing PbPbRatio plot with R = 0.2 as reference
for R in 1 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PbPbData_R2_Centrality${C}.root \
         --Output Output/PbPbDataRatio_R${R}R2_Centrality${C}.root \
         --DHFile $DH --State PbPbDataRatio_R${R}R2_Centrality${C} \
         --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration,HCentralityUp,HCentralityDown,HJECQuench \
         --Global GlobalSystematics.dh
   done
done

# R-RAA, which is the ratio between the two spectrum ratios
echo Processing RAA-ratio plot with R = 0.20 as reference
for R in 1 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      ./Execute --File1 Output/PbPbDataRatio_R${R}R2_Centrality${C}.root \
         --File2 Output/PPDataRatio_R${R}R2_CentralityInclusive.root \
         --Output Output/RRAA_R${R}R2_Centrality${C}.root \
         --DHFile $DH --State RRAA_R${R}R2_Centrality${C} \
         --Include HJECUp,HJECDown,HJERUp,HJERDown,HPrior,HIteration,HCentralityUp,HCentralityDown,HJECQuench \
         --Global GlobalSystematics.dh
   done
done








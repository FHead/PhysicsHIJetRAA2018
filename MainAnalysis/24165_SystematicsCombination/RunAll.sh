#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR`
Centrality=`DHQuery GlobalSetting.dh Global Centrality`

DH=Systematics.dh

# JEC=HJECUp,HJECDown
JEC=HJECAggressiveUp,HJECAggressiveDown
JER=HJERUp,HJERDown
Unfold=HPrior,HIteration
Matrix=HBinBiasUp,HBinBiasDown,HEarthquake
AA=HQuench,HCentralityUp,HCentralityDown

PPList=$JEC,$JER,$Unfold,$Matrix
AAList=$JEC,$JER,$Unfold,$Matrix,$AA

# pp spectrum ratio
echo Processing PPRatio plot with R = 1.2 as reference
for R in $JetR
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R9_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R9_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R9_CentralityInclusive
done

# pp spectrum ratio
echo Processing PPRatio plot with R = 1.0 as reference
for R in $JetR
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R8_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R8_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R8_CentralityInclusive
done

# RAA
echo Processing RAA
for R in $JetR
do
   for C in $Centrality
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PPData_R${R}_CentralityInclusive.root \
         --Output Output/RAA_R${R}_Centrality${C}.root \
         --DHFile $DH --State RAA_R${R}_Centrality${C}
   done
done

# RCP with 50-90 as reference
echo Processing RCP with 50-90% as reference
for R in $JetR
do
   for C in $Centrality
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PbPbData_R${R}_Centrality50to90.root \
         --Output Output/RCP_R${R}_Centrality${C}.root \
         --DHFile $DH --State RCP_R${R}_Centrality${C}
   done
done


# pp spectrum ratio, but based on the smallest radius
echo Processing PPRatio plot with R = 0.15 as reference
for R in $JetR
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R1_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R1_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R1_CentralityInclusive
done

# PbPb spectrum ratio, based on the smallest radius
echo Processing PbPbRatio plot with R = 0.15 as reference
for R in $JetR
do
   for C in $Centrality
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PbPbData_R1_Centrality${C}.root \
         --Output Output/PbPbDataRatio_R${R}R1_Centrality${C}.root \
         --DHFile $DH --State PbPbDataRatio_R${R}R1_Centrality${C}
   done
done

# R-RAA, which is the ratio between the two spectrum ratios
echo Processing RAA-ratio plot with R = 0.15 as reference
for R in $JetR
do
   for C in $Centrality
   do
      ./Execute --File1 Output/PbPbDataRatio_R${R}R1_Centrality${C}.root \
         --File2 Output/PPDataRatio_R${R}R1_CentralityInclusive.root \
         --Output Output/RRAA_R${R}R1_Centrality${C}.root \
         --DHFile $DH --State RRAA_R${R}R1_Centrality${C}
   done
done

# pp spectrum ratio, but based on R2
echo Processing PPRatio plot with R = 0.20 as reference
for R in $JetR
do
   ./Execute --File1 Input/PPData_R${R}_CentralityInclusive.root \
      --File2 Input/PPData_R2_CentralityInclusive.root \
      --Output Output/PPDataRatio_R${R}R2_CentralityInclusive.root \
      --DHFile $DH --State PPDataRatio_R${R}R2_CentralityInclusive
done

# PbPb spectrum ratio, based on R2
echo Processing PbPbRatio plot with R = 0.2 as reference
for R in $JetR
do
   for C in $Centrality
   do
      ./Execute --File1 Input/PbPbData_R${R}_Centrality${C}.root \
         --File2 Input/PbPbData_R2_Centrality${C}.root \
         --Output Output/PbPbDataRatio_R${R}R2_Centrality${C}.root \
         --DHFile $DH --State PbPbDataRatio_R${R}R2_Centrality${C}
   done
done

# R-RAA, which is the ratio between the two spectrum ratios
echo Processing RAA-ratio plot with R = 0.20 as reference
for R in $JetR
do
   for C in $Centrality
   do
      ./Execute --File1 Output/PbPbDataRatio_R${R}R2_Centrality${C}.root \
         --File2 Output/PPDataRatio_R${R}R2_CentralityInclusive.root \
         --Output Output/RRAA_R${R}R2_Centrality${C}.root \
         --DHFile $DH --State RRAA_R${R}R2_Centrality${C}
   done
done








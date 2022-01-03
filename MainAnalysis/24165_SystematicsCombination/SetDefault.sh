#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR`
Centrality=`DHQuery GlobalSetting.dh Global Centrality`

DH=Systematics.dh

# pp spectrum ratio
for R in $JetR
do
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive JECUp_Correlation          float 0.85
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive JECDown_Correlation        float 0.85
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive JERUp_Correlation          float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive JERDown_Correlation        float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive IterationUp_Correlation    float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive IterationDown_Correlation  float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive Prior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive Iteration_Correlation      float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive CentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive CentralityDown_Correlation float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive JECQuench_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive BinBiasUp_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive BinBiasDown_Correlation    float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive Earthquake_Correlation     float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive Cleaned_Correlation        float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive CleanedStrong_Correlation  float 0.00
done

# pp spectrum ratio
for R in $JetR
do
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive JECUp_Correlation          float 0.85
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive JECDown_Correlation        float 0.85
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive JERUp_Correlation          float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive JERDown_Correlation        float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive IterationUp_Correlation    float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive IterationDown_Correlation  float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive Prior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive Iteration_Correlation      float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive CentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive CentralityDown_Correlation float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive JECQuench_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive BinBiasUp_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive BinBiasDown_Correlation    float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive Earthquake_Correlation     float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive Cleaned_Correlation        float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive CleanedStrong_Correlation  float 0.00
done

# RAA
for R in $JetR
do
   for C in $Centrality
   do
	   DHSet $DH RAA_R${R}_Centrality${C} JECUp_Correlation          float 0.50
   	DHSet $DH RAA_R${R}_Centrality${C} JECDown_Correlation        float 0.50
	   DHSet $DH RAA_R${R}_Centrality${C} JERUp_Correlation          float 0.50
   	DHSet $DH RAA_R${R}_Centrality${C} JERDown_Correlation        float 0.50
	   DHSet $DH RAA_R${R}_Centrality${C} IterationUp_Correlation    float 0.25
   	DHSet $DH RAA_R${R}_Centrality${C} IterationDown_Correlation  float 0.25
	   DHSet $DH RAA_R${R}_Centrality${C} Prior_Correlation          float 0.00
	   DHSet $DH RAA_R${R}_Centrality${C} Iteration_Correlation      float 0.25
	   DHSet $DH RAA_R${R}_Centrality${C} CentralityUp_Correlation   float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} CentralityDown_Correlation float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} JECQuench_Correlation      float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} BinBiasUp_Correlation      float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} BinBiasDown_Correlation    float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} Earthquake_Correlation     float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} Cleaned_Correlation        float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} CleanedStrong_Correlation  float 0.00
   done
done

# RCP
for R in $JetR
do
   for C in $Centrality
   do
	   DHSet $DH RCP_R${R}_Centrality${C} JECUp_Correlation          float 0.95
   	DHSet $DH RCP_R${R}_Centrality${C} JECDown_Correlation        float 0.95
	   DHSet $DH RCP_R${R}_Centrality${C} JERUp_Correlation          float 0.95
   	DHSet $DH RCP_R${R}_Centrality${C} JERDown_Correlation        float 0.95
	   DHSet $DH RCP_R${R}_Centrality${C} IterationUp_Correlation    float 0.50
   	DHSet $DH RCP_R${R}_Centrality${C} IterationDown_Correlation  float 0.50
	   DHSet $DH RCP_R${R}_Centrality${C} Prior_Correlation          float 0.00
	   DHSet $DH RCP_R${R}_Centrality${C} Iteration_Correlation      float 0.50
	   DHSet $DH RCP_R${R}_Centrality${C} CentralityUp_Correlation   float 0.00
   	DHSet $DH RCP_R${R}_Centrality${C} CentralityDown_Correlation float 0.00
   	DHSet $DH RCP_R${R}_Centrality${C} JECQuench_Correlation      float 0.90
   	DHSet $DH RCP_R${R}_Centrality${C} BinBiasUp_Correlation      float 0.90
   	DHSet $DH RCP_R${R}_Centrality${C} BinBiasDown_Correlation    float 0.90
   	DHSet $DH RCP_R${R}_Centrality${C} Earthquake_Correlation     float 0.90
   	DHSet $DH RCP_R${R}_Centrality${C} Cleaned_Correlation        float 0.90
   	DHSet $DH RCP_R${R}_Centrality${C} CleanedStrong_Correlation  float 0.90
   done

   for C in 50to90
   do
	   DHSet $DH RCP_R${R}_Centrality${C} JECUp_Correlation          float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} JECDown_Correlation        float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} JERUp_Correlation          float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} JERDown_Correlation        float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} IterationUp_Correlation    float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} IterationDown_Correlation  float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} Prior_Correlation          float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} Iteration_Correlation      float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} CentralityUp_Correlation   float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} CentralityDown_Correlation float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} JECQuench_Correlation      float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} BinBiasUp_Correlation      float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} BinBiasDown_Correlation    float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} Earthquake_Correlation     float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} Cleaned_Correlation        float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} CleanedStrong_Correlation  float 0.9999
   done
done

# pp spectrum ratio, but based on the smallest radius
for R in $JetR
do
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive JECUp_Correlation          float 0.95
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive JECDown_Correlation        float 0.95
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive JERUp_Correlation          float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive JERDown_Correlation        float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive IterationUp_Correlation    float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive IterationDown_Correlation  float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive Prior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive Iteration_Correlation      float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive CentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive CentralityDown_Correlation float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive JECQuench_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive BinBiasUp_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive BinBiasDown_Correlation    float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive Earthquake_Correlation     float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive Cleaned_Correlation        float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive CleanedStrong_Correlation  float 0.00
done

# PbPb spectrum ratio, based on the smallest radius
for R in $JetR
do
   for C in $Centrality
   do
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} JECUp_Correlation          float 0.95
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} JECDown_Correlation        float 0.95
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} JERUp_Correlation          float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} JERDown_Correlation        float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} IterationUp_Correlation    float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} IterationDown_Correlation  float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} Prior_Correlation          float 0.00
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} Iteration_Correlation      float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} CentralityUp_Correlation   float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} CentralityDown_Correlation float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} JECQuench_Correlation      float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} BinBiasUp_Correlation      float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} BinBiasDown_Correlation    float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} Earthquake_Correlation     float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} Cleaned_Correlation        float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} CleanedStrong_Correlation  float 0.00
   done
done

# R-RAA, which is the ratio between the two spectrum ratios
for R in $JetR
do
   for C in $Centrality
   do
      DHSet $DH RRAA_R${R}R1_Centrality${C} JECUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} JECDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} JERUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} JERDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} IterationUp_Correlation    float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} IterationDown_Correlation  float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} Prior_Correlation          float 0.00
      DHSet $DH RRAA_R${R}R1_Centrality${C} Iteration_Correlation      float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} CentralityUp_Correlation   float 0.05
      DHSet $DH RRAA_R${R}R1_Centrality${C} CentralityDown_Correlation float 0.05
      DHSet $DH RRAA_R${R}R1_Centrality${C} JECQuench_Correlation      float 0.00
      DHSet $DH RRAA_R${R}R1_Centrality${C} BinBiasUp_Correlation      float 0.00
      DHSet $DH RRAA_R${R}R1_Centrality${C} BinBiasDown_Correlation    float 0.00
      DHSet $DH RRAA_R${R}R1_Centrality${C} Earthquake_Correlation     float 0.00
      DHSet $DH RRAA_R${R}R1_Centrality${C} Cleaned_Correlation        float 0.00
      DHSet $DH RRAA_R${R}R1_Centrality${C} CleanedStrong_Correlation  float 0.00
   done
done

# pp spectrum ratio, based on R2
for R in $JetR
do
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive JECUp_Correlation          float 0.95
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive JECDown_Correlation        float 0.95
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive JERUp_Correlation          float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive JERDown_Correlation        float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive IterationUp_Correlation    float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive IterationDown_Correlation  float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive Prior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive Iteration_Correlation      float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive CentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive CentralityDown_Correlation float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive JECQuench_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive BinBiasUp_Correlation      float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive BinBiasDown_Correlation    float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive Earthquake_Correlation     float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive Cleaned_Correlation        float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive CleanedStrong_Correlation  float 0.00
done

# PbPb spectrum ratio, based on R2
for R in $JetR
do
   for C in $Centrality
   do
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} JECUp_Correlation          float 0.95
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} JECDown_Correlation        float 0.95
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} JERUp_Correlation          float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} JERDown_Correlation        float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} IterationUp_Correlation    float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} IterationDown_Correlation  float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} Prior_Correlation          float 0.00
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} Iteration_Correlation      float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} CentralityUp_Correlation   float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} CentralityDown_Correlation float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} JECQuench_Correlation      float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} BinBiasUp_Correlation      float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} BinBiasDown_Correlation    float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} Earthquake_Correlation     float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} Cleaned_Correlation        float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} CleanedStrong_Correlation  float 0.00
   done
done

# R-RAA, based on R2
for R in $JetR
do
   for C in $Centrality
   do
      DHSet $DH RRAA_R${R}R2_Centrality${C} JECUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} JECDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} JERUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} JERDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} IterationUp_Correlation    float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} IterationDown_Correlation  float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} Prior_Correlation          float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} Iteration_Correlation      float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} CentralityUp_Correlation   float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} CentralityDown_Correlation float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} JECQuench_Correlation      float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} BinBiasUp_Correlation      float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} BinBiasDown_Correlation    float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} Earthquake_Correlation     float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} Cleaned_Correlation        float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} CleanedStrong_Correlation  float 0.00
   done
done





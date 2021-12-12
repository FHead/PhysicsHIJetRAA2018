#!/bin/bash

DH=CancellationSetting.dh

# pp spectrum ratio
for R in 1 2 3 4 5 6 7 8
do
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJECUp_Correlation          float 0.85
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJECDown_Correlation        float 0.85
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJERUp_Correlation          float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJERDown_Correlation        float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HIterationUp_Correlation    float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HIterationDown_Correlation  float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HPrior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HIteration_Correlation      float 0.50
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HCentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HCentralityDown_Correlation float 0.00
done

# pp spectrum ratio
for R in 1 2 3 4 5 6 7
do
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HJECUp_Correlation          float 0.85
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HJECDown_Correlation        float 0.85
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HJERUp_Correlation          float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HJERDown_Correlation        float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HIterationUp_Correlation    float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HIterationDown_Correlation  float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HPrior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HIteration_Correlation      float 0.50
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HCentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R8_CentralityInclusive HCentralityDown_Correlation float 0.00
done

# RAA
for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   DHSet $DH RAA_R${R}_Centrality${C} HJECUp_Correlation          float 0.50
   	DHSet $DH RAA_R${R}_Centrality${C} HJECDown_Correlation        float 0.50
	   DHSet $DH RAA_R${R}_Centrality${C} HJERUp_Correlation          float 0.50
   	DHSet $DH RAA_R${R}_Centrality${C} HJERDown_Correlation        float 0.50
	   DHSet $DH RAA_R${R}_Centrality${C} HIterationUp_Correlation    float 0.25
   	DHSet $DH RAA_R${R}_Centrality${C} HIterationDown_Correlation  float 0.25
	   DHSet $DH RAA_R${R}_Centrality${C} HPrior_Correlation          float 0.00
	   DHSet $DH RAA_R${R}_Centrality${C} HIteration_Correlation      float 0.25
	   DHSet $DH RAA_R${R}_Centrality${C} HCentralityUp_Correlation   float 0.00
   	DHSet $DH RAA_R${R}_Centrality${C} HCentralityDown_Correlation float 0.00
   done
done

# RCP
for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50
   do
	   DHSet $DH RCP_R${R}_Centrality${C} HJECUp_Correlation          float 0.95
   	DHSet $DH RCP_R${R}_Centrality${C} HJECDown_Correlation        float 0.95
	   DHSet $DH RCP_R${R}_Centrality${C} HJERUp_Correlation          float 0.95
   	DHSet $DH RCP_R${R}_Centrality${C} HJERDown_Correlation        float 0.95
	   DHSet $DH RCP_R${R}_Centrality${C} HIterationUp_Correlation    float 0.50
   	DHSet $DH RCP_R${R}_Centrality${C} HIterationDown_Correlation  float 0.50
	   DHSet $DH RCP_R${R}_Centrality${C} HPrior_Correlation          float 0.00
	   DHSet $DH RCP_R${R}_Centrality${C} HIteration_Correlation      float 0.50
	   DHSet $DH RCP_R${R}_Centrality${C} HCentralityUp_Correlation   float 0.00
   	DHSet $DH RCP_R${R}_Centrality${C} HCentralityDown_Correlation float 0.00
   done

   for C in 50to90
   do
	   DHSet $DH RCP_R${R}_Centrality${C} HJECUp_Correlation          float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} HJECDown_Correlation        float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} HJERUp_Correlation          float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} HJERDown_Correlation        float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} HIterationUp_Correlation    float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} HIterationDown_Correlation  float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} HPrior_Correlation          float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} HIteration_Correlation      float 0.9999
	   DHSet $DH RCP_R${R}_Centrality${C} HCentralityUp_Correlation   float 0.9999
   	DHSet $DH RCP_R${R}_Centrality${C} HCentralityDown_Correlation float 0.9999
   done
done

# pp spectrum ratio, but based on the smallest radius
for R in 2 3 4 5 6 7 8 9
do
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJECUp_Correlation          float 0.95
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJECDown_Correlation        float 0.95
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJERUp_Correlation          float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJERDown_Correlation        float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HIterationUp_Correlation    float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HIterationDown_Correlation  float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HPrior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HIteration_Correlation      float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HCentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HCentralityDown_Correlation float 0.00
done

# PbPb spectrum ratio, based on the smallest radius
for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJECUp_Correlation          float 0.95
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJECDown_Correlation        float 0.95
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJERUp_Correlation          float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJERDown_Correlation        float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HIterationUp_Correlation    float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HIterationDown_Correlation  float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HPrior_Correlation          float 0.00
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HIteration_Correlation      float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HCentralityUp_Correlation   float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HCentralityDown_Correlation float 0.00
   done
done

# R-RAA, which is the ratio between the two spectrum ratios
for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJECUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJECDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJERUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJERDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HIterationUp_Correlation    float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HIterationDown_Correlation  float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HPrior_Correlation          float 0.00
      DHSet $DH RRAA_R${R}R1_Centrality${C} HIteration_Correlation      float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HCentralityUp_Correlation   float 0.05
      DHSet $DH RRAA_R${R}R1_Centrality${C} HCentralityDown_Correlation float 0.05
   done
done

# pp spectrum ratio, based on R2
for R in 1 3 4 5 6 7 8 9
do
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HJECUp_Correlation          float 0.95
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HJECDown_Correlation        float 0.95
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HJERUp_Correlation          float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HJERDown_Correlation        float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HIterationUp_Correlation    float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HIterationDown_Correlation  float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HPrior_Correlation          float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HIteration_Correlation      float 0.90
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HCentralityUp_Correlation   float 0.00
	DHSet $DH PPDataRatio_R${R}R2_CentralityInclusive HCentralityDown_Correlation float 0.00
done

# PbPb spectrum ratio, based on R2
for R in 1 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HJECUp_Correlation          float 0.95
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HJECDown_Correlation        float 0.95
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HJERUp_Correlation          float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HJERDown_Correlation        float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HIterationUp_Correlation    float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HIterationDown_Correlation  float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HPrior_Correlation          float 0.00
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HIteration_Correlation      float 0.90
	   DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HCentralityUp_Correlation   float 0.00
   	DHSet $DH PbPbDataRatio_R${R}R2_Centrality${C} HCentralityDown_Correlation float 0.00
   done
done

# R-RAA, based on R2
for R in 1 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      DHSet $DH RRAA_R${R}R2_Centrality${C} HJECUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} HJECDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} HJERUp_Correlation          float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} HJERDown_Correlation        float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} HIterationUp_Correlation    float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} HIterationDown_Correlation  float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} HPrior_Correlation          float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} HIteration_Correlation      float 0.25
      DHSet $DH RRAA_R${R}R2_Centrality${C} HCentralityUp_Correlation   float 0.00
      DHSet $DH RRAA_R${R}R2_Centrality${C} HCentralityDown_Correlation float 0.00
   done
done





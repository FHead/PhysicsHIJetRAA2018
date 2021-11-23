#!/bin/bash

DH=CancellationSetting.dh

# pp spectrum ratio
for R in 1 2 3 4 5 6 7 8
do
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJECUp_Correlation   float 0.95
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJECDown_Correlation float 0.95
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJERUp_Correlation   float 0.90
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJERDown_Correlation float 0.90
done

# RAA
for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   DHSet $DH RAA_R${R}_Centrality${C} HJECUp_Correlation   float 0.25
   	DHSet $DH RAA_R${R}_Centrality${C} HJECDown_Correlation float 0.25
	   DHSet $DH RAA_R${R}_Centrality${C} HJERUp_Correlation   float 0.25
   	DHSet $DH RAA_R${R}_Centrality${C} HJERDown_Correlation float 0.25
   done
done

# pp spectrum ratio, but based on the smallest radius
for R in 2 3 4 5 6 7 8 9
do
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJECUp_Correlation   float 0.95
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJECDown_Correlation float 0.95
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJERUp_Correlation   float 0.90
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJERDown_Correlation float 0.90
done

# PbPb spectrum ratio, based on the smallest radius
for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJECUp_Correlation   float 0.95
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJECDown_Correlation float 0.95
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJERUp_Correlation   float 0.90
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJERDown_Correlation float 0.90
   done
done

# R-RAA, which is the ratio between the two spectrum ratios
for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJECUp_Correlation   float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJECDown_Correlation float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJERUp_Correlation   float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJERDown_Correlation float 0.25
   done
done





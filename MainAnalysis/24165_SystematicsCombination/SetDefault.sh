#!/bin/bash

DH=CancellationSetting.dh

for R in 1 2 3 4 5 6 7 8
do
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJECUp_Correlation   float 0.80
	DHSet $DH PPDataRatio_R${R}R9_CentralityInclusive HJECDown_Correlation float 0.80
done

for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   DHSet $DH RAA_R${R}_Centrality${C} HJECUp_Correlation   float 0.25
   	DHSet $DH RAA_R${R}_Centrality${C} HJECDown_Correlation float 0.25
   done
done

for R in 2 3 4 5 6 7 8 9
do
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJECUp_Correlation   float 0.80
	DHSet $DH PPDataRatio_R${R}R1_CentralityInclusive HJECDown_Correlation float 0.80
done

for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJECUp_Correlation   float 0.80
   	DHSet $DH PbPbDataRatio_R${R}R1_Centrality${C} HJECDown_Correlation float 0.80
   done
done

for R in 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJECUp_Correlation   float 0.25
      DHSet $DH RRAA_R${R}R1_Centrality${C} HJECDown_Correlation float 0.25
   done
done





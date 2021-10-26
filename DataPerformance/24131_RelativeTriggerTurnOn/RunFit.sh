#!/bin/bash


for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90
   do
	   ./ExecuteFit --Input Result_R${R}_Centrality${C}.root --Output Plots_R${R}_Centrality${C}.pdf \
		   --DHFile GlobalSettingTest.dh --State PbPbTriggerTurnOn --KeyPrefix R${R}_Centrality${C}
   done
done

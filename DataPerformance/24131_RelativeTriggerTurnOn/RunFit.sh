#!/bin/bash


for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90 Inclusive
   do
      ./ExecuteFit --Input Result_R${R}_Centrality${C}.root --Output Plots_R${R}_Centrality${C}.pdf \
         --DHFile GlobalSetting.dh --State TriggerTurnOn --KeyPrefix R${R}_Centrality${C} \
         --FunctionChoice 1 --CutPercentage 0.99
   done
done

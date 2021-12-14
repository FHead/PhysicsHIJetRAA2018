#!/bin/bash

for R in 1 2 3 4 5 6 7 8 9
do
   for C in 0to10 10to30 30to50 50to90 Inclusive
   do
      ./Execute --DHFile GlobalSetting.dh --Base R${R}_Centrality${C} \
         --MinPT 150 \
         --DoTrigger true --TriggerPercentage 0.99
   done
done

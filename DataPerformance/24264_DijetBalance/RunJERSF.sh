#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
   for j in PbPbData2 # PPDataUL # PPDataEOY PPDataUL PbPbData PbPbData2
   do
      Cut=150
      if [[ "$j" == "PbPbData"* ]]; then
         Cut=`DHQuery GlobalSetting.dh TriggerTurnOn R${i}_Centrality50to90_Cut`
      fi

   	./ExecuteJER --Data Output/${j}R${i}.root --MC Output/${j/Data/MC}R${i}.root \
         --OutputBase Result/${j/Data}R${i} \
		   --PTMin $Cut --DPhiMin 2.7 --AlphaMax 0.30
   done
done


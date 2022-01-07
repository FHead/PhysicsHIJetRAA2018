#!/bin/bash

for i in 3 4 # 1 2 3 4 5 6 7 8 9
do
   for j in PPDataEOY # PPDataUL PbPbData
   do
	./ExecuteJER --Data Output/${j}R${i}.root --MC Output/${j/Data/MC}R${i}.root \
      --OutputBase Result/${j/Data}R${i} \
		--PTMin 150 --DPhiMin 2.8 --AlphaMax 0.30
   done
done

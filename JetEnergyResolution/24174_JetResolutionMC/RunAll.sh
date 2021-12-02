#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
   # ./Execute --Input PPMC_R${i}_CentralityInclusive.root --GenBin 200 --MinStats 2500 \
   #    --FractionEachSide 0.025 --Output PPMC_R${i}_CentralityInclusive.pdf --GenPTMin 30 \
   #    --DHFile PPMC_R${i}_CentralityInclusive.dh --Fraction 1.0
	./ExecutePlot --Input PPMC_R${i}_CentralityInclusive.dh \
      --Output PPMC_R${i}_CentralityInclusive_Summary.pdf
done

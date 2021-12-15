#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
   echo
   # ./Execute --Input ROOT/PPMC_R${i}_CentralityInclusive.root --GenBin 200 --MinStats 2500 \
   #    --FractionEachSide 0.025 --Output PDF/PPMC_R${i}_CentralityInclusive.pdf --GenPTMin 30 \
   #    --DHFile DHFile/PPMC_R${i}_CentralityInclusive.dh --Fraction 1.0
	# ./ExecutePlot --Input DHFile/PPMC_R${i}_CentralityInclusive.dh \
   #    --Output SummaryPDF/PPMC_R${i}_CentralityInclusive_Summary.pdf
done

for i in 1 2 3 4 5 6 7 8 9
do
   for j in 0to10 10to30 30to50 50to90
   do
      ./Execute --Input ROOT/PbPbMCRho_R${i}_Centrality${j}.root --GenBin 100 --MinStats 10000 \
         --FractionEachSide 0.025 --Output PDF/PbPbMCRho_R${i}_Centrality${j}.pdf --GenPTMin 30 \
         --DHFile DHFile/PbPbMCRho_R${i}_Centrality${j}.dh --Fraction 1.0
	   ./ExecutePlot --Input DHFile/PbPbMCRho_R${i}_Centrality${j}.dh \
         --Output SummaryPDF/PbPbMCRho_R${i}_Centrality${j}_Summary.pdf
   done
done

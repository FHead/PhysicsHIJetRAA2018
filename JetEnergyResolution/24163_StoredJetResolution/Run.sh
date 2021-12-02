#!/bin/sh

# for i in 1 2 3 4 5 6 7 8 9
# do
#    ./Execute --Input Input/PPMC_R${i}_CentralityInclusive.root --Fraction 0.05 \
#       --Output ResultPPR${i}.pdf --RootOutput ResultPPR${i}.root
# done

for j in 0to10 10to30 30to50 50to90
do
   for i in 1 2 3 4 5 6 7 8 9
   do
      R=`DHQuery GlobalSetting.dh JetR $i`
      ./Execute --Input Input/PbPbMCRho_R${i}_Centrality${j}.root --Fraction 1 \
         --Output ResultAAR${i}C${j}.pdf --RootOutput ResultAAR${i}C${j}.root
   done
done




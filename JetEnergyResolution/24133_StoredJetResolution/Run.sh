#!/bin/sh

# for i in 1 2 3 4 5 6 7 8 9
# do
#    ./Execute --Input Input/TestRunPPMC_R${i}_CentralityInclusive.root --Fraction 0.001 \
#       --Output ResultPPR${i}.pdf
# done

# for i in 1 2 3 4 5 6 7 8 9
# do
#    for j in 0to10 10to30 30to50 50to90
#    do
#       ./Execute --Input Input/TestRunMC_R${i}_Centrality${j}.root --Fraction 1 \
#          --Output ResultAAR${i}C${j}.pdf \
#          --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
#          --OnTheFlyJEC false
#    done
# done

# for j in 0to10 10to30 30to50 50to90
# do
#    for i in 1 2 3 4 5 6 7 8 9
#    do
#       R=`DHQuery GlobalSetting.dh JetR $i`
#       ./Execute --Input Input/TestRunMCJEC_R${i}_Centrality${j}.root --Fraction 1 \
#          --Output ResultOnTheFlyJECAAR${i}C${j}.pdf \
#          --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9 \
#          --OnTheFlyJEC true --JEC $ProjectBase/CommonCode/jec/Phi_24151/PhiCorrectionGen_AK${i}PF.txt --JetR ${R}
#    done
# done

for i in 1 2 3 4 5 6 7 8 9
do
   for j in 0to10 10to30 30to50 50to90
   do
      ./Execute --Input Input/TestRunMCJEC_R${i}_Centrality${j}.root --Fraction 1 \
         --Output ResultAANoPhiR${i}C${j}.pdf \
         --Exclusion -0.5,1.5,0,1,-2,-1,-1.8,-0.9
   done
done


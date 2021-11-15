#!/bin/sh

mkdir -p pdf
mkdir -p root

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

declare -A Order1=()
declare -A Order2=()

# default for everyone
for R in $JetR
do
   for C in $Centrality
   do
      Order1[R${R}_C${C}]=8
      Order2[R${R}_C${C}]=0
   done
done

# special cases
Order1[R1_C50to90]=3
Order2[R1_C50to90]=4

for R in $JetR
do
   for C in $Centrality
   do
      ./ExecuteFit --Input root/Output_R${R}_Centrality${C}.root \
         --Output pdf/Fit_R${R}_Centrality${C}.pdf \
         --DHFile GlobalSetting.dh --Key R${R}_Centrality${C} \
         --Order1 ${Order1[R${R}_C${C}]} --Order2 ${Order2[R${R}_C${C}]}
   done
done



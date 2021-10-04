#!/bin/sh

InputFile=$1
Tag=$2
Trigger=$3
IsMC=$4
IsPP=$5

Fraction=0.001

# JetR="1:0.15 2:0.20 3:0.30 4:0.40 5:0.50 6:0.60 7:0.70 8:0.80 9:0.90 10:1.00"
JetR="4:0.15 4:0.20 3:0.30 4:0.40 4:0.50 4:0.60 4:0.80 4:1.00 4:1.20"

if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive:-1:-1"
else
   Centrality="0to10:0.00:0.10 10to30:0.10:0.30 30to50:0.30:0.50 50to90:0.50:0.90"
fi

for R in $JetR
do
   RTag=`echo $R | cut -f 1 -d ":"`
   RValue=`echo $R | cut -f 2 -d ":"`

   JECBase="$ProjectBase/CommonCode/jec/"
   JECTag="Autumn18_HI_RAAV2_MC"

   if [[ "$IsMC" == "1" ]] && [[ "$IsPP" == "0" ]]; then
      JECTag="Autumn18_HI_RAAV2_MC"
   elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
      JECTag="Autumn18_HI_RAAV2_MC"
   elif [[ "$IsMC" == "1" ]] && [[ "$IsPP" == "1" ]]; then
      JECTag="Autumn18_HI_RAAV2_MC"
   elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "1" ]]; then
      JECTag="Autumn18_HI_RAAV2_MC"
   fi
      
   if [[ "$IsMC" == "1" ]]; then
      JEC=$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt
   else
      JEC="$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt","$JECBase/$JECTag/${JECTag}_L2L3Residual_AK${RTag}PF.txt"
   fi

   JEU=$JECBase/$JECTag/${JECTag}_Uncertainty_AK${RTag}PF.txt

   for C in $Centrality
   do
      CTag=`echo $C | cut -f 1 -d ":"`
      CMin=`echo $C | cut -f 2 -d ":"`
      CMax=`echo $C | cut -f 3 -d ":"`

      CheckCentrality=true
      if [[ "$CTag" == "Inclusive" ]]; then
         CheckCentrality=false
      fi

      echo "Running R = $RValue, Centrality = $CTag"

      ./Execute --Input $InputFile --Output Output/${Tag}_R${RTag}_Centrality${CTag}.root \
         --JetR $RValue --Jet "akCs${RTag}PFJetAnalyzer/t" --JEC ${JEC} --JEU ${JEU} \
         --Fraction $Fraction \
         --UseStoredGen true --Trigger $Trigger \
         --CheckCentrality $CheckCentrality --CentralityMin $CMin --CentralityMax $CMax
   done
done



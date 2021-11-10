#!/bin/sh

echo
echo 'Make sure you have project base properly set!!!'
echo

InputFile=$1
Tag=$2
Trigger=$3
IsMC=$4
IsPP=$5
Recluster=$6

echo $InputFile $Tag $Trigger $IsMC $IsPP $Recluster

Fraction=1

# JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
JetR="5 6 7 8 9"

for RTag in $JetR
do
   RValue=`DHQuery GlobalSetting.dh JetR $RTag`

   JECBase="$ProjectBase/CommonCode/jec/"
   JECTag="Autumn18_HI_RAAV2_MC"

   if [[ "$IsMC" == "1" ]] && [[ "$IsPP" == "0" ]]; then
      JECTag="Autumn18_HI_RAAV2_MC"
   elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
      JECTag="Autumn18_HI_RAAV2_MC"
   elif [[ "$IsMC" == "1" ]] && [[ "$IsPP" == "1" ]]; then
      JECTag="Spring18_ppRef5TeV_RAAV2_MC"
   elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "1" ]]; then
      JECTag="Spring18_ppRef5TeV_RAAV2_MC"
   fi
      
   if [[ "$IsMC" == "1" ]]; then
      JEC=$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt
   else
      JEC="$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt","$JECBase/$JECTag/${JECTag}_L2L3Residual_AK${RTag}PF.txt"
   fi

   JEU=$JECBase/$JECTag/${JECTag}_Uncertainty_AK${RTag}PF.txt

   echo $JEC
   echo $JEU

   BaselineCutAA=false
   if [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
      BaselineCutAA=true
   fi
   BaselineCutPP=false
   if [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "1" ]]; then
      BaselineCutPP=true
   fi

   echo "Running R = $RValue"

   if [[ "$Recluster" != "1" ]]; then
      ./Execute --Input $InputFile --Output Output/${Tag}_R${RTag}.root \
         --JetR $RValue --Jet "akCs${RTag}PFJetAnalyzer/t" --JEC ${JEC} --JEU ${JEU} \
         --Fraction $Fraction \
         --UseStoredGen true --UseStoredReco true --DoRecoSubtraction false --Trigger $Trigger \
         --PTMin 15 --GenPTMin 10 --DoBaselineCutPP $BaselineCutPP --DoBaselineCutAA $BaselineCutAA
   else
      ./Execute --Input $InputFile --Output Output/${Tag}_R${RTag}.root \
         --JetR $RValue --Jet "akCs${RTag}PFJetAnalyzer/t" --JEC ${JEC} --JEU ${JEU} \
         --Fraction $Fraction \
         --UseStoredGen false --UseStoredReco false --DoRecoSubtraction false --Trigger $Trigger \
         --PTMin 15 --GenPTMin 10 --DoBaselineCutPP $BaselineCutPP --DoBaselineCutAA $BaselineCutAA
   fi
done



#!/bin/bash

IsPP=0
IsMC=0
FileCount=20

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

if [[ "$IsPP" == "1" ]]
then
   TriggerBase=HLT_HIAK4PFJet60
   Trigger=HLT_HIAK4PFJet80
   Centrality="Inclusive"
   CutString="--DoBaselineCutAA false --DoBaselineCutPP true"
else   
   TriggerBase=HLT_HIPuAK4CaloJet80Eta5p1
   Trigger=HLT_HIPuAK4CaloJet100Eta5p1
   CutString="--DoBaselineCutAA true --DoBaselineCutPP false"
fi

for R in $JetR
do
   JetRValue=`DHQuery GlobalSetting.dh JetR ${R}`

   JECBase=$ProjectBase/CommonCode/jec/
   
   JetTree=
   JECTag=
   Recluster=false
   if [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
      Prefix=PbPbData
      JECTag="Autumn18_HI_RAAV2_MC"
      JECList="${JECBase}/${JECTag}/${JECTag}_L2Relative_AK${R}PF.txt","${JECBase}/${JECTag}/${JECTag}_L2L3Residual_AK${R}PF.txt"
      JetTree="akCs${R}PFJetAnalyzer/t"
      Recluster=false
   elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "1" ]]; then
      Prefix=PPData
      JECTag="Spring18_ppRef5TeV_RAAV2_MC"
      JECList="${JECBase}/${JECTag}/${JECTag}_L2Relative_AK${R}PF.txt","${JECBase}/Phi_24151/PhiCorrectionGen_AK${R}PF.txt","${JECBase}/${JECTag}/${JECTag}_L2L3Residual_AK${R}PF.txt"
      JetTree="ak${R}PFJetAnalyzer/t"
      Recluster=true
   fi

   LocationBase=`DHQuery GlobalSetting.dh Sample $Prefix$R | tr -d '"'`

   for C in $Centrality
   do
      CMin=`DHQuery GlobalSetting.dh CentralityMin $C`
      CMax=`DHQuery GlobalSetting.dh CentralityMax $C`
      
      time ./Execute --Input `find $LocationBase | grep root$ | head -n${FileCount} | tr '\n' ','` \
         --OutputBase Result_R${R}_Centrality${C} \
         --Base ${TriggerBase} \
         --Trigger ${Trigger} \
         --Jet "${JetTree}" --JetR ${JetRValue} \
         --Recluster ${Recluster} \
         --CentralityMin ${CMin} --CentralityMax ${CMax} \
         --EtaMin -2.0 --EtaMax 2.0 \
         ${CutString} \
         --JEC $JECList
   done
done



#!/bin/bash

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_11_2_1_patch2/src/
eval `scramv1 runtime -sh`
cd -
CodeBase=/afs/cern.ch/user/c/chenyi/PhysicsWorkspace/HIJetRAA2018/DataPerformance/24261_TriggerTurnOnBatchRun/
export ProjectBase=/afs/cern.ch/work/c/chenyi//PhysicsWorkspace/HIJetRAA2018/
export PATH=$PATH:/afs/cern.ch/user/c/chenyi/RootMacros/

FileList=$1    # list of files to run over
Tag=$2         # Tag to use for outputs
IsPP=$3        # 0 = PbPb, 1 = pp NonUL, 2 = pp UL
FromMB=$4      # if 1 use minimum bias
IsMC=0         # Only do data at the moment
TriggerBase=$5 # Base trigger
Trigger=$6     # Target trigger
JetR=$7        # What Jet R to run over
OutputBase=/eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIJetRAA2018/DataPerformance/24261_TriggerTurnOnBatchRun/


echo "Running with the following inputs"
echo "   FileList = $FileList"
echo "   Tag = $Tag"
echo "   IsPP = $IsPP"
echo "   FromMB = $FromMB"
echo "   IsMC = $IsMC"
echo "   TriggerBase = $TriggerBase"
echo "   Trigger = $Trigger"
echo "   JetR = $JetR"

Centrality=
if [[ "$Tag" == "PbPbData"* ]]; then
   Centrality=`DHQuery $CodeBase/GlobalSetting.dh Global Centrality`
elif [[ "$Tag" == "PbPbMBData"* ]]; then
   Centrality=Inclusive
elif [[ "$Tag" == "PPData"* ]]; then
   Centrality=Inclusive
fi

if [[ "$IsPP" != "0" ]]; then
   CutString="--DoBaselineCutAA false --DoBaselineCutPP true"
else
   CutString="--DoBaselineCutAA true --DoBaselineCutPP false"
fi

JetRValue=`DHQuery $CodeBase/GlobalSetting.dh JetR ${JetR}`

JECBase=$ProjectBase/CommonCode/jec/

JetTree=
JECTag=
Recluster=false
ReEvaluate=false
DoJetID=false
JetIDKeyBase="none"
if [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
   JECTag="Autumn18_HI_RAAV2_DATA"
   JECList="${JECBase}/${JECTag}/${JECTag}_L2Relative_AK${JetR}PF.txt","${JECBase}/Phi_24252/PhiCorrectionGenLowNoThreshold_AK${JetR}PF.txt","${JECBase}/${JECTag}/${JECTag}_L2L3Residual_AK${JetR}PF.txt"
   JetTree="akCs${JetR}PFJetAnalyzer/t"
   Recluster=false
   ReEvaluate=true
   DoJetID=true
   JetIDKeyBase=PbPbData_R${JetR}_Centrality0to10
elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "1" ]]; then
   JECTag="Spring18_ppRef5TeV_RAAV2_DATA"
   JECList="${JECBase}/${JECTag}/${JECTag}_L2Relative_AK${JetR}PF.txt","${JECBase}/${JECTag}/${JECTag}_L2L3Residual_AK${JetR}PF.txt"
   JetTree="ak${JetR}PFJetAnalyzer/t"
   Recluster=false
   ReEvaluate=false
   DoJetID=true
   JetIDKeyBase=PPData_R${JetR}_CentralityInclusive
elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "2" ]]; then
   JECTag="Summer20UL17_ppRef5TeV_RAAV1_DATA"
   JECList="${JECBase}/${JECTag}/${JECTag}_L2Relative_AK${JetR}PF.txt","${JECBase}/${JECTag}/${JECTag}_L2L3Residual_AK${JetR}PF.txt"
   JetTree="ak${JetR}PFJetAnalyzer/t"
   Recluster=false
   ReEvaluate=false
   DoJetID=true
   JetIDKeyBase=PPData_R${JetR}_CentralityInclusive
fi

for C in $Centrality
do
   CMin=`DHQuery $CodeBase/GlobalSetting.dh CentralityMin $C`
   CMax=`DHQuery $CodeBase/GlobalSetting.dh CentralityMax $C`

   time $CodeBase/Source/Execute --Input $FileList \
      --OutputBase Result_${Tag}_R${JetR}_Centrality${C} \
      --Base ${TriggerBase} \
      --Trigger ${Trigger} \
      --Jet "${JetTree}" --JetR ${JetRValue} \
      --Recluster ${Recluster} \
      --ReEvaluateCentrality $ReEvaluate --CentralityMin ${CMin} --CentralityMax ${CMax} \
      --EtaMin -2.0 --EtaMax 2.0 \
      ${CutString} \
      --DoJetID $DoJetID --JetIDKeyBase $JetIDKeyBase \
      --JEC $JECList --WriteTree true
   mv Result_*root $OutputBase/
done



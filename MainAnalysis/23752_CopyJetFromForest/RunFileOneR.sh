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
RTag=$7
DoPhiResidual=$8
DoExclusion=$9
Centrality=${10}

echo "Runing with the following"
echo "  Input = $InputFile"
echo "  Tag = $Tag"
echo "  Trigger = $Trigger"
echo "  IsMC = $IsMC (1 = yes, 0 = no)"
echo "  IsPP = $IsPP (0 = PbPb, 1 = NonUL pp, 2 = UL pp)"
echo "  Recluster = $Recluster (0 = no, 1 = yes)"
echo "  RTag = $RTag (what radius?  Goes from 1-9)"
echo "  DoPhiResidual = $DoPhiResidual (0 = no, 1 = yes)"
echo "  DoExclusion = $DoExclusion (0 = no, 1 = yes)"
echo "  Centrality = $Centrality"
echo

Fraction=1

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

DoRhoWeight=0
if [[ "$Centrality" == "default" ]]; then
   if [[ "$IsPP" != "0" ]]; then
      Centrality="Inclusive"
   else
      Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
   fi
elif [[ "$Centrality" == "rho" ]]; then
   if [[ "$IsPP" != "0" ]]; then
      Centrality="Inclusive"
   else
      Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
   fi
   DoRhoWeight=1
fi

RValue=`DHQuery GlobalSetting.dh JetR $RTag`

JECBase="$ProjectBase/CommonCode/jec/"
JECTag="Autumn18_HI_RAAV2_MC"
PhiTag="Phi_24151"

if [[ "$IsMC" == "1" ]] && [[ "$IsPP" == "0" ]]; then
   JECTag="Autumn18_HI_RAAV2_MC"
elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
   JECTag="Autumn18_HI_RAAV2_DATA"
elif [[ "$IsMC" == "1" ]] && [[ "$IsPP" == "1" ]]; then
   JECTag="Spring18_ppRef5TeV_RAAV2_MC"
elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "1" ]]; then
   JECTag="Spring18_ppRef5TeV_RAAV2_DATA"
elif [[ "$IsMC" == "1" ]] && [[ "$IsPP" == "2" ]]; then
   JECTag="Summer20UL17_ppRef5TeV_RAAV1_MC"
elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "2" ]]; then
   JECTag="Summer20UL17_ppRef5TeV_RAAV1_DATA"
fi

if [[ "$IsMC" == "1" ]] && [[ "$DoPhiResidual" == 1 ]]; then
   JEC="$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt","$JECBase/$PhiTag/PhiCorrectionGen_AK${RTag}PF.txt"
elif [[ "$IsMC" == "0" ]] && [[ "$DoPhiResidual" == 1 ]]; then
   JEC="$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt","$JECBase/$PhiTag/PhiCorrectionGen_AK${RTag}PF.txt","$JECBase/$JECTag/${JECTag}_L2L3Residual_AK${RTag}PF.txt"
elif [[ "$IsMC" == "1" ]] && [[ "$DoPhiResidual" == 0 ]]; then
   JEC="$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt"
elif [[ "$IsMC" == "0" ]] && [[ "$DoPhiResidual" == 0 ]]; then
   JEC="$JECBase/$JECTag/${JECTag}_L2Relative_AK${RTag}PF.txt","$JECBase/$JECTag/${JECTag}_L2L3Residual_AK${RTag}PF.txt"
fi

Exclusion=`DHQuery GlobalSetting.dh Binning JetExclusion`
if [[ "$DoExclusion" == 0 ]]; then
   Exclusion="99,100,99,100"
fi

JEU=$JECBase/$JECTag/${JECTag}_Uncertainty_AK${RTag}PF.txt

echo $JEC
echo $JEU

BaselineCutAA=false
if [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
   BaselineCutAA=true
fi
BaselineCutPP=false
if [[ "$IsMC" == "0" ]] && [[ "$IsPP" != "0" ]]; then
   BaselineCutPP=true
fi

for CTag in $Centrality
do
   CMin=`DHQuery GlobalSetting.dh CentralityMin $CTag`
   CMax=`DHQuery GlobalSetting.dh CentralityMax $CTag`

   CheckCentrality=true
   if [[ "$CTag" == "Inclusive" ]]; then
      CheckCentrality=false
   fi

   RhoKey="none"
   if [[ "$DoRhoWeight" == 1 ]]; then
      RhoKey="R${RTag}_Centrality${CTag}"
      CheckCentrality=false
   fi

   echo "Running R = $RValue, Centrality = $CTag"

   Stored=true
   if [[ "$Recluster" == "1" ]]; then
      Stored=false
   fi

   PTMin=15
   GenPTMin=10
   if [[ "$IsPP" == 0 ]] && [[ "$DoPhiResidual" == 0 ]] && [[ "$IsMC" == 1 ]]; then
      PTMin=0
      GenPTMin=0
   elif [[ "$IsPP" == 0 ]] && [[ "$RhoKey" != "none" ]] && [[ "$IsMC" == 1 ]]; then
      PTMin=40
      GenPTMin=40
   fi

   Jet="akCs4PFJetAnalyzer/t"
   if [[ "$IsPP" == 0 ]]; then
      Jet="akCs${RTag}PFJetAnalyzer/t"
   else
      Jet="ak${RTag}PFJetAnalyzer/t"
   fi

   JetIDTag=
   if [[ "$IsPP" == 0 ]]; then
      JetIDTag=PbPb
   else
      JetIDTag=PP
   fi
   if [[ "$IsMC" == 0 ]]; then
      JetIDTag=${JetIDTag}Data
   else
      JetIDTag=${JetIDTag}MC
   fi

   mkdir -p /tmp/chenyi/
   ./Execute --Input $InputFile --Output /tmp/chenyi/${Tag}_R${RTag}_Centrality${CTag}.root \
      --JetR $RValue --Jet "${Jet}" --JEC ${JEC} --JEU ${JEU} \
      --Fraction $Fraction --Exclusion "$Exclusion" \
      --UseStoredGen $Stored --UseStoredReco $Stored --DoRecoSubtraction false --Trigger $Trigger \
      --CheckCentrality $CheckCentrality --CentralityMin $CMin --CentralityMax $CMax \
      --PTMin $PTMin --GenPTMin $GenPTMin \
      --DoBaselineCutPP $BaselineCutPP --DoBaselineCutAA $BaselineCutAA \
      --DHFile GlobalSetting.dh --RhoKeyBase $RhoKey \
      --DoJetID true --JetIDKeyBase ${JetIDTag}_R${RTag}_Centrality${CTag}
   mv /tmp/chenyi/${Tag}_R${RTag}_Centrality${CTag}.root Output/${Tag}_R${RTag}_Centrality${CTag}.root
done



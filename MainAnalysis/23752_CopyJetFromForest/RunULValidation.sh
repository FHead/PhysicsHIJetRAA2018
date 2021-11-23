#!/bin/bash

mkdir ROOT

for R in 1 2 3 4 5 6 7 8 9
do
   JECBase=$ProjectBase/CommonCode/jec/
   JECTag=Spring18_ppRef5TeV_RAAV2_MC
   JEC=$JECBase/$JECTag/${JECTag}_L2Relative_AK${R}PF.txt

   RValue=`DHQuery GlobalSetting.dh JetR $R`

   ./Execute --Input HiForestMiniAOD.root --Output ROOT/ULFromJet_R${R}.root --Jet "ak${R}PFJetAnalyzer/t" \
      --JetR $RValue --CheckCentrality false --UseStoredGen false --UseStoredReco true \
      --DoRecoSubtraction false --JEC ${JEC} --PTMin 5
   ./Execute --Input HiForestMiniAOD.root --Output ROOT/ULFromPF_R${R}.root --Jet "ak${R}PFJetAnalyzer/t" \
      --JetR $RValue --CheckCentrality false --UseStoredGen false --UseStoredReco false \
      --PF "particleFlowAnalyser/pftree" --JEC ${JEC} --PTMin 5
done


IsPP=0
IsMC=0

PPMCBase=/eos/cms/store/group/phys_heavyions/chenyi///pp2017/Forest/QCD_pThat-15_Dijet_TuneCP5_5p02TeV_pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV_v1-v1/AODSIM/ManualRun22651//
PPDataBase=/eos/cms/store/group/phys_heavyions/chenyi///pp2017/Forest/HighEGJet/Run2017G-17Nov2017-v2/AOD/HighEGJet/20201111FirstRun/201111_162524/0000//
PbPbMCBase=/eos/cms/store/group/phys_heavyions/chenyi////PbPb2018/Forest/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/DefaultPbPbMCForJetRAARetry/211009_142235/0000/
PbPbDataBase=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAARetry3/211015_104302/

declare -A Location=()
for i in `seq 1 9`
do
   Location[PPMC$i]=$PPMCBase
   Location[PPData$i]=$PPDataBase
   Location[PbPbMC$i]=$PbPbMCBase
done

Location[PbPbData1]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12/211020_104744/0000/
Location[PbPbData2]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit12/211020_104744/0000/
Location[PbPbData3]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35/211020_104754/0000/
Location[PbPbData4]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35/211020_104754/0000/
Location[PbPbData5]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit35/211020_104754/0000/
Location[PbPbData6]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67/211020_104804/0000/
Location[PbPbData7]=/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIHardProbes/DefaultPbPbDataForJetRAASplit67/211020_104804/0000/
Location[PbPbData8]=$PbPbDataBase
Location[PbPbData9]=$PbPbDataBase

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

for R in $JetR
do
   JECBase=$ProjectBase/CommonCode/jec/
   
   JECTag=
   if [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "0" ]]; then
      Prefix=PbPbData
      JECTag="Autumn18_HI_RAAV2_MC"
   elif [[ "$IsMC" == "0" ]] && [[ "$IsPP" == "1" ]]; then
      Prefix=PPData
      JECTag="Spring18_ppRef5TeV_RAAV2_MC"
   fi

   for C in $Centrality
   do
      CMin=`DHQuery GlobalSetting.dh CentralityMin $C`
      CMax=`DHQuery GlobalSetting.dh CentralityMax $C`
      
      time ./Execute --Input `ls ${Location[$Prefix$R]}/*root | head -n20 | tr '\n' ','` \
         --OutputBase Result_R${R}_Centrality${C} \
         --Base HLT_HIPuAK4CaloJet80Eta5p1 \
         --Trigger HLT_HIPuAK4CaloJet100Eta5p1 \
         --Jet "akCs1PFJetAnalyzer/t" \
         --CentralityMin ${CMin} --CentralityMax ${CMax} \
         --EtaMin -2.0 --EtaMax 2.0 \
         --DoBaselineCutAA true --DoBaselineCutPP false \
         --JEC "${JECBase}/${JECTag}/${JECTag}_L2Relative_AK${R}PF.txt","${JECBase}/${JECTag}/${JECTag}_L2L3Residual_AK${R}PF.txt"
   done
done



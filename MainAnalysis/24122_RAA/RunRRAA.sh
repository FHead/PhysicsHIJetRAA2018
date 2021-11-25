#!/bin/bash

PPState=PPData
AAState=PbPbData

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

for R in $JetR
do
   if [[ $R == "1" ]]; then
      continue
   fi

   PPFile=Root/RAAR1.root
   PPCurve0=RAA_R1_Centrality0to10
   PPCurve1=RAA_R1_Centrality10to30
   PPCurve2=RAA_R1_Centrality30to50
   PPCurve3=RAA_R1_Centrality50to90
   AAFile=Root/RAAR${R}.root
   AACurve0=RAA_R${R}_Centrality0to10
   AACurve1=RAA_R${R}_Centrality10to30
   AACurve2=RAA_R${R}_Centrality30to50
   AACurve3=RAA_R${R}_Centrality50to90
   SysFile0=CombinedSystematics/RRAA_R${R}R1_Centrality0to10.root
   SysFile1=CombinedSystematics/RRAA_R${R}R1_Centrality10to30.root
   SysFile2=CombinedSystematics/RRAA_R${R}R1_Centrality30to50.root
   SysFile3=CombinedSystematics/RRAA_R${R}R1_Centrality50to90.root
   CLabel0=R${R}R1_Centrality0to10
   CLabel1=R${R}R1_Centrality10to30
   CLabel2=R${R}R1_Centrality30to50
   CLabel3=R${R}R1_Centrality50to90

   PPLumi=`DHQuery GlobalSetting.dh Lumi ${PPState}_R${R}_CentralityInclusive_BRIL | tr -d '"' | DivideConst 1000000`
   PPLumiUnit="pb^{-1}"
   AALumi=`DHQuery GlobalSetting.dh Lumi ${AAState}_R${R}_Centrality0to10_BRIL | tr -d '"'`
   AALumiUnit="#mub^{-1}"

   RValue1=`DHQuery GlobalSetting.dh JetR 1`
   RValue2=`DHQuery GlobalSetting.dh JetR $R`
   YLabel="R_{AA} Ratio: (R = $RValue2) / (R = $RValue1)"

   ./Execute \
      --PP ${PPFile},${PPFile},${PPFile},${PPFile} \
      --PPName $PPCurve0,$PPCurve1,$PPCurve2,$PPCurve3 \
      --AA ${AAFile},${AAFile},${AAFile},${AAFile} \
      --AAName $AACurve0,$AACurve1,$AACurve2,$AACurve3 \
      --Systematics ${SysFile0},${SysFile1},${SysFile2},${SysFile3} \
      --Labels "0-10%","10-30%","30-50%","50-90%" \
      --FinalOutput Plots/RRAAR${R}.pdf \
      --RootOutput Root/RRAAR${R}.root \
      --CurveLabel $CLabel0,$CLabel1,$CLabel2,$CLabel3 \
      --WorldXMin 158 --WorldXMax 1500 --WorldYMin 0.0 --WorldYMax 2.0 --LogX true --LogY false \
      --XLabel "Jet p_{T} (GeV)" --YLabel "$YLabel" \
      --XAxisSpacing 505 --YAxisSpacing 505 \
      --LegendX 0.7 --LegendY 0.45 --LegendSize 0.045 \
      --PPLumi ${PPLumi} --AALumi ${AALumi} --PPLumiUnit ${PPLumiUnit} --AALumiUnit ${AALumiUnit}
done



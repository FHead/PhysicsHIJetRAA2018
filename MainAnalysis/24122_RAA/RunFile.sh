#!/bin/bash

PPState=$1
PPSuffix=$2
AAState=$3
AASuffix=$4
OutputTag=$5

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

for R in $JetR
do
   PPFile=SpectraRoot/${PPState}_R${R}_CentralityInclusive_${PPSuffix}.root
   PPCurve=Result0
   AAFile0=SpectraRoot/${AAState}_R${R}_Centrality0to10_${AASuffix}.root
   AAFile1=SpectraRoot/${AAState}_R${R}_Centrality10to30_${AASuffix}.root
   AAFile2=SpectraRoot/${AAState}_R${R}_Centrality30to50_${AASuffix}.root
   AAFile3=SpectraRoot/${AAState}_R${R}_Centrality50to90_${AASuffix}.root
   AACurve0=Result0
   AACurve1=Result0
   AACurve2=Result0
   AACurve3=Result0
   SysFile0=CombinedSystematics/RAA_R${R}_Centrality0to10.root
   SysFile1=CombinedSystematics/RAA_R${R}_Centrality10to30.root
   SysFile2=CombinedSystematics/RAA_R${R}_Centrality30to50.root
   SysFile3=CombinedSystematics/RAA_R${R}_Centrality50to90.root
   CLabel0=R${R}_Centrality0to10
   CLabel1=R${R}_Centrality10to30
   CLabel2=R${R}_Centrality30to50
   CLabel3=R${R}_Centrality50to90

   PPLumi=`DHQuery GlobalSetting.dh Lumi ${PPState}_R${R}_CentralityInclusive_BRIL | tr -d '"' | DivideConst 1000000`
   PPLumiUnit="pb^{-1}"
   AALumi=`DHQuery GlobalSetting.dh Lumi ${AAState}_R${R}_Centrality0to10_BRIL | tr -d '"' | DivideConst 1000`
   AALumiUnit="nb^{-1}"

   if [[ "$PPLumi" == "" ]]; then
      PPLumi=0
   fi
   if [[ "$PbPbLumi" == "" ]]; then
      PbPbLumi=0
   fi

   RValue=`DHQuery GlobalSetting.dh JetR $R`
   YLabel="R_{AA} (R = $RValue)"

   if [[ "$OutputTag" == "" ]]; then
      OutputTag=PP${PPSuffix}_AA${AASuffix}
   fi

   ./Execute \
      --PP ${PPFile},${PPFile},${PPFile},${PPFile} \
      --PPName $PPCurve,$PPCurve,$PPCurve,$PPCurve \
      --AA ${AAFile0},${AAFile1},${AAFile2},${AAFile3} \
      --AAName $AACurve0,$AACurve1,$AACurve2,$AACurve3 \
      --Systematics ${SysFile0},${SysFile1},${SysFile2},${SysFile3} \
      --Labels "0-10%","10-30%","30-50%","50-90%" \
      --FinalOutput Plots/RAAR${R}_${OutputTag}.pdf \
      --RootOutput Root/RAAR${R}_${OutputTag}.root \
      --CurveLabel $CLabel0,$CLabel1,$CLabel2,$CLabel3 \
      --WorldXMin 158 --WorldXMax 1500 --WorldYMin 0.0 --WorldYMax 1.2 --LogX true --LogY false \
      --XLabel "Jet p_{T} (GeV)" --YLabel "$YLabel" \
      --XAxisSpacing 505 --YAxisSpacing 505 \
      --LegendX 0.7 --LegendY 0.45 --LegendSize 0.045 \
      --PPLumi ${PPLumi} --AALumi ${AALumi} --PPLumiUnit ${PPLumiUnit} --AALumiUnit ${AALumiUnit}
done



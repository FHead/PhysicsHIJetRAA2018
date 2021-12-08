#!/bin/bash

PPState=PPData
AAState=PbPbData

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

for R in $JetR
do
   PPFile0=SpectraRoot/${AAState}_R${R}_Centrality50to90.root
   PPFile1=SpectraRoot/${AAState}_R${R}_Centrality50to90.root
   PPFile2=SpectraRoot/${AAState}_R${R}_Centrality50to90.root
   PPFile3=SpectraRoot/${AAState}_R${R}_Centrality50to90.root
   PPCurve0=Result0
   PPCurve1=Result0
   PPCurve2=Result0
   PPCurve3=Result0
   AAFile0=SpectraRoot/${AAState}_R${R}_Centrality0to10.root
   AAFile1=SpectraRoot/${AAState}_R${R}_Centrality10to30.root
   AAFile2=SpectraRoot/${AAState}_R${R}_Centrality30to50.root
   AAFile3=SpectraRoot/${AAState}_R${R}_Centrality50to90.root
   AACurve0=Result0
   AACurve1=Result0
   AACurve2=Result0
   AACurve3=Result0
   SysFile0=CombinedSystematics/RCP_R${R}_Centrality0to10.root
   SysFile1=CombinedSystematics/RCP_R${R}_Centrality10to30.root
   SysFile2=CombinedSystematics/RCP_R${R}_Centrality30to50.root
   SysFile3=CombinedSystematics/RCP_R${R}_Centrality50to90.root
   CLabel0=R${R}_Centrality0to10
   CLabel1=R${R}_Centrality10to30
   CLabel2=R${R}_Centrality30to50
   CLabel3=R${R}_Centrality50to90

   PPLumi=`DHQuery GlobalSetting.dh Lumi ${PPState}_R${R}_CentralityInclusive_BRIL | tr -d '"' | DivideConst 1000000`
   PPLumiUnit="pb^{-1}"
   AALumi=`DHQuery GlobalSetting.dh Lumi ${AAState}_R${R}_Centrality0to10_BRIL | tr -d '"' | DivideConst 1000`
   AALumiUnit="nb^{-1}"

   RValue=`DHQuery GlobalSetting.dh JetR $R`
   YLabel="R_{CP} (R = $RValue)"

   ./Execute \
      --PP ${PPFile0},${PPFile1},${PPFile2} \
      --PPName $PPCurve0,$PPCurve1,$PPCurve2 \
      --AA ${AAFile0},${AAFile1},${AAFile2} \
      --AAName $AACurve0,$AACurve1,$AACurve2 \
      --Systematics ${SysFile0},${SysFile1},${SysFile2} \
      --Labels "0-10%","10-30%","30-50%" \
      --FinalOutput Plots/RCPR${R}.pdf \
      --RootOutput Root/RCPR${R}.root \
      --CurveLabel $CLabel0,$CLabel1,$CLabel2 \
      --WorldXMin 158 --WorldXMax 1500 --WorldYMin 0.0 --WorldYMax 1.2 --LogX true --LogY false \
      --XLabel "Jet p_{T} (GeV)" --YLabel "$YLabel" \
      --XAxisSpacing 505 --YAxisSpacing 505 \
      --LegendX 0.7 --LegendY 0.45 --LegendSize 0.045 \
      --PPLumi ${PPLumi} --AALumi ${AALumi} --PPLumiUnit ${PPLumiUnit} --AALumiUnit ${AALumiUnit}
done



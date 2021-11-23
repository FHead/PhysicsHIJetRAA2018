#!/bin/bash

PPState=PPData
AAState=PbPbData

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

for R in $JetR
do
   PPFile=SpectraRoot/${PPState}_R${R}_CentralityInclusive.root
   AAFile0=SpectraRoot/${AAState}_R${R}_Centrality0to10.root
   AAFile1=SpectraRoot/${AAState}_R${R}_Centrality10to30.root
   AAFile2=SpectraRoot/${AAState}_R${R}_Centrality30to50.root
   AAFile3=SpectraRoot/${AAState}_R${R}_Centrality50to90.root
   SysFile0=CombinedSystematics/RAA_R${R}_Centrality0to10.root
   SysFile1=CombinedSystematics/RAA_R${R}_Centrality10to30.root
   SysFile2=CombinedSystematics/RAA_R${R}_Centrality30to50.root
   SysFile3=CombinedSystematics/RAA_R${R}_Centrality50to90.root

   PPLumi=`DHQuery GlobalSetting.dh Lumi ${PPState}_R${R}_CentralityInclusive_BRIL | tr -d '"' | DivideConst 1000000`
   PPLumiUnit="pb^{-1}"
   AALumi=`DHQuery GlobalSetting.dh Lumi ${AAState}_R${R}_Centrality0to10_BRIL | tr -d '"'`
   AALumiUnit="#mub^{-1}"

   ./Execute \
      --PP ${PPFile},${PPFile},${PPFile},${PPFile} \
      --AA ${AAFile0},${AAFile1},${AAFile2},${AAFile3} \
      --Systematics ${SysFile0},${SysFile1},${SysFile2},${SysFile3} \
      --Labels "0-10%","10-30%","30-50%","50-90%" \
      --FinalOutput Plots/RAAR${R}.pdf \
      --WorldXMin 158 --WorldXMax 1500 --WorldYMin 0.0 --WorldYMax 1.2 --LogX true --LogY false \
      --XLabel "Jet p_{T} (GeV)" --YLabel "R_{AA}" \
      --XAxisSpacing 505 --YAxisSpacing 505 \
      --LegendX 0.7 --LegendY 0.45 --LegendSize 0.045 \
      --PPLumi ${PPLumi} --AALumi ${AALumi} --PPLumiUnit ${PPLumiUnit} --AALumiUnit ${AALumiUnit}
done



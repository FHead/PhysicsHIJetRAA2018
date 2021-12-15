#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

OfficialCount=11775759052
OfficialLumi=1695.62

for R in $JetR
do
   for C in $Centrality
   do
      echo $R $C
      # PbPbData_R9_Centrality30to50

      Lumi=`DHQuery GlobalSetting.dh Lumi PbPbData_R${R}_Centrality${C}_BRIL | tr -d '"'`
      CMin=`DHQuery GlobalSetting.dh CentralityMin $C`
      CMax=`DHQuery GlobalSetting.dh CentralityMax $C`
      CRange=`echo $CMax | SubtractConst $CMin`

      echo "Lumi: $Lumi $OfficialLumi"
      echo "CRange: $CMin $CMax $CRange"

      NMB=`echo $OfficialCount | DivideConst $OfficialLumi | MultiplyConst $Lumi`
      NMB=`echo $NMB | DivideConst 0.9 | MultiplyConst $CRange`

      DHSet GlobalSetting.dh MBCount PbPbData_R${R}_Centrality${C}_OfficialCount float $NMB
   done
done

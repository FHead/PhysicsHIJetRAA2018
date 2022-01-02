#!/bin/bash

JSON=$1

# example: Input/PbPbData_R7_Centrality50to90_Nominal_JSON.txt

Tag=`basename $JSON | sed "s/_NominalFine_JSON.txt//g"`

CentralityTag=`echo $Tag | egrep Centrality[0-9]*to[0-9]* -o | sed "s/Centrality//g"`

# echo $Tag
# echo $CentralityTag

./Execute --JSON $JSON \
   --MB1 MergedMB0.root \
   --HLTMatch1 "HLT_HI","MinimumBias_","part0" \
   --L1Match1 "L1_MinimumBiasHF1_AND_BptxAND" \
   --MB2 MergedMB1.root \
   --HLTMatch2 "HLT_HI","MinimumBias_","part1" \
   --L1Match2 "L1_MinimumBiasHF1_AND_BptxAND" \
   --MB3 MergedMB1.root \
   --HLTMatch3 "HLT_HI","MinimumBias_","part2" \
   --L1Match3 "L1_MinimumBiasHF1_AND_BptxAND" \
   --DHFile GlobalSetting.dh --State MBCount --Tag ${Tag} --CentralityTag $CentralityTag





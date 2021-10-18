#!/bin/bash

JSON=$1

# example: Input/TestRunData_R7_Centrality50to90_Nominal_JSON.txt

Tag=`basename $JSON | sed "s/_Nominal_JSON.txt//g"`

CentralityTag=`echo $Tag | egrep Centrality[0-9]*to[0-9]* -o | sed "s/Centrality//g"`

# echo $Tag
# echo $CentralityTag

./Execute --JSON $JSON \
   --MB MergedMB.root \
   --HLTMatch "HLT_HIMinimumBias_","part0" \
   --L1Match "L1_MinimumBiasHF1_AND_BptxAND" \
   --DHFile GlobalSetting.dh --State MBCount --Tag ${Tag} --CentralityTag $CentralityTag





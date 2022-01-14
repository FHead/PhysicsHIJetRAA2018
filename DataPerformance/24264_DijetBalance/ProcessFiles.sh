#!/bin/bash

for i in 1 2 3 4 5 6 7 8 9
do
   echo "Running R$i"

   # cp Input/PbPbData_R${i}_Centrality50to90.root /tmp/chenyi/Input.root
   # ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 0
   # cp /tmp/chenyi/Output.root Output/PbPbDataR${i}.root

   # cp Input/PbPbMC_R${i}_Centrality50to90.root /tmp/chenyi/Input.root
   # ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 1
   # cp /tmp/chenyi/Output.root Output/PbPbMCR${i}.root
   
   cp Input/PbPbData_R${i}_Centrality70to90.root /tmp/chenyi/Input.root
   ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 0
   cp /tmp/chenyi/Output.root Output/PbPbData2R${i}.root

   cp Input/PbPbMC_R${i}_Centrality70to90.root /tmp/chenyi/Input.root
   ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 1
   cp /tmp/chenyi/Output.root Output/PbPbMC2R${i}.root
   
   # cp Input/PPDataEOY_R${i}_CentralityInclusive.root /tmp/chenyi/Input.root
   # ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 0
   # cp /tmp/chenyi/Output.root Output/PPDataEOYR${i}.root

   # cp Input/PPMCEOY_R${i}_CentralityInclusive.root /tmp/chenyi/Input.root
   # ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 1
   # cp /tmp/chenyi/Output.root Output/PPMCEOYR${i}.root
   
   # cp Input/PPData_R${i}_CentralityInclusive.root /tmp/chenyi/Input.root
   # ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 0
   # cp /tmp/chenyi/Output.root Output/PPDataULR${i}.root

   # cp Input/PPMC_R${i}_CentralityInclusive.root /tmp/chenyi/Input.root
   # ./Execute --Input /tmp/chenyi/Input.root --Output /tmp/chenyi/Output.root --IsMC 1
   # cp /tmp/chenyi/Output.root Output/PPMCULR${i}.root
done

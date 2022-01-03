#!/bin/bash

for i in HighEGJet/*/*root
do
   echo $i
   
   ./Execute --Input $i \
      --Directories ggHiNtuplizer,ggHiNtuplizerGED,ak4CaloJetAnalyzer,ak3PFJetAnalyzer,ak4PFJetAnalyzer
done

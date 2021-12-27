#!/bin/bash

Prefix=$1
IsPP=$2

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

MCPrefix=$1
if [[ "$Prefix" == "PbPbData" ]]; then
   MCPrefix="PbPbMCRho"
else
   MCPrefix="PPMC"
fi

for R in $JetR
do
   for C in $Centrality
   do
      MCNP="`DHQuery GlobalSetting.dh PriorToUse ${MCPrefix}_R${R}_Centrality${C}_Default | tr -d '"'`Prior"
      NP="`DHQuery GlobalSetting.dh PriorToUse ${Prefix}_R${R}_Centrality${C}_Default | tr -d '"'`Prior"
      AP="`DHQuery GlobalSetting.dh PriorToUse ${Prefix}_R${R}_Centrality${C}_Alternate | tr -d '"'`Prior"

      RC="R${R}_Centrality${C}"
      PRC="${Prefix}_${RC}"
      PRCN="Input/${PRC}_Nominal_${NP}.root"

      MCPRC="${MCPrefix}_${RC}"
      MCPRCN="Input/${MCPRC}_Nominal_${MCNP}.root"
      MCPRCToy="Input/${MCPRC}_Nominal_Toy_${MCNP}.root"

      Method=`DHQuery GlobalSetting.dh MethodToUse ${Prefix}_R${R}_Centrality${C}_Default | tr -d '"'`
      if [[ "$Method" == "Bayes" ]]; then
         NominalIteration=`DHQuery GlobalSetting.dh Iterations ${Prefix}_R${R}_Centrality${C}_Nominal_${NP}`
         HNominal=HUnfoldedBayes${NominalIteration}

         MCIteration=`DHQuery GlobalSetting.dh Iterations ${MCPrefix}_R${R}_Centrality${C}_Nominal_${MCNP}`
         HMCNominal=HUnfoldedBayes${MCIteration}

         PriorIteration=`DHQuery GlobalSetting.dh Iterations ${Prefix}_R${R}_Centrality${C}_Nominal_${AP}`
         HPrior=HUnfoldedBayes${PriorIteration}

         IterationUp=`./ExecuteIteration --Input ${PRCN} --Mode Next --Iteration $NominalIteration`
         IterationDown=`./ExecuteIteration --Input ${PRCN} --Mode Previous --Iteration $NominalIteration`
         HIterationUp=HUnfoldedBayes${IterationUp}
         HIterationDown=HUnfoldedBayes${IterationDown}
      elif [[ "$Method" == "TUnfold" ]]; then
         HNominal=HUnfoldedTUnfold
         HMCNominal=HUnfoldedTUnfold
         HPrior=HUnfoldedTUnfold
         HIterationUp=HUnfoldedTUnfold
         HIterationDown=HUnfoldedTUnfold
      fi

      State=$PRC

      DHRemove Systematics.dh $PRC

      DHSet Systematics.dh $PRC JECUp_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC JECUp_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC JECUp_VariantFile      string  Input/${PRC}_JECUp_${NP}.root
      DHSet Systematics.dh $PRC JECUp_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC JECUp_Label            string  JECUp
      DHSet Systematics.dh $PRC JECUp_Include          int     1
      DHSet Systematics.dh $PRC JECUp_Bridging         int     0
      DHSet Systematics.dh $PRC JECUp_ExtraScaling     float   1
      
      DHSet Systematics.dh $PRC JECDown_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC JECDown_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC JECDown_VariantFile      string  Input/${PRC}_JECDown_${NP}.root
      DHSet Systematics.dh $PRC JECDown_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC JECDown_Label            string  JECDown
      DHSet Systematics.dh $PRC JECDown_Include          int     1
      DHSet Systematics.dh $PRC JECDown_Bridging         int     0
      DHSet Systematics.dh $PRC JECDown_ExtraScaling     float   1

      DHSet Systematics.dh $PRC JECQuench_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC JECQuench_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC JECQuench_VariantFile      string  Input/${PRC}_JECQuench_${NP}.root
      DHSet Systematics.dh $PRC JECQuench_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC JECQuench_Label            string  JECQuench
      DHSet Systematics.dh $PRC JECQuench_Include          int     1
      DHSet Systematics.dh $PRC JECQuench_Bridging         int     0
      DHSet Systematics.dh $PRC JECQuench_ExtraScaling     float   1

      DHSet Systematics.dh $PRC JERUp_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC JERUp_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC JERUp_VariantFile      string  Input/${PRC}_JERUp_${NP}.root
      DHSet Systematics.dh $PRC JERUp_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC JERUp_Label            string  JERUp
      DHSet Systematics.dh $PRC JERUp_Include          int     1
      DHSet Systematics.dh $PRC JERUp_Bridging         int     0
      DHSet Systematics.dh $PRC JERUp_ExtraScaling     float   1
      
      DHSet Systematics.dh $PRC JERDown_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC JERDown_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC JERDown_VariantFile      string  Input/${PRC}_JERDown_${NP}.root
      DHSet Systematics.dh $PRC JERDown_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC JERDown_Label            string  JERDown
      DHSet Systematics.dh $PRC JERDown_Include          int     1
      DHSet Systematics.dh $PRC JERDown_Bridging         int     0
      DHSet Systematics.dh $PRC JERDown_ExtraScaling     float   1

      DHSet Systematics.dh $PRC IterationUp_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC IterationUp_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC IterationUp_VariantFile      string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC IterationUp_VariantHistogram string  ${HIterationUp}
      DHSet Systematics.dh $PRC IterationUp_Label            string  IterationUp
      DHSet Systematics.dh $PRC IterationUp_Include          int     0
      DHSet Systematics.dh $PRC IterationUp_Bridging         int     0
      DHSet Systematics.dh $PRC IterationUp_ExtraScaling     float   1
      
      DHSet Systematics.dh $PRC IterationDown_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC IterationDown_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC IterationDown_VariantFile      string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC IterationDown_VariantHistogram string  ${HIterationDown}
      DHSet Systematics.dh $PRC IterationDown_Label            string  IterationDown
      DHSet Systematics.dh $PRC IterationDown_Include          int     0
      DHSet Systematics.dh $PRC IterationDown_Bridging         int     0
      DHSet Systematics.dh $PRC IterationDown_ExtraScaling     float   1

      DHSet Systematics.dh $PRC Prior_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC Prior_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC Prior_VariantFile      string  Input/${PRC}_Nominal_${AP}.root
      DHSet Systematics.dh $PRC Prior_VariantHistogram string  ${HPrior}
      DHSet Systematics.dh $PRC Prior_Label            string  Prior
      DHSet Systematics.dh $PRC Prior_Include          int     0
      DHSet Systematics.dh $PRC Prior_Bridging         int     0
      DHSet Systematics.dh $PRC Prior_ExtraScaling     float   1
      
      DHSet Systematics.dh $PRC Iteration_BaseFile         string  Input/${MCPRC}_Nominal_Toy_${MCNP}.root
      DHSet Systematics.dh $PRC Iteration_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC Iteration_VariantFile      string  Input/${MCPRC}_Nominal_Toy_${MCNP}.root
      DHSet Systematics.dh $PRC Iteration_VariantHistogram string  ${HMCNominal}
      DHSet Systematics.dh $PRC Iteration_Label            string  Iteration
      DHSet Systematics.dh $PRC Iteration_Include          int     1
      DHSet Systematics.dh $PRC Iteration_Bridging         int     0
      DHSet Systematics.dh $PRC Iteration_ExtraScaling     float   1

      DHSet Systematics.dh $PRC CentralityUp_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC CentralityUp_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC CentralityUp_VariantFile      string  Input/${PRC}_CentralityUp_${NP}.root
      DHSet Systematics.dh $PRC CentralityUp_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC CentralityUp_Label            string  CentralityUp
      DHSet Systematics.dh $PRC CentralityUp_Include          int     1
      DHSet Systematics.dh $PRC CentralityUp_Bridging         int     0
      DHSet Systematics.dh $PRC CentralityUp_ExtraScaling     float   1
      
      DHSet Systematics.dh $PRC CentralityDown_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC CentralityDown_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC CentralityDown_VariantFile      string  Input/${PRC}_CentralityDown_${NP}.root
      DHSet Systematics.dh $PRC CentralityDown_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC CentralityDown_Label            string  CentralityDown
      DHSet Systematics.dh $PRC CentralityDown_Include          int     1
      DHSet Systematics.dh $PRC CentralityDown_Bridging         int     0
      DHSet Systematics.dh $PRC CentralityDown_ExtraScaling     float   1

      DHSet Systematics.dh $PRC BinBiasUp_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC BinBiasUp_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC BinBiasUp_VariantFile      string  Input/${PRC}_NominalBinBiasUp_${NP}.root
      DHSet Systematics.dh $PRC BinBiasUp_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC BinBiasUp_Label            string  BinBiasUp
      DHSet Systematics.dh $PRC BinBiasUp_Include          int     1
      DHSet Systematics.dh $PRC BinBiasUp_Bridging         int     0
      DHSet Systematics.dh $PRC BinBiasUp_ExtraScaling     float   1
      
      DHSet Systematics.dh $PRC BinBiasDown_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC BinBiasDown_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC BinBiasDown_VariantFile      string  Input/${PRC}_NominalBinBiasDown_${NP}.root
      DHSet Systematics.dh $PRC BinBiasDown_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC BinBiasDown_Label            string  BinBiasDown
      DHSet Systematics.dh $PRC BinBiasDown_Include          int     1
      DHSet Systematics.dh $PRC BinBiasDown_Bridging         int     0
      DHSet Systematics.dh $PRC BinBiasDown_ExtraScaling     float   1

      DHSet Systematics.dh $PRC Earthquake_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC Earthquake_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC Earthquake_VariantFile      string  Input/${PRC}_NominalEarthquake_${NP}.root
      DHSet Systematics.dh $PRC Earthquake_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC Earthquake_Label            string  Earthquake
      DHSet Systematics.dh $PRC Earthquake_Include          int     1
      DHSet Systematics.dh $PRC Earthquake_Bridging         int     0
      DHSet Systematics.dh $PRC Earthquake_ExtraScaling     float   1
      
      DHSet Systematics.dh $PRC Cleaned_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC Cleaned_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC Cleaned_VariantFile      string  Input/${PRC}_NominalCleaned_${NP}.root
      DHSet Systematics.dh $PRC Cleaned_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC Cleaned_Label            string  Cleaned
      DHSet Systematics.dh $PRC Cleaned_Include          int     0
      DHSet Systematics.dh $PRC Cleaned_Bridging         int     0
      DHSet Systematics.dh $PRC Cleaned_ExtraScaling     float   1

      DHSet Systematics.dh $PRC CleanedStrong_BaseFile         string  Input/${PRC}_Nominal_${NP}.root
      DHSet Systematics.dh $PRC CleanedStrong_BaseHistogram    string  ${HNominal}
      DHSet Systematics.dh $PRC CleanedStrong_VariantFile      string  Input/${PRC}_NominalCleanedStrong_${NP}.root
      DHSet Systematics.dh $PRC CleanedStrong_VariantHistogram string  ${HNominal}
      DHSet Systematics.dh $PRC CleanedStrong_Label            string  CleanedStrong
      DHSet Systematics.dh $PRC CleanedStrong_Include          int     0
      DHSet Systematics.dh $PRC CleanedStrong_Bridging         int     0
      DHSet Systematics.dh $PRC CleanedStrong_ExtraScaling     float   1

      ./Execute \
         --ReadFromDHFile true \
         --DHFile Systematics.dh --State $PRC \
         --BinMapping BinMapping/${PRC}_Nominal.root \
         --DoSelfNormalize false \
         --Output Output/${PRC}.root
      
      if [[ $IsPP == 0 ]]; then
         TAA=`DHQuery GlobalSetting.dh TAA $C`
         TAAError=`DHQuery GlobalSetting.dh TAAErrorUp $C`
         TAARelativeError=`echo $TAAError | DivideConst $TAA`
         DHSet Systematics.dh $PRC Global_TAA float $TAARelativeError
         DHSet Systematics.dh $PRC Global_NMB float 0.0126
         DHSet Systematics.dh $PRC Global_PbPbSelection float 0.01
      else
         DHSet Systematics.dh $PRC Global_Luminosity float 0.019
         DHSet Systematics.dh $PRC Global_PPSelection float 0.01
      fi

      ./ExecutePlot \
         --Input Output/${PRC}.root --Output Plot/${PRC}.pdf \
         --Variations HJECUp,HJECDown,HJERUp,HJERDown,HIterationUp,HIterationDown,HPrior,HIteration,HCentralityDown,HCentralityDown,HJECQuench \
         --Labels "JEC Up","JEC Down","JER Up","JER Down","Iteration Up","Iteration Down","Prior","Iteration","Centrality Up","Centrality Down","Quench"
      done
   done



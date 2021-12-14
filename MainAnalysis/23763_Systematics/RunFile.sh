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
      NP="`DHQuery GlobalSetting.dh DefaultPrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`Prior"
      AP="`DHQuery GlobalSetting.dh AlternatePrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`Prior"

      RC="R${R}_Centrality${C}"
      PRC="${Prefix}_${RC}"
      PRCN="Input/${PRC}_Nominal_${NP}.root"

      MCPRC="${MCPrefix}_${RC}"
      MCPRCN="Input/${MCPRC}_Nominal_${NP}.root"
      MCPRCToy="Input/${MCPRC}_Nominal_Toy_${NP}.root"

      NominalIteration=`DHQuery GlobalSetting.dh Iterations ${Prefix}_R${R}_Centrality${C}_Nominal_${NP}`
      HNominal=HUnfoldedBayes${NominalIteration}

      MCIteration=`DHQuery GlobalSetting.dh Iterations ${MCPrefix}_R${R}_Centrality${C}_Nominal_${NP}`
      HMCNominal=HUnfoldedBayes${MCIteration}
      
      PriorIteration=`DHQuery GlobalSetting.dh Iterations ${Prefix}_R${R}_Centrality${C}_Nominal_${AP}`
      HPrior=HUnfoldedBayes${PriorIteration}
      
      IterationUp=`./ExecuteIteration --Input ${PRCN} --Mode Next --Iteration $NominalIteration`
      IterationDown=`./ExecuteIteration --Input ${PRCN} --Mode Previous --Iteration $NominalIteration`
      HIterationUp=HUnfoldedBayes${IterationUp}
      HIterationDown=HUnfoldedBayes${IterationDown}

      ./Execute \
         --BaseInput ${PRCN},${PRCN},${PRCN},${PRCN},${PRCN},${PRCN},${PRCN},${MCPRCToy},${PRCN},${PRCN},${PRCN} \
         --Input Input/${PRC}_JECUp_${NP}.root,Input/${PRC}_JECDown_${NP}.root,Input/${PRC}_JERUp_${NP}.root,Input/${PRC}_JERDown_${NP}.root,${PRCN},${PRCN},Input/${PRC}_Nominal_${AP}.root,${MCPRCToy},Input/${PRC}_CentralityUp_${NP}.root,Input/${PRC}_CentralityDown_${NP}.root,Input/${PRC}_JECQuench_${NP}.root \
         --BaseHistogram ${HNominal},${HNominal},${HNominal},${HNominal},${HNominal},${HNominal},${HNominal},${HMCNominal},${HNominal},${HNominal},${HNominal} \
         --Histogram ${HNominal},${HNominal},${HNominal},${HNominal},${HIterationUp},${HIterationDown},${HPrior},${HNominal},${HNominal},${HNominal},${HNominal} \
         --Label JECUp,JECDown,JERUp,JERDown,IterationUp,IterationDown,Prior,Iteration,CentralityUp,CentralityDown,JECQuench \
         --Group 1,1,1,1,0,0,1,1,1,1,1 \
         --Bridging 0,0,0,0,0,0,0,0,0,0,0 \
         --ExtraScaling 1,1,1,1,1,1,1,1,1,1,1 \
         --BinMapping BinMapping/${PRC}_Nominal.root \
         --DoSelfNormalize false \
         --Output Output/${PRC}.root

      if [[ $IsPP == 0 ]]; then
         TAA=`DHQuery GlobalSetting.dh TAA $C`
         TAAError=`DHQuery GlobalSetting.dh TAAErrorUp $C`
         TAARelativeError=`echo $TAAError | DivideConst $TAA`
         DHSet GlobalSystematics.dh $PRC TAA float $TAARelativeError
         DHSet GlobalSystematics.dh $PRC NMB float 0.0126
         DHSet GlobalSystematics.dh $PRC PbPbSelection float 0.01
      else
         DHSet GlobalSystematics.dh $PRC Luminosity float 0.019
         DHSet GlobalSystematics.dh $PRC PPSelection float 0.01
      fi

      ./ExecutePlot \
         --Input Output/${PRC}.root --Output Plot/${PRC}.pdf \
         --Variations HJECUp,HJECDown,HJERUp,HJERDown,HIterationUp,HIterationDown,HPrior,HIteration,HCentralityDown,HCentralityDown,HJECQuench \
         --Labels "JEC Up","JEC Down","JER Up","JER Down","Iteration Up","Iteration Down","Prior","Iteration","Centrality Up","Centrality Down","Quench"
   done
done



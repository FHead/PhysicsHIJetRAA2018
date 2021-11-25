#!/bin/bash

Prefix=$1
IsPP=$2

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
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

      NominalIteration=`DHQuery GlobalSetting.dh Iterations ${Prefix}_R${R}_Centrality${C}_Nominal_${NP}`
      HNominal=HUnfoldedBayes${NominalIteration}
      
      PriorIteration=`DHQuery GlobalSetting.dh Iterations ${Prefix}_R${R}_Centrality${C}_Nominal_${AP}`
      HPrior=HUnfoldedBayes${PriorIteration}
      
      IterationUp=`./ExecuteIteration --Input ${PRCN} --Mode Next --Iteration $NominalIteration`
      IterationDown=`./ExecuteIteration --Input ${PRCN} --Mode Previous --Iteration $NominalIteration`
      HIterationUp=HUnfoldedBayes${IterationUp}
      HIterationDown=HUnfoldedBayes${IterationDown}

      ./Execute \
         --BaseInput ${PRCN},${PRCN},${PRCN},${PRCN},${PRCN},${PRCN},${PRCN} \
         --Input Input/${PRC}_JECUp_${NP}.root,Input/${PRC}_JECDown_${NP}.root,Input/${PRC}_JERUp_${NP}.root,Input/${PRC}_JERDown_${NP}.root,${PRCN},${PRCN},Input/${PRC}_Nominal_${AP}.root \
         --BaseHistogram ${HNominal},${HNominal},${HNominal},${HNominal},${HNominal},${HNominal},${HNominal} \
         --Histogram ${HNominal},${HNominal},${HNominal},${HNominal},${HIterationUp},${HIterationDown},${HPrior} \
         --Label JECUp,JECDown,JERUp,JERDown,IterationUp,IterationDown,Prior \
         --Group 1,1,1,1,1,1,1 \
         --Bridging 0,0,0,0,0,0,0 \
         --ExtraScaling 1,1,1,1,1,1,1 \
         --BinMapping BinMapping/${PRC}_Nominal.root \
         --DoSelfNormalize false \
         --Output Output/${PRC}.root

      ./ExecutePlot \
         --Input Output/${PRC}.root --Output Plot/${PRC}.pdf \
         --Variations HJECUp,HJECDown,HJERUp,HJERDown,HIterationUp,HIterationDown,HPrior \
         --Labels "JEC Up","JEC Down","JER Up","JER Down","Iteration Up","Iteration Down","Prior"
   done
done





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
      RC="R${R}_Centrality${C}"
      PRC="${Prefix}_${RC}"
      PRCN="Input/${PRC}_Nominal.root"

      NominalIteration=`DHQuery GlobalSetting.dh ${Prefix} BestIteration_R${R}_Centrality${C}`
      HNominal=HUnfoldedBayes${NominalIteration}

      ./Execute \
         --BaseInput ${PRCN},${PRCN},${PRCN},${PRCN} \
         --Input Input/${PRC}_JECUp.root,Input/${PRC}_JECDown.root,Input/${PRC}_JERUp.root,Input/${PRC}_JERDown.root \
         --BaseHistogram ${HNominal},${HNominal},${HNominal},${HNominal} \
         --Histogram ${HNominal},${HNominal},${HNominal},${HNominal} \
         --Label JECUp,JECDown,JERUp,JERDown \
         --Group 1,1,1,1 \
         --Bridging 0,0,0,0 \
         --ExtraScaling 1,1,1,1 \
         --BinMapping BinMapping/${PRC}_Nominal.root \
         --DoSelfNormalize false \
         --Output Output/${PRC}.root

      ./ExecutePlot \
         --Input Output/${PRC}.root --Output Plot/${PRC}.pdf \
         --Variations HJECUp,HJECDown \
         --Labels "JEC Up","JEC Down"
   done
done



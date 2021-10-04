

Prefix=$1

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

for R in $JetR
do
   for C in $Centrality
   do
      RC="R${R}_Centrality${C}"
      PRC="${Prefix}_${RC}"
      PRCN="Input/${PRC}_Nominal.root"

      ./Execute \
         --BaseInput ${PRCN},${PRCN} \
         --Input Input/${PRC}_JECUp.root,Input/${PRC}_JECDown.root \
         --BaseHistogram HUnfoldedBayes30,HUnfoldedBayes30 \
         --Histogram HUnfoldedBayes30,HUnfoldedBayes30 \
         --Label JECUp,JECDown \
         --Group 1,1 \
         --Bridging 0,0 \
         --ExtraScaling 1,1 \
         --BinMapping BinMapping/${PRC}_Nominal.root \
         --DoSelfNormalize false \
         --Output Output/${PRC}.root

      ./ExecutePlot \
         --Input Output/${PRC}.root --Output Plot/${PRC}.pdf \
         --Variations HJECUp,HJECDown \
         --Labels "JEC Up","JEC Down"
   done
done



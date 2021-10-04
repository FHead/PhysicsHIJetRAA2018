
Prefix=$1
Suffix=$2

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

if [[ "$Suffix" != "" ]]; then
   Suffix="_$Suffix"
fi

for R in $JetR
do
   for C in $Centrality
   do
      PRC="${Prefix}_R${R}_Centrality${C}"
      PRCN="${PRC}_Nominal${Suffix}.root"

      ./Execute \
         --Input Input/${PRCN} \
         --Systematic Systematics/${PRC}.root \
         --Output Plots/QualityPlots_${PRC}${Suffix}.pdf --FinalOutput Plots/${PRC}${Suffix}.pdf \
         --MCFile "Input/${PRCN}" \
         --MCHistogram "HMCTruth" \
         --MCLabel "MC (normalized to data)" \
         --PrimaryName HUnfoldedBayes15 \
         --DoSelfNormalize false \
         --WorldXMin 150 --WorldXMax 1000 --WorldYMin 0.0005 --WorldYMax 500 --WorldRMin 0.51 --WorldRMax 1.49 \
         --LogX true --LogY true \
         --XLabel "Jet p_{T} (GeV)" --YLabel "dN / d(Jet p_{T})" --Binning None \
         --LegendX 0.45 --LegendY 0.55 --LegendSize 0.04 \
         --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
         --Texts 0,0.65,0.9,"Anti-k_{T} jet R = 0.4",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"Centrality 0-90%" \
         --IgnoreGroup 0 --Row 1 --Column 1
   done
done

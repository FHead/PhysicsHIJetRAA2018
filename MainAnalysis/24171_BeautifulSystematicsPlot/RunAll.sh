#!/bin/bash

JetR=`DHQuery GlobalSetting.dh Global JetR | tr -d '"'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr -d '"'`

Variations="HJECUp,HJECDown,HJERUp,HJERDown,HIterationUp,HIterationDown,HPrior"
SystematicGroups="1,1,2,2,3,3,3"
Labels="JEC,JER,Iteration"

# Run pp spectrum
for R in $JetR
do
   LowerBound=`DHQuery GlobalSetting.dh TriggerTurnOn R${R}_CentralityInclusive_Cut`

   ./Execute --Input Systematics/PPData_R${R}_CentralityInclusive.root \
      --Output Plots/PPData_R${R}_CentralityInclusive.pdf \
      --FinalOutput FinalPlots/PPData_R${R}_CentralityInclusive.pdf \
      --GenPrimaryMin 0 --GenPrimaryMax 1600 \
      --WorldXMin $LowerBound --WorldXMax 1500 --WorldYMin 0 --WorldYMax 1.0 --LogY false --LogX true \
      --XLabel "Jet p_{T}" --YLabel "Uncertainty" --Binning "none" \
      --LegendX 0.12 --LegendY 0.5 --LegendSize 0.05 \
      --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1 \
      --Texts 0,0.12,0.88,"Anti-k_{T} jet R = 0.4",0,0.12,0.83,"|#eta| < 2.0" \
      --Group 1 --Row 1 --Column 1 \
      --Variations ${Variations} \
      --SystematicGroups ${SystematicGroups} \
      --Labels ${Labels}
done

# Run PbPb spectrum
for R in $JetR
do
   for C in $Centrality
   do
      LowerBound=`DHQuery GlobalSetting.dh TriggerTurnOn R${R}_Centrality${C}_Cut`
      
      ./Execute --Input Systematics/PbPbData_R${R}_Centrality${C}.root \
         --Output Plots/PbPbData_R${R}_Centrality${C}.pdf \
         --FinalOutput FinalPlots/PbPbData_R${R}_Centrality${C}.pdf \
         --GenPrimaryMin 0 --GenPrimaryMax 1600 \
         --WorldXMin $LowerBound --WorldXMax 1500 --WorldYMin 0 --WorldYMax 1.0 --LogY false --LogX true \
         --XLabel "Jet p_{T}" --YLabel "Uncertainty" --Binning "none" \
         --LegendX 0.12 --LegendY 0.5 --LegendSize 0.05 \
         --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1 \
         --Texts 0,0.12,0.88,"Anti-k_{T} jet R = 0.4",0,0.12,0.83,"|#eta| < 2.0" \
         --Group 1 --Row 1 --Column 1 \
         --Variations ${Variations} \
         --SystematicGroups ${SystematicGroups} \
         --Labels ${Labels}
   done
done

# Run pp spectra ratio
for R in $JetR
do
   LowerBound=`DHQuery GlobalSetting.dh TriggerTurnOn R9_CentralityInclusive_Cut`
   
   ./Execute --Input CombinedSystematics/PPDataRatio_R${R}R9_CentralityInclusive.root \
      --Output Plots/PPDataRatio_R${R}R9_CentralityInclusive.pdf \
      --FinalOutput FinalPlots/PPDataRatio_R${R}R9_CentralityInclusive.pdf \
      --GenPrimaryMin 0 --GenPrimaryMax 1600 \
      --WorldXMin $LowerBound --WorldXMax 1500 --WorldYMin 0 --WorldYMax 1.0 --LogY false --LogX true \
      --XLabel "Jet p_{T}" --YLabel "Uncertainty" --Binning "none" \
      --LegendX 0.12 --LegendY 0.5 --LegendSize 0.05 \
      --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1 \
      --Texts 0,0.12,0.88,"Anti-k_{T} jet R = 0.4",0,0.12,0.83,"|#eta| < 2.0" \
      --Group 1 --Row 1 --Column 1 \
      --Variations ${Variations} \
      --SystematicGroups ${SystematicGroups} \
      --Labels ${Labels}
done

# Run RAA
for R in $JetR
do
   for C in $Centrality
   do
      LowerBound=`DHQuery GlobalSetting.dh TriggerTurnOn R${R}_Centrality${C}_Cut`
   
      ./Execute --Input CombinedSystematics/RAA_R${R}_Centrality${C}.root \
         --Output Plots/RAA_R${R}_Centrality${C}.pdf \
         --FinalOutput FinalPlots/RAA_R${R}_Centrality${C}.pdf \
         --GenPrimaryMin 0 --GenPrimaryMax 1600 \
         --WorldXMin $LowerBound --WorldXMax 1500 --WorldYMin 0 --WorldYMax 1.0 --LogY false --LogX true \
         --XLabel "Jet p_{T}" --YLabel "Uncertainty" --Binning "none" \
         --LegendX 0.12 --LegendY 0.5 --LegendSize 0.05 \
         --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1 \
         --Texts 0,0.12,0.88,"Anti-k_{T} jet R = 0.4",0,0.12,0.83,"|#eta| < 2.0" \
         --Group 1 --Row 1 --Column 1 \
         --Variations ${Variations} \
         --SystematicGroups ${SystematicGroups} \
         --Labels ${Labels}
   done
done

# Run RRAA
for R in $JetR
do
   for C in $Centrality
   do
      LowerBound=`DHQuery GlobalSetting.dh TriggerTurnOn R${R}_Centrality${C}_Cut`
      
      ./Execute --Input CombinedSystematics/RRAA_R${R}R1_Centrality${C}.root \
         --Output Plots/RRAA_R${R}R1_Centrality${C}.pdf \
         --FinalOutput FinalPlots/RRAA_R${R}R1_Centrality${C}.pdf \
         --GenPrimaryMin 0 --GenPrimaryMax 1600 \
         --WorldXMin $LowerBound --WorldXMax 1500 --WorldYMin 0 --WorldYMax 1.0 --LogY false --LogX true \
         --XLabel "Jet p_{T}" --YLabel "Uncertainty" --Binning "none" \
         --LegendX 0.12 --LegendY 0.5 --LegendSize 0.05 \
         --XAxis 305 --YAxis 505 --RAxis 303 --MarkerModifier 1 \
         --Texts 0,0.12,0.88,"Anti-k_{T} jet R = 0.4",0,0.12,0.83,"|#eta| < 2.0" \
         --Group 1 --Row 1 --Column 1 \
         --Variations ${Variations} \
         --SystematicGroups ${SystematicGroups} \
         --Labels ${Labels}
   done
done






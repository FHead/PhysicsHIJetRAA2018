#!/bin/bash
Prefix=$1
Suffix=$2
IsPP=$3

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

if [[ "$Suffix" != "" ]]; then
   Suffix="_$Suffix"
fi

for R in $JetR
do
   for C in $Centrality
   do
      RValue=`DHQuery GlobalSetting.dh JetR $R`

      State=PbPbData
      if [[ "$IsPP" == "1" ]]; then
         State=PPData
      fi

      Luminosity=1
      LuminosityUnit="b^{-1}"
      ExtraScale=0.25 # coming from |eta| going from -2 to +2
      if [[ "$IsPP" == "1" ]]; then
         Luminosity=`DHQuery GlobalSetting.dh Lumi ${State}_R${R}_Centrality${C}_BRIL | tr -d '"' | DivideConst 1000000`
         LuminosityUnit="pb^{-1}"
         ExtraScale=`echo $ExtraScale | DivideConst $Luminosity | DivideConst 1000`
         # echo Lumi = $Luminosity
         # echo Extra scale = $ExtraScale
      else
         Luminosity=`DHQuery GlobalSetting.dh Lumi ${State}_R${R}_Centrality${C}_BRIL | tr -d '"'`
         LuminosityUnit="#mub^{-1}"
         MBCount=`DHQuery GlobalSetting.dh MBCount ${State}_R${R}_Centrality${C}_WeightedCount | tr -d '"'`
         # MBCount=`echo 11532346230 | DivideConst 1788.69 | MultiplyConst $Luminosity`
         TAA=`DHQuery GlobalSetting.dh TAA ${C} | tr -d '"' | DivideConst 1000000`
         ExtraScale=`echo $ExtraScale | DivideConst $MBCount | DivideConst $TAA`
      fi

      PUBugCorrection=`DHQuery GlobalSetting.dh PUBugCorrection ${State}_R${R}_Centrality${C}`
      ExtraScale=`echo $ExtraScale | MultiplyConst $PUBugCorrection`

      System="PbPb"
      if [[ "$IsPP" == "1" ]]; then
         System="pp"
      else
         System="PbPb"
      fi

      CentralityString=" "
      if [[ "$IsPP" == "1" ]]; then
         CentralityString=" "
      else
         CentralityMin=`DHQuery GlobalSetting.dh CentralityMin ${C} | tr -d '"' | MultiplyConst 100`
         CentralityMax=`DHQuery GlobalSetting.dh CentralityMax ${C} | tr -d '"' | MultiplyConst 100`
         CentralityString="Centrality ${CentralityMin}%-${CentralityMax}%"
      fi

      YLabel="default"
      if [[ "$IsPP" == "1" ]]; then
         YLabel="d^2#sigma / dp_{T}d#eta (nb)"
      else
         YLabel="#frac{1}{<T_{AA}>}#frac{1}{N_{evt}}#frac{d^{2}N_{jet}}{dp_{T}d#eta}"
      fi

      NP="`DHQuery GlobalSetting.dh DefaultPrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`Prior"
      PRC="${Prefix}_R${R}_Centrality${C}"
      PRCN="${PRC}_Nominal${Suffix}_${NP}.root"
      HPrimary=HUnfoldedBayes`DHQuery GlobalSetting.dh Iterations ${State}_R${R}_Centrality${C}_Nominal_${NP}`
      Underflow=`DHQuery GlobalSetting.dh Binning PTUnderflow_R${R}_Centrality${C}`

      MCFile="Input/${PRCN},HEPData/Graph_pp_CMSR${R}.root,HEPData/Graph_pp_ATLASR${R}.root"
      MCHist="HMCTruth,GHEPData,GHEPData"
      MCLabel="MC (normalize to data),CMS HIN-18-014 |#eta|<2.0 (pp),ATLAS (2019) |y|<2.8 (pp)"
      NormalizeMCToData="true,false,false"

      if [[ "$Suffix" == "_Toy" ]]; then
         MCFile="Input/${PRCN}"
         MCHist="HMCTruth"
         MCLabel="Input"
         NormalizeMCToData="true"
      fi

      ./Execute \
         --Input Input/${PRCN} \
         --Systematic Systematics/${PRC}.root \
         --Output Plots/QualityPlots_${PRC}${Suffix}.pdf --FinalOutput Plots/${PRC}${Suffix}.pdf \
         --RootOutput Root/${PRC}${Suffix}.root \
         --MCFile "${MCFile}" --MCHistogram "${MCHist}" --MCLabel "${MCLabel}" \
         --NormalizeMCToData ${NormalizeMCToData} \
         --PrimaryName $HPrimary \
         --Underflow $Underflow \
         --DoSelfNormalize false \
         --ExtraScale $ExtraScale \
         --WorldXMin 141 --WorldXMax 1500 --WorldYMin 0.000000001 --WorldYMax 1 --WorldRMin 0.51 --WorldRMax 1.49 \
         --LogX true --LogY true \
         --XLabel "Jet p_{T} (GeV)" --YLabel ${YLabel} --Binning None \
         --LegendX 0.10 --LegendY 0.10 --LegendSize 0.04 \
         --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
         --Texts 0,0.65,0.9,"Anti-k_{T} jet R = $RValue",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"$CentralityString" \
         --Luminosity $Luminosity --LuminosityUnit $LuminosityUnit --System $System \
         --IgnoreGroup 0 --Row 1 --Column 1
   done
done

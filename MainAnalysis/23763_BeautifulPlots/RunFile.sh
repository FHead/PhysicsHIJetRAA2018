#!/bin/bash
Prefix=$1
Type=$2
Suffix=$3
IsPP=$4
Tier=$5

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
         # MBCount=`DHQuery GlobalSetting.dh MBCount ${State}_R${R}_Centrality${C}_WeightedCount | tr -d '"'`
         MBCount=`DHQuery GlobalSetting.dh MBCount ${State}_R${R}_Centrality${C}_OfficialCount | tr -d '"'`
         TAA=`DHQuery GlobalSetting.dh TAA ${C} | tr -d '"' | DivideConst 1000000`
         ExtraScale=`echo $ExtraScale | DivideConst $MBCount | DivideConst $TAA`
      fi

      PUBugCorrection=`DHQuery GlobalSetting.dh PUBugCorrection ${State}_R${R}_Centrality${C}`
      ExtraScale=`echo $ExtraScale | MultiplyConst $PUBugCorrection`
      
      EfficiencyCorrection=`DHQuery GlobalSetting.dh EventSelection ${State}_R${R}_Centrality${C}`
      ExtraScale=`echo $ExtraScale | MultiplyConst $EfficiencyCorrection`

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
         YLabel="d^{2}#sigma / dp_{T}d#eta (nb)"
      else
         YLabel="#frac{1}{<T_{AA}>}#frac{1}{N_{evt}}#frac{d^{2}N_{jet}}{dp_{T}d#eta}"
      fi

      NP="`DHQuery GlobalSetting.dh PriorToUse ${Prefix}_R${R}_Centrality${C}_Default | tr -d '"'`Prior"
      PRC="${Prefix}_R${R}_Centrality${C}"
      PRCTS="${PRC}_${Type}${Suffix}"
      PRCN="${PRCTS}_${NP}.root"
      
      PRCTST=${PRCTS}
      if [[ "$Tier" != "Gen" ]]; then
         PRCTST=${PRCTS}_${Tier}
      fi

      Method=`DHQuery GlobalSetting.dh MethodToUse ${State}_R${R}_Centrality${C}_Default | tr -d '"'`
      if [[ "$Tier" == "Gen" ]]; then
         if [[ "${Method}" == "Bayes" ]]; then
            HPrimary=HUnfoldedBayes`DHQuery GlobalSetting.dh Iterations ${State}_R${R}_Centrality${C}_Nominal_${NP}`
         elif [[ "$Method" == "TUnfold" ]]; then
            HPrimary=HUnfoldedTUnfold
         fi
         Underflow=`DHQuery GlobalSetting.dh Binning PTUnderflow_R${R}_Centrality${C}`
         Overflow=`DHQuery GlobalSetting.dh Binning PTOverflow_R${R}_Centrality${C}`
      elif [[ "$Tier" == "Reco" ]]; then
         if [[ "${Method}" == "Bayes" ]]; then
            HPrimary=HRefoldedBayes`DHQuery GlobalSetting.dh Iterations ${State}_R${R}_Centrality${C}_Nominal_${NP}`
         elif [[ "$Method" == "TUnfold" ]]; then
            HPrimary=HRefoldedTUnfold
         fi
         Underflow=0
         Overflow=0
      elif [[ "$Tier" == "InputReco" ]]; then
         HPrimary=HInput
         Underflow=0
         Overflow=0
      elif [[ "$Tier" == "InputRecoGenBin" ]]; then
         HPrimary=HInputGenBin
         Underflow=0
         Overflow=0
      fi

      MCFile="Input/${PRCN},HEPData/Graph_pp_CMSR${R}.root,HEPData/Graph_pp_ATLASR${R}.root"
      MCHist="HMCTruth,GHEPData,GHEPData"
      MCLabel="MC (normalize to data),CMS HIN-18-014 |#eta|<2.0 (pp),ATLAS (2019) |y|<2.8 (pp)"
      NormalizeMCToData="true,false,false"
      MCExtraScale="1,1,1"
      MCAbsoluteScale="true,true,true"

      if [[ "$Tier" == "Gen" ]]; then
         if [[ "$Suffix" == "_Toy" ]]; then
            MCFile="Input/${PRCN}"
            MCHist="HMCTruth"
            MCLabel="Input"
            NormalizeMCToData="true"
            MCExtraScale="1"
            MCAbsoluteScale="true"
         fi
         if [[ "$Type" != "Nominal" ]]; then
            MCFile="DUMMY"
            MCHist="DUMMY"
            MCLabel="DUMMY"
            NormalizeMCToData="false"
            MCExtraScale="1"
            MCAbsoluteScale="true"
         fi
      elif [[ "$Tier" == "Reco" ]]; then
         MCFile="Input/${PRCN}"
         MCHist="HInput"
         MCLabel="Input"
         NormalizeMCToData="false"
         MCExtraScale="$ExtraScale"
         MCAbsoluteScale="false"
      elif [[ "$Tier" == "InputReco" ]]; then
         MCFile="Input/${PRCN}"
         MCHist="HMCMeasured"
         MCLabel="MC"
         NormalizeMCToData="true"
         MCExtraScale="$ExtraScale"
         MCAbsoluteScale="false"
      elif [[ "$Tier" == "InputRecoGenBin" ]]; then
         MCFile="Input/${PRCN}"
         MCHist="HMCMeasuredGenBin"
         MCLabel="MC"
         NormalizeMCToData="true"
         MCExtraScale="$ExtraScale"
         MCAbsoluteScale="false"
      fi

      SystematicsFile=Systematics/${PRC}.root
      if [[ "$Tier" != "Gen" ]]; then
         SystematicsFile=NULL
      fi

      DataLabel=Data
      if [[ "$Tier" == "Gen" ]]; then
         DataLabel="Data"
      elif [[ "$Tier" == "Reco" ]]; then
         DataLabel="Refolded"
      elif [[ "$Tier" == "InputReco" ]]; then
         DataLabel="Reco data"
      elif [[ "$Tier" == "InputRecoGenBin" ]]; then
         DataLabel="Reco data"
      fi

      BinningTier=Gen
      if [[ "$Tier" == "Gen" ]]; then
         BinningTier=Gen
      elif [[ "$Tier" == "Reco" ]]; then
         BinningTier=Reco
      elif [[ "$Tier" == "InputReco" ]]; then
         BinningTier=Reco
      elif [[ "$Tier" == "InputRecoGenBin" ]]; then
         BinningTier=Gen
      fi

      ./Execute \
         --Input Input/${PRCN} \
         --Systematic $SystematicsFile \
         --Output Plots/QualityPlots_${PRCTST}.pdf --FinalOutput Plots/${PRCTST}.pdf \
         --RootOutput Root/${PRCTST}.root \
         --DataLabel "$DataLabel" \
         --MCFile "${MCFile}" --MCHistogram "${MCHist}" --MCLabel "${MCLabel}" \
         --MCExtraScale "$MCExtraScale" --MCAbsoluteScale "$MCAbsoluteScale" \
         --Tier $BinningTier \
         --NormalizeMCToData ${NormalizeMCToData} \
         --PrimaryName $HPrimary \
         --Underflow $Underflow \
         --Overflow $Overflow \
         --DoSelfNormalize false \
         --ExtraScale $ExtraScale \
         --WorldXMin 141 --WorldXMax 1500 --WorldYMin 0.000000001 --WorldYMax 3 --WorldRMin 0.51 --WorldRMax 1.49 \
         --LogX true --LogY true \
         --XLabel "Jet p_{T} (GeV)" --YLabel "${YLabel}" --Binning None \
         --LegendX 0.10 --LegendY 0.10 --LegendSize 0.04 \
         --XAxis 505 --YAxis 505 --RAxis 505 --MarkerModifier 0.5 \
         --Texts 0,0.65,0.9,"Anti-k_{T} jet R = $RValue",0,0.65,0.85,"|#eta_{jet}| < 2.0",0,0.65,0.8,"$CentralityString" \
         --Luminosity $Luminosity --LuminosityUnit $LuminosityUnit --System $System \
         --IgnoreGroup 0 --Row 1 --Column 1
   done
done

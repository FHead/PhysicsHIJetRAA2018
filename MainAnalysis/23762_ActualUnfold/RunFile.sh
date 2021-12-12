

Location=$1
Prefix=$2
Suffix=$3
IsPP=$4
PriorChoice=$5

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

for R in $JetR
do
   for C in $Centrality
   do
      Prior=
      if [[ $PriorChoice == "Nominal" ]]; then
         Prior=`DHQuery GlobalSetting.dh DefaultPrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`
      elif [[ $PriorChoice == "Alternate" ]]; then
         Prior=`DHQuery GlobalSetting.dh AlternatePrior ${Prefix}_R${R}_Centrality${C} | tr -d '"'`
      else
         Prior=$PriorChoice
      fi

      PriorString=$Prior
      PriorExtra=""
      if [[ "$Prior" == "Power40" ]]; then
         PriorString="Power"
         PriorExtra="--PriorK -4.0"
      elif [[ "$Prior" == "Power50" ]]; then
         PriorString="Power"
         PriorExtra="--PriorK -5.0"
      elif [[ "$Prior" == "Power60" ]]; then
         PriorString="Power"
         PriorExtra="--PriorK -6.0"
      elif [[ "$Prior" == "Power70" ]]; then
         PriorString="Power"
         PriorExtra="--PriorK -7.0"
      elif [[ "$Prior" == "ExternalMC" ]]; then
         PriorString="ExternalMC"
         PriorExtra="--ExternalPriorFile Input/${Prefix}_R${R}_Centrality${C}_Nominal.root"
      fi

      DoToyError=false
      if [[ "$Suffix" == "Nominal" ]] && [[ "$PriorChoice" == "Nominal" ]]; then
         DoToyError=true
      fi

      echo Unfolding now with R$R, Centrality $C, Prefix $Prefix, Suffix $Suffix and prior $Prior
      # echo Input file = $Location/${Prefix}_R${R}_Centrality${C}_${Suffix}.root

      Ignore=`DHQuery GlobalSetting.dh Binning PTUnderflow_R${R}_Centrality${C}`

      OutputSuffix="${Prior}Prior"

      ./Execute --Input $Location/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Output Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_${OutputSuffix}.root \
         --Prior $PriorString $PriorExtra --DoToyError $DoToyError
         # --FoldNormalize true --Ignore $Ignore --DoToyError $DoToyError
      ./ExecutePlot --Input Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_${OutputSuffix}.root \
         --Output Plots/${Prefix}_R${R}_Centrality${C}_${Suffix}_${OutputSuffix}.pdf \
         --Ignore $Ignore
   done

done




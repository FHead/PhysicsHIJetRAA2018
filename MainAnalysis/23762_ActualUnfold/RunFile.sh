

Location=$1
Prefix=$2
Suffix=$3
IsPP=$4
Prior=$5

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

OutputSuffix=
if [[ "$Prior" != "MC" ]]; then
   OutputSuffix="_${Prior}Prior"
fi

for R in $JetR
do
   for C in $Centrality
   do
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

      echo Unfolding now with R$R, Centrality $C, Prefix $Prefix, Suffix $Suffix and prior $Prior
      echo Input file = $Location/${Prefix}_R${R}_Centrality${C}_${Suffix}.root

      Ignore=`DHQuery GlobalSetting.dh Binning PTUnderflow_R${R}_Centrality${C}`

      ./Execute --Input $Location/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Output Output/${Prefix}_R${R}_Centrality${C}_${Suffix}${OutputSuffix}.root \
         --Prior $PriorString $PriorExtra
      ./ExecutePlot --Input Output/${Prefix}_R${R}_Centrality${C}_${Suffix}${OutputSuffix}.root \
         --Output Plots/${Prefix}_R${R}_Centrality${C}_${Suffix}${OutputSuffix}.pdf \
         --Ignore $Ignore
   done
done




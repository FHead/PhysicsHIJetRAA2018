

Prefix=$1
Suffix=$2
IsPP=$3
IterationPrefix=$4

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`

Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

echo $JetR

for R in $JetR
do
   echo $R
   for C in $Centrality
   do
      GenHistogram=HMCGen
      GenFolder=Input
      if [[ "$IterationPrefix" == "" ]]; then
         GenHistogram=HMCGen
         GenFolder=Input
      else
         GenHistogram=HUnfoldedBayes`DHQuery GlobalSetting.dh ${IterationPrefix} BestIteration_R${R}_Centrality${C}`
         GenFolder=UnfoldedInput
      fi

      echo $C
      echo GenHistogram = $GenHistogram
      echo Input = Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root

      ./Execute --MC Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Yield     Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Gen       $GenFolder/${Prefix}_R${R}_Centrality${C}_${Suffix}.root --GenHistogram $GenHistogram \
         --Output    Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_PerfectReco.root
   done
done


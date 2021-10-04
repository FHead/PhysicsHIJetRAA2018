

Prefix=$1
Suffix=$2

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

echo $JetR

for R in $JetR
do
   echo $R
   for C in $Centrality
   do
      echo $C
      ./Execute --MC Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Yield     Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Gen       Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root --GenHistogram HMCGen \
         --Output    Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_PerfectReco.root
   done
done


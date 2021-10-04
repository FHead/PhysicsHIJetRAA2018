

Prefix=$1
Suffix=$2
YieldPrefix=$3
YieldSuffix=$4
Fraction=$5

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`

for R in $JetR
do
   for C in $Centrality
   do
      ./Execute \
         --MC Input/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Shape PerfectInput/${Prefix}_R${R}_Centrality${C}_${Suffix}_PerfectReco.root \
         --Yield Input/${YieldPrefix}_R${R}_Centrality${C}_${YieldSuffix}.root \
         --Output Output/${Prefix}_R${R}_Centrality${C}_${Suffix}_Toy.root \
         --Fraction $Fraction
   done
done



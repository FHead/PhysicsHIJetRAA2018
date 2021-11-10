

Location=$1
Prefix=$2
Suffix=$3
IsPP=$4

JetR=`DHQuery GlobalSetting.dh Global JetR | sed 's/"//g'`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | sed 's/"//g'`
if [[ "$IsPP" == "1" ]]; then
   Centrality="Inclusive"
fi

for R in $JetR
do
   for C in $Centrality
   do
      ./Execute --Input $Location/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --Output Output/${Prefix}_R${R}_Centrality${C}_${Suffix}.root \
         --MCPrior false
   done
done




#!/bin/sh

TempFolder=Output/Parts/
mkdir -p $TempFolder
# rm ${TempFolder}/*root

mv Output/*Part*root $TempFolder

for i in `ls $TempFolder | cut -d '_' -f 2-3 | sort | uniq`
do
   hadd -k -f Output/TestRunMC_$i $TempFolder/*Part*_${i}
done

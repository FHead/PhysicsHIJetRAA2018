#!/bin/sh

TempFolder=Output/Parts/
mkdir -p $TempFolder

# mv Output/*Part*root $TempFolder

for Type in `ls $TempFolder | cut -d '_' -f 2 | sort | uniq`
do
   for Bin in `ls $TempFolder/*${Type}* | cut -d '_' -f 4-5 | sort | uniq`
   do
      echo ${Type} ${Bin}
      hadd -k -f Output/${Type}_${Bin} $TempFolder/*_${Type}_Part*_${Bin}
   done
done

#!/bin/sh

TempFolder=$1

if [[ "$TempFolder" == "" ]]; then
   TempFolder=Output/Parts
fi

# mkdir -p $TempFolder
# mv Output/*Part*root $TempFolder

for Type in `ls $TempFolder | cut -d '_' -f 2 | sort | uniq`
do
   for Bin in `ls $TempFolder/*_${Type}_* | cut -d '_' -f 4-5 | sort | uniq`
   do
      echo ${Type} ${Bin}
      hadd -k -f Output/${Type}_${Bin} $TempFolder/*_${Type}_Part*_${Bin}

      root -l -b -q Output/${Type}_${Bin}
      ls -lh Output/${Type}_${Bin}
   done
done

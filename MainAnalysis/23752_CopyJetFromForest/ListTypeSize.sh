#!/bin/bash
for i in `ls Output/*root | cut -d '_' -f 1 | sort | uniq | grep -v 'Output/Run'`
do
   echo $i: `du -csh ${i}_*root | grep total`
done

for i in `ls Output/Run_*root | cut -d '_' -f 1,2 | sort | uniq`
do
   echo $i: `du -csh ${i}_*root | grep total`
done

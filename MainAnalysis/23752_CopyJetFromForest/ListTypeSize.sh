#!/bin/bash
for i in `ls Output/*root | cut -d '_' -f 1 | sort | uniq`
do
   echo $i: `du -csh ${i}_*root | grep total`
done

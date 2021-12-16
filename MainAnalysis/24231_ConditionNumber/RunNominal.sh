#!/bin/bash

for i in `ls Input/*root | grep Nominal`
do
   State=`basename $i`
   State=${State/.root}
	./Execute --Input $i --Response HResponse --DHFile Condition.dh
   echo "Condition number: $i = `DHQuery Condition.dh $State ConditionNumber`"
done



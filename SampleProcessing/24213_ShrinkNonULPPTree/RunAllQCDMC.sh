#!/bin/bash

for i in QCDMC/*root
do
   echo $i
   # ./Execute --Input $i --Directories ppTrack
done

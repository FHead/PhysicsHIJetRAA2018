#!/bin/bash

for i in Input/*Fine*root
do
   ./Execute --Input $i --Output Output/`basename ${i/Fine}` --DHFile GlobalSetting.dh
done

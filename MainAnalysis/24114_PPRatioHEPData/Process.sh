#!/bin/bash

curl https://www.hepdata.net/download/table/ins1848440/Figure%206/1/yaml --output CMS-PPRatio.yaml

python3 Parse.py

cat PPRatio0.2.txt | TextToTree PPRatio0.2.root 7 "XMin:XMax:Y:StatMin:StatMax:SysMin:SysMax"
cat PPRatio0.3.txt | TextToTree PPRatio0.3.root 7 "XMin:XMax:Y:StatMin:StatMax:SysMin:SysMax"
cat PPRatio0.4.txt | TextToTree PPRatio0.4.root 7 "XMin:XMax:Y:StatMin:StatMax:SysMin:SysMax"
cat PPRatio0.6.txt | TextToTree PPRatio0.6.root 7 "XMin:XMax:Y:StatMin:StatMax:SysMin:SysMax"
cat PPRatio0.8.txt | TextToTree PPRatio0.8.root 7 "XMin:XMax:Y:StatMin:StatMax:SysMin:SysMax"

rm -f HIN18014PPRatio.root

./Execute --Input PPRatio0.2.root --Output HIN18014PPRatio.root --Graph R2
./Execute --Input PPRatio0.3.root --Output HIN18014PPRatio.root --Graph R3
./Execute --Input PPRatio0.4.root --Output HIN18014PPRatio.root --Graph R4
./Execute --Input PPRatio0.6.root --Output HIN18014PPRatio.root --Graph R6
./Execute --Input PPRatio0.8.root --Output HIN18014PPRatio.root --Graph R7


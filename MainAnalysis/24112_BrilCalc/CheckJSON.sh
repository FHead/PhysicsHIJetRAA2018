#!/bin/bash

Input=$1
DH=$2

if [[ "$DH" == "" ]]; then
   DH=GlobalSetting.dh
fi

brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_BRIL.json -i ${Input} -o temp.csv
BrilValue=`grep -v "^#" temp.csv | cut -d ',' -f 6 | Sum`

brilcalc lumi --normtag /cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json -i ${Input} -o temp.csv
PhysicsValue=`grep -v "^#" temp.csv | cut -d ',' -f 6 | Sum`

rm temp.csv

Tag=`basename $Input | sed "s/_Nominal//" | sed "s/_JSON.txt//"`

echo $Tag $BrilValue $PhysicsValue

DHSet $DH Lumi ${Tag/Fine}_BRIL double $BrilValue
DHSet $DH Lumi ${Tag/Fine}_PHYSICS double $PhysicsValue


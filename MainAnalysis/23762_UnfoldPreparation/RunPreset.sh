#!/bin/bash

echo Yay..

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_11_2_1_patch2/src/
eval `scramv1 runtime -sh`
cd /afs/cern.ch/work/c/chenyi//PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23762_UnfoldPreparation

export ProjectBase=/afs/cern.ch/work/c/chenyi//PhysicsWorkspace/HIJetRAA2018/
export PATH=$PATH:/afs/cern.ch/user/c/chenyi/RootMacros/

echo Running preset with argument = "$@"

eval `./ExecutePreset $@ | grep ^time`


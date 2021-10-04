#!/bin/sh

Input=$1
Output=$2
ScriptDir=$3

WorkDir=`pwd`

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_11_2_1_patch2/src/
eval `scramv1 runtime -sh`
cd $WorkDir

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/CommonCode/proxy/x509up_proxy

echo "Working directory = $WorkDir"

cat $ScriptDir/forest_miniAOD_112X_DATA_template.py | sed "s#__INPUT__#$Input#" > $WorkDir/run.py
cp $ScriptDir/Cert_326381-327564_HI_PromptReco_Collisions18_JSON.txt JSON.txt
cmsRun run.py

mv HiForestMiniAOD.root $Output





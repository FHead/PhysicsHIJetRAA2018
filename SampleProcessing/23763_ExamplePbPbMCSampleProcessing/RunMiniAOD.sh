#!/bin/sh

Input=$1
Output=$2

WorkDir=`pwd`

cd /afs/cern.ch/work/c/chenyi/CMSSW/CMSSW_11_2_1_patch2/src/
eval `scramv1 runtime -sh`
cd $WorkDir

ScriptDir=/afs/cern.ch/work/c/chenyi/PhysicsWorkspace/HIJetRAA2018/SampleProcessing/23763_ExamplePbPbMCSampleProcessing/

export X509_USER_PROXY=/afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/CommonCode/proxy/x509up_proxy

echo "Working directory = $WorkDir"

cat $ScriptDir/forest_miniAOD_112X_MC_template.py | sed "s#__INPUT__#$Input#" > $WorkDir/run.py
cmsRun run.py

mv HiForestMiniAOD.root /eos/cms/store/group/phys_heavyions/chenyi/Share/23763_ExampleMiniAOD/$Output





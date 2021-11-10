

CondorFile=SubmitMiniAOD.condor
OutputBase=/eos/cms/store/group/phys_heavyions/chenyi/Share/24143_ExampleMiniAOD/
mkdir -p $OutputBase

echo "Universe              = vanilla" > $CondorFile
echo "Executable            = `pwd`/RunMiniAOD.sh" >> $CondorFile
echo "should_transfer_files = NO" >> $CondorFile
echo "+JobFlavour           = \"workday\"" >> $CondorFile
echo >> $CondorFile
echo >> $CondorFile

Count=0
for File in `cat filelist.txt`
do
   echo "Arguments = $File ${OutputBase}/Output${Count}.root `pwd`" >> $CondorFile
   echo "Output    = Log/MiniAOD${Count}.out" >> $CondorFile
   echo "Error     = Log/MiniAOD${Count}.err" >> $CondorFile
   echo "Log       = Log/MiniAOD${Count}.log" >> $CondorFile
   echo "Queue" >> $CondorFile
   echo >> $CondorFile

   Count=`echo $Count | AddConst 1`
done

mkdir -p Log

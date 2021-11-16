
Submit=Submit.condor

echo "Universe              = vanilla" > $Submit
echo "Executable            = /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23762_UnfoldPreparation/RunPreset.sh" >> $Submit
echo "should_transfer_files = NO" >> $Submit
# echo "+JobFlavour           = \"microcentury\"" >> $Submit
echo "+JobFlavour           = \"workday\"" >> $Submit
echo >> $Submit

for R in 1 2 3 4 5 6 7 8 9
do
   # PbPb MC
   echo "Arguments = --Prefix PbPbMCRho --Suffix Nominal --MCTag Input/PbPbMCRho --DataTag Input/PbPbMCRho --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.0 --Flooring false --JetR $R" >> $Submit
   echo "Output    = Log/PbPbMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbMCNominal${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data
   echo "Arguments = --Prefix PbPbData --Suffix Nominal --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.0 --Flooring false --JetR $R" >> $Submit
   echo "Output    = Log/PbPbDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataNominal${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC up
   echo "Arguments = --Prefix PbPbData --Suffix JECUp --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 1.0 --Flooring false --JetR $R" >> $Submit
   echo "Output    = Log/PbPbDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC down
   echo "Arguments = --Prefix PbPbData --Suffix JECDown --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 1.0 --Flooring false --JetR $R" >> $Submit
   echo "Output    = Log/PbPbDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PP MC
   echo "Arguments = --Prefix PPMC --Suffix Nominal --MCTag Input/PPMC --DataTag Input/PPMC --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.0 --Flooring false --JetR $R --Centrality Inclusive" >> $Submit
   echo "Output    = Log/PPMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PPMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PPMCNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data
   echo "Arguments = --Prefix PPData --Suffix Nominal --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.0 --Flooring false --JetR $R --Centrality Inclusive" >> $Submit
   echo "Output    = Log/PPDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PPDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PPDataNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Up
   echo "Arguments = --Prefix PPData --Suffix JECUp --MCTag Input/PPMC --DataTag Input/PPData --Prefix PPData --Suffix JECUp --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 1.0 --Flooring false --JetR $R --Centrality Inclusive" >> $Submit
   echo "Output    = Log/PPDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Down
   echo "Arguments = --Prefix PPData --Suffix JECUp --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 1.0 --Flooring false --JetR $R --Centrality Inclusive" >> $Submit
   echo "Output    = Log/PPDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
done



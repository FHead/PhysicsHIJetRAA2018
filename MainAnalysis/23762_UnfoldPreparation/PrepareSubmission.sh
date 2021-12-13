
Submit=Submit.condor

echo "Universe              = vanilla" > $Submit
echo "Executable            = /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23762_UnfoldPreparation/RunPresetCopy.sh" >> $Submit
echo "should_transfer_files = NO" >> $Submit
# echo "+JobFlavour           = \"microcentury\"" >> $Submit
echo "+JobFlavour           = \"workday\"" >> $Submit
echo >> $Submit

for R in 1 2 3 4 5 6 7 8 9
do
   PPJERSF=$ProjectBase/CommonCode/jer/Summer19UL17_JRV3_MC/Summer19UL17_JRV3_MC_SF_AK4PF.txt
   PbPbJERSF=$ProjectBase/CommonCode/jer/Autumn18_RunD_V7b_MC/Autumn18_RunD_V7b_MC_SF_AK4PF.txt

   # PbPb MC
   echo "Arguments = --Prefix PbPbMCRho --Suffix Nominal --MCTag Input/PbPbMCRho --DataTag Input/PbPbMCRho --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJERSFFile false --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbMCNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data
   echo "Arguments = --Prefix PbPbData --Suffix Nominal --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJERSFFile true --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC up
   echo "Arguments = --Prefix PbPbData --Suffix JECUp --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJERSFFile true --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC down
   echo "Arguments = --Prefix PbPbData --Suffix JECDown --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJERSFFile true --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JER up
   echo "Arguments = --Prefix PbPbData --Suffix JERUp --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1 --Flooring false --JetR $R --DoCopy true --UseJERSFFile true --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbDataJERUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJERUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJERUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JER down
   echo "Arguments = --Prefix PbPbData --Suffix JERDown --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear -1 --Flooring false --JetR $R --DoCopy true --UseJERSFFile true --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbDataJERDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJERDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJERDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, Centrality up
   echo "Arguments = --Prefix PbPbData --Suffix CentralityUp --MCTag Input/PbPbMCRhoCentralityUp --DataTag Input/PbPbDataCentralityUp --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJERSFFile true --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbDataCentralityUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataCentralityUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataCentralityUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, Centrality down
   echo "Arguments = --Prefix PbPbData --Suffix CentralityDown --MCTag Input/PbPbMCRhoCentralityDown --DataTag Input/PbPbDataCentralityDown --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJERSFFile true --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PbPbDataCentralityDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataCentralityDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataCentralityDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP MC
   echo "Arguments = --Prefix PPMC --Suffix Nominal --MCTag Input/PPMC --DataTag Input/PPMC --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJERSFFile false --JERSF ${PbPbJERSF}" >> $Submit
   echo "Output    = Log/PPMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PPMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PPMCNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data
   echo "Arguments = --Prefix PPData --Suffix Nominal --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJERSFFile true --JERSF ${PPJERSF}" >> $Submit
   echo "Output    = Log/PPDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PPDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PPDataNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Up
   echo "Arguments = --Prefix PPData --Suffix JECUp --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJERSFFile true --JERSF ${PPJERSF}" >> $Submit
   echo "Output    = Log/PPDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Down
   echo "Arguments = --Prefix PPData --Suffix JECDown --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJERSFFile true --JERSF ${PPJERSF}" >> $Submit
   echo "Output    = Log/PPDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data, JER Up
   echo "Arguments = --Prefix PPData --Suffix JERUp --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJERSFFile true --JERSF ${PPJERSF}" >> $Submit
   echo "Output    = Log/PPDataJERUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJERUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJERUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data, JER Down
   echo "Arguments = --Prefix PPData --Suffix JERDown --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear -1 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJERSFFile true --JERSF ${PPJERSF}" >> $Submit
   echo "Output    = Log/PPDataJERDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJERDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJERDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
done



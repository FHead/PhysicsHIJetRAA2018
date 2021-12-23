#!/bin/bash

Submit=Submit.condor

# switch both to empty for reading binning from DHFile
Binning="--GenBins fine --RecoBins fine --GenMin 80 --RecoMin 80"
Fine="Fine"

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
   echo "Arguments = --Prefix PbPbMCRho --Suffix Nominal${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbMCRho --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbMCNominal${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data
   echo "Arguments = --Prefix PbPbData --Suffix Nominal${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataNominal${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC up
   echo "Arguments = --Prefix PbPbData --Suffix JECUp${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC down
   echo "Arguments = --Prefix PbPbData --Suffix JECDown${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JEC Quench
   echo "Arguments = --Prefix PbPbData --Suffix JECQuench${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift -0.035 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU false --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataJECQuench${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECQuench${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECQuench${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JEC No residual (MC as usual with phi, data also with phi)
   echo "Arguments = --Prefix PbPbData --Suffix JECNoResidual${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbDataNoResidual --GlobalSetting GlobalSetting.dh --Shift -0.035 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU false --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataJECNoResidual${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECNoResidual${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECNoResidual${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JEC No phi (MC no phi, data no phi, but L2Res is applied)
   echo "Arguments = --Prefix PbPbData --Suffix JECNoPhi${Fine} --MCTag Input/PbPbMCRhoNoPhiResidual --DataTag Input/PbPbDataNoPhiResidual --GlobalSetting GlobalSetting.dh --Shift -0.035 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU false --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataJECNoPhi${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECNoPhi${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECNoPhi${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JER up
   echo "Arguments = --Prefix PbPbData --Suffix JERUp${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.5 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataJERUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJERUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJERUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JER down
   echo "Arguments = --Prefix PbPbData --Suffix JERDown${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear -1.5 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataJERDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJERDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJERDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, no JER
   echo "Arguments = --Prefix PbPbData --Suffix NoJER${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataNoJER${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataNoJER${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataNoJER${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
 
   # PbPb Data, Flat JER smearing
   echo "Arguments = --Prefix PbPbData --Suffix FlatJER${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0.10 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataFlatJER${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataFlatJER${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataFlatJER${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
 
   # PbPb Data, Centrality up
   echo "Arguments = --Prefix PbPbData --Suffix CentralityUp${Fine} --MCTag Input/PbPbMCRhoCentralityUp --DataTag Input/PbPbDataCentralityUp --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataCentralityUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataCentralityUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataCentralityUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, Centrality down
   echo "Arguments = --Prefix PbPbData --Suffix CentralityDown${Fine} --MCTag Input/PbPbMCRhoCentralityDown --DataTag Input/PbPbDataCentralityDown --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataCentralityDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataCentralityDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataCentralityDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, MC Centrality
   echo "Arguments = --Prefix PbPbData --Suffix MCCentrality${Fine} --MCTag Input/PbPbMC --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PbPbDataMCCentrality${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataMCCentrality${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataMCCentrality${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PP MC
   echo "Arguments = --Prefix PPMC --Suffix Nominal${Fine} --MCTag Input/PPMC --DataTag Input/PPMC --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning" >> $Submit
   echo "Output    = Log/PPMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PPMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PPMCNominal${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data
   echo "Arguments = --Prefix PPData --Suffix Nominal${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning" >> $Submit
   echo "Output    = Log/PPDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PPDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PPDataNominal${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Up
   echo "Arguments = --Prefix PPData --Suffix JECUp${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning" >> $Submit
   echo "Output    = Log/PPDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Down
   echo "Arguments = --Prefix PPData --Suffix JECDown${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning" >> $Submit
   echo "Output    = Log/PPDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data, JER Up
   echo "Arguments = --Prefix PPData --Suffix JERUp${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.5 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning" >> $Submit
   echo "Output    = Log/PPDataJERUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJERUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJERUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data, JER Down
   echo "Arguments = --Prefix PPData --Suffix JERDown${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear -1.5 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} ${Binning}" >> $Submit
   echo "Output    = Log/PPDataJERDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJERDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJERDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
done



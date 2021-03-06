#!/bin/bash

Submit=Submit.condor

# switch both to empty for reading binning from DHFile
Binning="--GenBins fine --RecoBins fine --GenMin 80 --RecoMin 80"
Fine=Fine

# Use this for eta up to 1.3
# Eta=Eta13
# EtaString="--EtaMin -1.3 --EtaMax 1.3"

# Use this for eta up to 2.0
Eta=
EtaString="--EtaMin -2.0 --EtaMax 2.0"

echo "Universe              = vanilla" > $Submit
echo "Executable            = /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetRAA2018/MainAnalysis/23762_UnfoldPreparation/RunPresetCopy.sh" >> $Submit
echo "should_transfer_files = NO" >> $Submit
# echo "+JobFlavour           = \"microcentury\"" >> $Submit
echo "+JobFlavour           = \"workday\"" >> $Submit
echo >> $Submit

JetR=`DHQuery GlobalSetting.dh Global JetR`
Centrality=`DHQuery GlobalSetting.dh Global Centrality | tr ' ' ','`

for R in $JetR
do
   PPJERSF=$ProjectBase/CommonCode/jer/Summer19UL17_JRV3_MC/Summer19UL17_JRV3_MC_SF_AK4PF.txt
   PbPbJERSF=$ProjectBase/CommonCode/jer/Autumn18_RunD_V7b_MC/Autumn18_RunD_V7b_MC_SF_AK4PF.txt

   # PbPb MC
   echo "Arguments = --Prefix PbPbMCRho --Suffix Nominal${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbMCRho --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbMCNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data
   echo "Arguments = --Prefix PbPbData --Suffix Nominal${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC up
   echo "Arguments = --Prefix PbPbData --Suffix JECUp${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC down
   echo "Arguments = --Prefix PbPbData --Suffix JECDown${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JEC up aggressive
   echo "Arguments = --Prefix PbPbData --Suffix JECAggressiveUp${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 1.0 --JEUOffset -0.03 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJECAggressiveUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECAggressiveUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECAggressiveUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JEC down aggressive
   echo "Arguments = --Prefix PbPbData --Suffix JECAggressiveDown${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift -1.0 --JEUOffset -0.03 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJECAggressiveDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECAggressiveDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECAggressiveDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JEC Quench
   echo "Arguments = --Prefix PbPbData --Suffix JECQuench${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.035 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU false --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJECQuench${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECQuench${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECQuench${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JEC No residual (MC as usual with phi, data also with phi)
   echo "Arguments = --Prefix PbPbData --Suffix JECNoResidual${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbDataNoResidual --GlobalSetting GlobalSetting.dh --Shift 0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU false --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJECNoResidual${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECNoResidual${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECNoResidual${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JEC No phi (MC no phi, data no phi, but L2Res is applied)
   echo "Arguments = --Prefix PbPbData --Suffix JECNoPhi${Eta}${Fine} --MCTag Input/PbPbMCRhoNoPhiResidual --DataTag Input/PbPbDataNoPhiResidual --GlobalSetting GlobalSetting.dh --Shift 0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU false --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJECNoPhi${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJECNoPhi${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJECNoPhi${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, JER up
   echo "Arguments = --Prefix PbPbData --Suffix JERUp${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.5 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJERUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJERUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJERUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, JER down
   echo "Arguments = --Prefix PbPbData --Suffix JERDown${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear -1.5 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataJERDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataJERDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataJERDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, no JER
   echo "Arguments = --Prefix PbPbData --Suffix NoJER${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataNoJER${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataNoJER${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataNoJER${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
 
   # PbPb Data, Flat JER smearing
   echo "Arguments = --Prefix PbPbData --Suffix FlatJER${Eta}${Fine} --MCTag Input/PbPbMCRho --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0.10 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataFlatJER${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataFlatJER${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataFlatJER${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
 
   # PbPb Data, Centrality up
   echo "Arguments = --Prefix PbPbData --Suffix CentralityUp${Eta}${Fine} --MCTag Input/PbPbMCRhoCentralityUp --DataTag Input/PbPbDataCentralityUp --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataCentralityUp${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataCentralityUp${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataCentralityUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, Centrality down
   echo "Arguments = --Prefix PbPbData --Suffix CentralityDown${Eta}${Fine} --MCTag Input/PbPbMCRhoCentralityDown --DataTag Input/PbPbDataCentralityDown --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataCentralityDown${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataCentralityDown${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataCentralityDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, MC Centrality
   echo "Arguments = --Prefix PbPbData --Suffix MCCentrality${Eta}${Fine} --MCTag Input/PbPbMC --DataTag Input/PbPbData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataMCCentrality${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataMCCentrality${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataMCCentrality${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PbPb Data, Stored Centrality
   echo "Arguments = --Prefix PbPbData --Suffix StoredCentrality${Eta}${Fine} --MCTag Input/PbPbMC --DataTag Input/PbPbDataStoredCentrality --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataStoredCentrality${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataStoredCentrality${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataStoredCentrality${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PbPb Data, No Jet ID
   echo "Arguments = --Prefix PbPbData --Suffix NoJetID${Eta}${Fine} --MCTag Input/PbPbMC --DataTag Input/PbPbDataNoJetID --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PbPbDataNoJetID${R}.out" >> $Submit
   echo "Error     = Log/PbPbDataNoJetID${R}.err" >> $Submit
   echo "Log       = Log/PbPbDataNoJetID${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP MC
   echo "Arguments = --Prefix PPMC --Suffix Nominal${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPMC --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPMCNominal${R}.out" >> $Submit
   echo "Error     = Log/PPMCNominal${R}.err" >> $Submit
   echo "Log       = Log/PPMCNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data
   echo "Arguments = --Prefix PPData --Suffix Nominal${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataNominal${R}.out" >> $Submit
   echo "Error     = Log/PPDataNominal${R}.err" >> $Submit
   echo "Log       = Log/PPDataNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Up
   echo "Arguments = --Prefix PPData --Suffix JECUp${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataJECUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Down
   echo "Arguments = --Prefix PPData --Suffix JECDown${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataJECDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data, JEC Up aggressive
   echo "Arguments = --Prefix PPData --Suffix JECAggressiveUp${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 1.0 --JEUOffset -0.02 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataJECAggressiveUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECAggressiveUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECAggressiveUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data, JEC Down aggressive
   echo "Arguments = --Prefix PPData --Suffix JECAggressiveDown${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift -1.0 --JEUOffset -0.02 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataJECAggressiveDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJECAggressiveDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJECAggressiveDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data, JER Up
   echo "Arguments = --Prefix PPData --Suffix JERUp${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.5 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataJERUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataJERUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataJERUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data, JER Down
   echo "Arguments = --Prefix PPData --Suffix JERDown${Eta}${Fine} --MCTag Input/PPMC --DataTag Input/PPData --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear -1.5 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} ${Binning} ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataJERDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataJERDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataJERDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP MC EOY
   echo "Arguments = --Prefix PPMCEOY --Suffix Nominal${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPMCEOY --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile false --JERSF ${PbPbJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPMCEOYNominal${R}.out" >> $Submit
   echo "Error     = Log/PPMCEOYNominal${R}.err" >> $Submit
   echo "Log       = Log/PPMCEOYNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data EOY
   echo "Arguments = --Prefix PPDataEOY --Suffix Nominal${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPDataEOY --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataEOYNominal${R}.out" >> $Submit
   echo "Error     = Log/PPDataEOYNominal${R}.err" >> $Submit
   echo "Log       = Log/PPDataEOYNominal${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data EOY, JEC Up
   echo "Arguments = --Prefix PPDataEOY --Suffix JECUp${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPDataEOY --GlobalSetting GlobalSetting.dh --Shift 1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataEOYJECUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataEOYJECUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataEOYJECUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data EOY, JEC Down
   echo "Arguments = --Prefix PPDataEOY --Suffix JECDown${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPDataEOY --GlobalSetting GlobalSetting.dh --Shift -1.0 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataEOYJECDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataEOYJECDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataEOYJECDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data EOY, JEC Up Aggressive
   echo "Arguments = --Prefix PPDataEOY --Suffix JECAggressiveUp${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPDataEOY --GlobalSetting GlobalSetting.dh --Shift 1.0 --JEUOffset -0.01 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataEOYJECAggressiveUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataEOYJECUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataEOYJECUp${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit

   # PP Data EOY, JEC Down Aggressive
   echo "Arguments = --Prefix PPDataEOY --Suffix JECAggressiveDown${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPDataEOY --GlobalSetting GlobalSetting.dh --Shift -1.0 --JEUOffset -0.01 --Smear 0 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataEOYJECAggressiveDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataEOYJECAggressiveDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataEOYJECAggressiveDown${R}.log" >> $Submit
   echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data EOY, JER Up
   echo "Arguments = --Prefix PPDataEOY --Suffix JERUp${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPDataEOY --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear 1.5 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} $Binning --Centrality $Centrality ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataEOYJERUp${R}.out" >> $Submit
   echo "Error     = Log/PPDataEOYJERUp${R}.err" >> $Submit
   echo "Log       = Log/PPDataEOYJERUp${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
   
   # PP Data EOY, JER Down
   echo "Arguments = --Prefix PPDataEOY --Suffix JERDown${Eta}${Fine} --MCTag Input/PPMCEOY --DataTag Input/PPDataEOY --GlobalSetting GlobalSetting.dh --Shift 0.0 --Smear -1.5 --Flooring false --JetR $R --Centrality Inclusive --DoCopy true --UseJEU true --UseJERSFFile true --JERSF ${PPJERSF} ${Binning} ${EtaString}" >> $Submit
   echo "Output    = Log/PPDataEOYJERDown${R}.out" >> $Submit
   echo "Error     = Log/PPDataEOYJERDown${R}.err" >> $Submit
   echo "Log       = Log/PPDataEOYJERDown${R}.log" >> $Submit
   # echo "Queue" >> $Submit
   echo >> $Submit
done



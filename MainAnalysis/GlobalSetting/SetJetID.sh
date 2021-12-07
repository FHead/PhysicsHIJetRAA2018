#!/bin/bash

DH=GlobalSetting.dh

for i in 1 2 3 4 5 6 7 8 9
do
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_NHFMinCut float -999
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_NHFMaxCut float 0.9
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_NEFMinCut float -999
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_NEFMaxCut float 0.9
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_CHFMinCut float 0
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_CHFMaxCut float 999
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_CEFMinCut float -999
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_CEFMaxCut float 0.8
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_MUFMinCut float -999
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_MUFMaxCut float 0.8
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_MultiplicityMinCut int 1
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_MultiplicityMaxCut int 99999
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_ChargedMultiplicityMinCut int 0
   DHSet ${DH} JetID PPMC_R${i}_CentralityInclusive_ChargedMultiplicityMaxCut int 99999
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_NHFMinCut float -999
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_NHFMaxCut float 0.9
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_NEFMinCut float -999
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_NEFMaxCut float 0.9
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_CHFMinCut float 0
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_CHFMaxCut float 999
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_CEFMinCut float -999
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_CEFMaxCut float 0.8
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_MUFMinCut float -999
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_MUFMaxCut float 0.8
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_MultiplicityMinCut int 1
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_MultiplicityMaxCut int 99999
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_ChargedMultiplicityMinCut int 0
   DHSet ${DH} JetID PPData_R${i}_CentralityInclusive_ChargedMultiplicityMaxCut int 99999
done

for i in 1 2 3 4 5 6 7 8 9
do
   for j in 0to10 10to30 30to50 50to90
   do
      # PP Style
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NHFMinCut float -999
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NHFMaxCut float 0.9
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NEFMinCut float -999
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NEFMaxCut float 0.9
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CHFMinCut float 0
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CHFMaxCut float 999
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CEFMinCut float -999
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CEFMaxCut float 0.8
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MUFMinCut float -999
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MUFMaxCut float 0.8
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MultiplicityMinCut int 1
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MultiplicityMaxCut int 99999
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_ChargedMultiplicityMinCut int 0
      # DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_ChargedMultiplicityMaxCut int 99999

      # Looser cuts
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_NHFMinCut float -999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_NHFMaxCut float 0.9
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_NEFMinCut float -999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_NEFMaxCut float 999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_CHFMinCut float 0
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_CHFMaxCut float 999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_CEFMinCut float -999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_CEFMaxCut float 999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_MUFMinCut float -999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_MUFMaxCut float 0.8
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_MultiplicityMinCut int -99999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_MultiplicityMaxCut int 99999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_ChargedMultiplicityMinCut int -99999
      DHSet ${DH} JetID PbPbMC_R${i}_Centrality${j}_ChargedMultiplicityMaxCut int 99999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NHFMinCut float -999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NHFMaxCut float 0.9
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NEFMinCut float -999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_NEFMaxCut float 999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CHFMinCut float 0
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CHFMaxCut float 999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CEFMinCut float -999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_CEFMaxCut float 999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MUFMinCut float -999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MUFMaxCut float 0.8
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MultiplicityMinCut int -99999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_MultiplicityMaxCut int 99999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_ChargedMultiplicityMinCut int -99999
      DHSet ${DH} JetID PbPbData_R${i}_Centrality${j}_ChargedMultiplicityMaxCut int 99999
   done
done


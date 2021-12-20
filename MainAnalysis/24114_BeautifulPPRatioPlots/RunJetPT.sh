#!/bin/bash

PP1NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R1_CentralityInclusive_Default | tr -d '"'`Prior
PP2NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R2_CentralityInclusive_Default | tr -d '"'`Prior
PP3NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R3_CentralityInclusive_Default | tr -d '"'`Prior
PP4NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R4_CentralityInclusive_Default | tr -d '"'`Prior
PP5NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R5_CentralityInclusive_Default | tr -d '"'`Prior
PP6NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R6_CentralityInclusive_Default | tr -d '"'`Prior
PP7NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R7_CentralityInclusive_Default | tr -d '"'`Prior
PP8NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R8_CentralityInclusive_Default | tr -d '"'`Prior
PP9NP=`DHQuery GlobalSetting.dh PriorToUse PPData_R9_CentralityInclusive_Default | tr -d '"'`Prior

PPR1=Input/PPData_R1_CentralityInclusive_Nominal_${PP1NP}.root
PPR2=Input/PPData_R2_CentralityInclusive_Nominal_${PP2NP}.root
PPR3=Input/PPData_R3_CentralityInclusive_Nominal_${PP3NP}.root
PPR4=Input/PPData_R4_CentralityInclusive_Nominal_${PP4NP}.root
PPR5=Input/PPData_R5_CentralityInclusive_Nominal_${PP5NP}.root
PPR6=Input/PPData_R6_CentralityInclusive_Nominal_${PP6NP}.root
PPR7=Input/PPData_R7_CentralityInclusive_Nominal_${PP7NP}.root
PPR8=Input/PPData_R8_CentralityInclusive_Nominal_${PP8NP}.root
PPR9=Input/PPData_R9_CentralityInclusive_Nominal_${PP9NP}.root

SysR19=CombinedSystematics/PPDataRatio_R1R9_CentralityInclusive.root
SysR29=CombinedSystematics/PPDataRatio_R2R9_CentralityInclusive.root
SysR39=CombinedSystematics/PPDataRatio_R3R9_CentralityInclusive.root
SysR49=CombinedSystematics/PPDataRatio_R4R9_CentralityInclusive.root
SysR59=CombinedSystematics/PPDataRatio_R5R9_CentralityInclusive.root
SysR69=CombinedSystematics/PPDataRatio_R6R9_CentralityInclusive.root
SysR79=CombinedSystematics/PPDataRatio_R7R9_CentralityInclusive.root
SysR89=CombinedSystematics/PPDataRatio_R8R9_CentralityInclusive.root

./Execute --Output Plots/Base1.2.pdf \
   --BaseFileName ${PPR9} \
   --BaseRLabel 9 \
   --FileName $PPR1,$PPR2,$PPR3,$PPR4,$PPR5,$PPR6,$PPR7,$PPR8 \
   --Systematics $SysR19,$SysR29,$SysR39,$SysR49,$SysR59,$SysR69,$SysR79,$SysR89 \
   --RLabel 1,2,3,4,5,6,7,8 \
   --Color 0,1,2,3,4,5,6,7 \
   --XMin 199 --XMax 1200

SysR18=CombinedSystematics/PPDataRatio_R1R8_CentralityInclusive.root
SysR28=CombinedSystematics/PPDataRatio_R2R8_CentralityInclusive.root
SysR38=CombinedSystematics/PPDataRatio_R3R8_CentralityInclusive.root
SysR48=CombinedSystematics/PPDataRatio_R4R8_CentralityInclusive.root
SysR58=CombinedSystematics/PPDataRatio_R5R8_CentralityInclusive.root
SysR68=CombinedSystematics/PPDataRatio_R6R8_CentralityInclusive.root
SysR78=CombinedSystematics/PPDataRatio_R7R8_CentralityInclusive.root

./Execute --Output Plots/Base1.0.pdf \
   --BaseFileName ${PPR8} \
   --BaseRLabel 8 \
   --FileName $PPR3,$PPR4,$PPR5,$PPR6,$PPR7 \
   --Systematics $SysR38,$SysR48,$SysR58,$SysR68,$SysR78 \
   --RLabel 3,4,5,6,7 \
   --Color 1,2,5,3,4 \
   --XMin 199 --XMax 1200

./Execute --Output Plots/Validation.pdf \
   --BaseFileName ${PPR8} \
   --BaseRLabel 8 \
   --FileName $PPR2,$PPR3,$PPR4,$PPR6,$PPR7 \
   --Systematics $SysR28,$SysR38,$SysR48,$SysR68,$SysR78 \
   --RLabel 2,3,4,6,7 \
   --Color 0,1,2,3,4 \
   --XMin 199 --XMax 1000 \
   --AddHIN18014 true


#!/bin/bash

DHRemove GlobalSetting.dh TAA 
DHRemove GlobalSetting.dh TAAErrorUp
DHRemove GlobalSetting.dh TAAErrorDown

# These values from previous RAA paper
DHSet GlobalSetting.dh "TAA" "0to10" float 23.2
DHSet GlobalSetting.dh "TAAErrorUp" "0to10" float 0.4
DHSet GlobalSetting.dh "TAAErrorDown" "0to10" float 0.7
DHSet GlobalSetting.dh "TAA" "10to30" float 11.5
DHSet GlobalSetting.dh "TAAErrorUp" "10to30" float 0.3
DHSet GlobalSetting.dh "TAAErrorDown" "10to30" float 0.4
DHSet GlobalSetting.dh "TAA" "30to50" float 3.82
DHSet GlobalSetting.dh "TAAErrorUp" "30to50" float 0.21
DHSet GlobalSetting.dh "TAAErrorDown" "30to50" float 0.21
DHSet GlobalSetting.dh "TAA" "50to90" float 0.440
DHSet GlobalSetting.dh "TAAErrorUp" "50to90" float 0.049
DHSet GlobalSetting.dh "TAAErrorDown" "50to90" float 0.032
# These values from 1710.07098
DHSet GlobalSetting.dh "TAA" "0to5" float 26.1
DHSet GlobalSetting.dh "TAAErrorUp" "0to5" float 2.2
DHSet GlobalSetting.dh "TAAErrorDown" "0to5" float 2.2
DHSet GlobalSetting.dh "TAA" "5to10" float 20.4
DHSet GlobalSetting.dh "TAAErrorUp" "5to10" float 1.7
DHSet GlobalSetting.dh "TAAErrorDown" "5to10" float 1.7
DHSet GlobalSetting.dh "TAA" "10to15" float 16.1
DHSet GlobalSetting.dh "TAAErrorUp" "10to15" float 1.4
DHSet GlobalSetting.dh "TAAErrorDown" "10to15" float 1.4
DHSet GlobalSetting.dh "TAA" "15to20" float 12.7
DHSet GlobalSetting.dh "TAAErrorUp" "15to20" float 1.2
DHSet GlobalSetting.dh "TAAErrorDown" "15to20" float 1.2
DHSet GlobalSetting.dh "TAA" "20to25" float 9.88
DHSet GlobalSetting.dh "TAAErrorUp" "20to25" float 1.1
DHSet GlobalSetting.dh "TAAErrorDown" "20to25" float 1.1
DHSet GlobalSetting.dh "TAA" "25to30" float 7.63
DHSet GlobalSetting.dh "TAAErrorUp" "25to30" float 0.95
DHSet GlobalSetting.dh "TAAErrorDown" "25to30" float 0.95
DHSet GlobalSetting.dh "TAA" "30to35" float 5.81
DHSet GlobalSetting.dh "TAAErrorUp" "30to35" float 0.84
DHSet GlobalSetting.dh "TAAErrorDown" "30to35" float 0.84
DHSet GlobalSetting.dh "TAA" "35to40" float 4.36
DHSet GlobalSetting.dh "TAAErrorUp" "35to40" float 0.74
DHSet GlobalSetting.dh "TAAErrorDown" "35to40" float 0.74
DHSet GlobalSetting.dh "TAA" "40to45" float 3.2
DHSet GlobalSetting.dh "TAAErrorUp" "40to45" float 0.64
DHSet GlobalSetting.dh "TAAErrorDown" "40to45" float 0.64
DHSet GlobalSetting.dh "TAA" "45to50" float 2.3
DHSet GlobalSetting.dh "TAAErrorUp" "45to50" float 0.54
DHSet GlobalSetting.dh "TAAErrorDown" "45to50" float 0.54
DHSet GlobalSetting.dh "TAA" "50to55" float 1.62
DHSet GlobalSetting.dh "TAAErrorUp" "50to55" float 0.45
DHSet GlobalSetting.dh "TAAErrorDown" "50to55" float 0.45
DHSet GlobalSetting.dh "TAA" "55to60" float 1.11
DHSet GlobalSetting.dh "TAAErrorUp" "55to60" float 0.36
DHSet GlobalSetting.dh "TAAErrorDown" "55to60" float 0.36
DHSet GlobalSetting.dh "TAA" "60to65" float 0.738
DHSet GlobalSetting.dh "TAAErrorUp" "60to65" float 0.28
DHSet GlobalSetting.dh "TAAErrorDown" "60to65" float 0.28
DHSet GlobalSetting.dh "TAA" "65to70" float 0.479
DHSet GlobalSetting.dh "TAAErrorUp" "65to70" float 0.22
DHSet GlobalSetting.dh "TAAErrorDown" "65to70" float 0.22
DHSet GlobalSetting.dh "TAA" "70to75" float 0.304
DHSet GlobalSetting.dh "TAAErrorUp" "70to75" float 0.16
DHSet GlobalSetting.dh "TAAErrorDown" "70to75" float 0.16
DHSet GlobalSetting.dh "TAA" "75to80" float 0.19
DHSet GlobalSetting.dh "TAAErrorUp" "75to80" float 0.12
DHSet GlobalSetting.dh "TAAErrorDown" "75to80" float 0.12
DHSet GlobalSetting.dh "TAA" "80to85" float 0.118
DHSet GlobalSetting.dh "TAAErrorUp" "80to85" float 0.086
DHSet GlobalSetting.dh "TAAErrorDown" "80to85" float 0.086
DHSet GlobalSetting.dh "TAA" "85to90" float 0.0752
DHSet GlobalSetting.dh "TAAErrorUp" "85to90" float 0.06
DHSet GlobalSetting.dh "TAAErrorDown" "85to90" float 0.06
DHSet GlobalSetting.dh "TAA" "90to95" float 0.0484
DHSet GlobalSetting.dh "TAAErrorUp" "90to95" float 0.041
DHSet GlobalSetting.dh "TAAErrorDown" "90to95" float 0.041
DHSet GlobalSetting.dh "TAA" "95to100" float 0.0301
DHSet GlobalSetting.dh "TAAErrorUp" "95to100" float 0.025
DHSet GlobalSetting.dh "TAAErrorDown" "95to100" float 0.025


#!/bin/bash

DHRemove GlobalSetting.dh TAA 
DHRemove GlobalSetting.dh TAAErrorUp
DHRemove GlobalSetting.dh TAAErrorDown
# These values from CMS twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/Glauber5TeVPbPbNewParameters
DHSet GlobalSetting.dh "TAA" "0to10" float 23.05
DHSet GlobalSetting.dh "TAAErrorUp" "0to10" float 0.42
DHSet GlobalSetting.dh "TAAErrorDown" "0to10" float 0.42
DHSet GlobalSetting.dh "TAA" "10to30" float 11.6
DHSet GlobalSetting.dh "TAAErrorUp" "10to30" float 0.26
DHSet GlobalSetting.dh "TAAErrorDown" "10to30" float 0.26
DHSet GlobalSetting.dh "TAA" "30to50" float 3.950
DHSet GlobalSetting.dh "TAAErrorUp" "30to50" float 0.132
DHSet GlobalSetting.dh "TAAErrorDown" "30to50" float 0.132
DHSet GlobalSetting.dh "TAA" "50to90" float 0.5803
DHSet GlobalSetting.dh "TAAErrorUp" "50to90" float 0.0288
DHSet GlobalSetting.dh "TAAErrorDown" "50to90" float 0.0288
DHSet GlobalSetting.dh "TAA" "50to70" float 0.9957
DHSet GlobalSetting.dh "TAAErrorUp" "50to70" float 0.0500
DHSet GlobalSetting.dh "TAAErrorDown" "50to70" float 0.0500
DHSet GlobalSetting.dh "TAA" "70to90" float 0.1650
DHSet GlobalSetting.dh "TAAErrorUp" "70to90" float 0.0077
DHSet GlobalSetting.dh "TAAErrorDown" "70to90" float 0.0077
# Fine values from CMS twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/Glauber5TeVPbPbNewParameters
DHSet GlobalSetting.dh "TAA"  "0to5"   float 25.70
DHSet GlobalSetting.dh "TAA"  "5to10"  float 20.40
DHSet GlobalSetting.dh "TAA" "10to15"  float 16.13
DHSet GlobalSetting.dh "TAA" "15to20"  float 12.66
DHSet GlobalSetting.dh "TAA" "20to25"  float 9.916
DHSet GlobalSetting.dh "TAA" "25to30"  float 7.680
DHSet GlobalSetting.dh "TAA" "30to35"  float 5.684
DHSet GlobalSetting.dh "TAA" "35to40"  float 4.385
DHSet GlobalSetting.dh "TAA" "40to45"  float 3.228
DHSet GlobalSetting.dh "TAA" "45to50"  float 2.325
DHSet GlobalSetting.dh "TAA" "50to55"  float 1.634
DHSet GlobalSetting.dh "TAA" "55to60"  float 1.118
DHSet GlobalSetting.dh "TAA" "60to65"  float 0.7469
DHSet GlobalSetting.dh "TAA" "65to70"  float 0.4838
DHSet GlobalSetting.dh "TAA" "70to75"  float 0.3032
DHSet GlobalSetting.dh "TAA" "75to80"  float 0.1852
DHSet GlobalSetting.dh "TAA" "80to85"  float 0.1088
DHSet GlobalSetting.dh "TAA" "85to90"  float 0.06273
DHSet GlobalSetting.dh "TAA" "90to95"  float 0.03296
DHSet GlobalSetting.dh "TAA" "95to100" float 0.01768




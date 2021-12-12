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

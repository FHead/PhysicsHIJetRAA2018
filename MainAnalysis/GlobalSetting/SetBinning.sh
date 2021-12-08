#!/bin/bash

# Initial naive Binning
# DHSet GlobalSetting.dh "Binning" "GenPT" string "20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500"
# DHSet GlobalSetting.dh "Binning" "RecoPT" string "20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,110,120,130,140,150,160,170,180,190,200,220,240,260,280,300,325,350,375,400,425,450,475,500,525,550,575,600,625,650,675,700,725,750,775,800,825,850,875,900,925,950,975,1000,1100,1200,1300,1400,1500"

# ATLAS Binning
# DHSet GlobalSetting.dh "Binning" "GenPT" string "20,25,30,35,40,45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1100,1200,1300,1400,1500"
# DHSet GlobalSetting.dh "Binning" "RecoPT" string "20,25,30,35,40,45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1100,1200,1300,1400,1500"

# Binning to be used for MinPT = 40
# DHSet GlobalSetting.dh "Binning" "GenPT" string "45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1200,1500"
# DHSet GlobalSetting.dh "Binning" "RecoPT" string "45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,447,501,562,631,708,794,891,1000,1200,1500"

# Reduced binning above 400 GeV
DHSet GlobalSetting.dh "Binning" "GenPT" string "45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,501,631,794,1000,1200,1500"
DHSet GlobalSetting.dh "Binning" "RecoPT" string "45,50,56,63,71,79,89,100,112,126,141,158,178,200,224,251,282,316,355,398,501,631,794,1000,1200,1500"

# Some more phase space cuts
DHSet GlobalSetting.dh "Binning" "GenMin" float 40
DHSet GlobalSetting.dh "Binning" "RecoMin" float 40
DHSet GlobalSetting.dh "Binning" "JetExclusion" string "-0.5,1.5,0.0,1.0,-2.0,-1.0,-1.8,-0.9"

# Default underflow/overflow.  Not really used
DHSet GlobalSetting.dh "Binning" "PTUnderflow" int 13
DHSet GlobalSetting.dh "Binning" "PTOverflow" int 0
condor_q -nobatch | cat | grep Run_PbPbMC[A-Za-z]*_Part -o | sort | uniq -c

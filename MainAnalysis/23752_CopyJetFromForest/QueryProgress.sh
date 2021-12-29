echo by type
condor_q -nobatch | cat | grep Run_[A-Za-z]*_Part -o | cut -d '_' -f 2 | sort | uniq -c
echo


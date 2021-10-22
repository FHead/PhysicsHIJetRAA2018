

for i in `condor_q -nobatch | grep chenyi | grep " R " | awk '{print $1}'`
do
   echo $i
   echo
   condor_tail -maxbytes 10000000 $i | grep Running
   echo
   echo
done

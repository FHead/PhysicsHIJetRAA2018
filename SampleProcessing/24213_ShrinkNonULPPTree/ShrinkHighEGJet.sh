
#!/bin/bash

for i in HighEGJet/000*/*root
do
   echo `basename $i`
   hadd -f7 /tmp/chenyi/TempEG.root $i
   mv /tmp/chenyi/TempEG.root HighEGJet/`basename $i`
   rm $i
done


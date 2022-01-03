
#!/bin/bash

for i in QCDMC/NotYet/*root
do
   echo `basename $i`
   hadd -f7 /tmp/chenyi/Temp.root $i
   mv /tmp/chenyi/Temp.root QCDMC/`basename $i`
   rm $i
done


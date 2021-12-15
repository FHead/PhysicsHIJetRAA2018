#!/bin/bash

for i in *xml
do
   # echo 5.19995e+03 > ${i/xml/txt}
   grep bin-edge $i | tr '><' ' ' | awk '{print $2}' >> ${i/xml/txt}
done

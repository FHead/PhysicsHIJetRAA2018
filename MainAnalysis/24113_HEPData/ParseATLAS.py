#!/usr/local/bin/python3

import sys
import yaml
Data = yaml.safe_load(open('ATLAS-R04.yaml'))

XList = Data['independent_variables'][0]['values']
YList = Data['dependent_variables'][0]['values']

N = len(XList)

import numpy as np

Result = np.zeros((N, 9))

for i in range(0, N):
    Result[i,0] = XList[i]['low']
    Result[i,1] = XList[i]['high']
    Result[i,2] = YList[i]['value']
    Result[i,3] = YList[i]['errors'][1]['symerror']
    Result[i,4] = YList[i]['errors'][1]['symerror']
    Result[i,5] = -YList[i]['errors'][0]['asymerror']['minus']
    Result[i,6] = YList[i]['errors'][0]['asymerror']['plus']
    Result[i,7] = YList[i]['errors'][2]['symerror']
    Result[i,8] = YList[i]['errors'][2]['symerror']

np.savetxt('ATLAS-R04.txt', Result)



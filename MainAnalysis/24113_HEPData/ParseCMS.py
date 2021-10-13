#!/usr/local/bin/python3

import sys

R = '02'
if len(sys.argv) > 1:
    R = sys.argv[1]

import yaml
Data = yaml.safe_load(open('CMS-R'+R+'.yaml'))

XList = Data['independent_variables'][0]['values']
YList = Data['dependent_variables'][-1]['values']

N = len(XList)

import numpy as np

Result = np.zeros((N, 9))

for i in range(0, N):
    Result[i,0] = XList[i]['low']
    Result[i,1] = XList[i]['high']
    Result[i,2] = YList[i]['value']
    Result[i,3] = -YList[i]['errors'][0]['asymerror']['minus']
    Result[i,4] = YList[i]['errors'][0]['asymerror']['plus']
    Result[i,5] = -YList[i]['errors'][1]['asymerror']['minus']
    Result[i,6] = YList[i]['errors'][1]['asymerror']['plus']
    Result[i,7] = -YList[i]['errors'][2]['asymerror']['minus']
    Result[i,8] = YList[i]['errors'][2]['asymerror']['plus']

np.savetxt('CMS-R'+R+'.txt', Result)



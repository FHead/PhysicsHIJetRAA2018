#!/usr/local/bin/python3

import sys

import yaml
Data = yaml.safe_load(open('CMS-PPRatio.yaml'))

XList = Data['independent_variables'][0]['values']
YList = Data['dependent_variables']

DataCount = len(XList)

import numpy as np

for Column in YList:
    Result = np.zeros((DataCount, 7))

    R = 0
    for Item in Column['qualifiers']:
        if Item['name'] == 'R':
            R = Item['value']

    for i in range(0, DataCount):
        Result[i, 0] = XList[i]['low']
        Result[i, 1] = XList[i]['high']
        Result[i, 2] = Column['values'][i]['value']
        Result[i, 3] = -Column['values'][i]['errors'][0]['asymerror']['minus']
        Result[i, 4] = Column['values'][i]['errors'][0]['asymerror']['plus']
        Result[i, 5] = -Column['values'][i]['errors'][1]['asymerror']['minus']
        Result[i, 6] = Column['values'][i]['errors'][1]['asymerror']['plus']

    np.savetxt(f'PPRatio{R}.txt', Result)


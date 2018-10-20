#!/usr/bin/env python

import sys

runNo   = sys.argv[1]
evenNo  = sys.argv[2]
spec    = sys.argv[3]
setting = sys.argv[4]

if (setting == 'singles') : filename = './REPORT_OUTPUT/%s/PRODUCTION/replay_%s_production_%s_%s.report' % (spec.upper(), spec, runNo, evenNo)
if (setting == 'coin')    : filename = './REPORT_OUTPUT/%s/PRODUCTION/replay_%s_%s_production_%s_%s.report' % (spec.upper(), spec, setting, runNo, evenNo)

f    = open(filename)
fout = open('output.txt','w')

objList = ['Run #', 
           'BCM1 Beam Cut Current', 'BCM2 Beam Cut Current', 'BCM4A Beam Cut Current', 'BCM4B Beam Cut Current', 'BCM4C Beam Cut Current',
           'SING FID TRACK EFFIC', 'SHMS TRIG5 Computer Live Time',
           'Plane 1', 'Plane 2', 'Plane 3', 'Plane 4', '3_of_4 EFF']

if (setting == 'singles') :
    psList     = ['1', '2', '3']
    psNameList = ['3/4', 'EL-REAL', 'EL-CLEAN']

if (setting == 'coin') :
    psList     = ['1', '2', '3', '4', '5', '6']
    psNameList = ['SHMS 3/4', 'SHMS EL-REAL', 'HMS EL-REAL', 'HMS 3/4', 'HMS EL-REAL x SHMS 3/4', 'SHMS 3/4 x HMS 3/4']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(objList) :
        if (objList[index] in data[0]) :
            if (index == 0) :
                fout.write('\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
                if (setting == 'coin') : fout.write('50k %s %s Report File Summary' % (setting.upper(), spec.upper()))
                else : fout.write('50k %s Report File Summary' % spec.upper())
                fout.write('\n\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
            #if ('HADRON' in data[0]) : continue
            fout.write(data[0] + ' : ' + data[1])

    data = line.split('=')
    for index, ps in enumerate(psList) :
        if ('Ps%s_factor' % psList[index] in data[0]) :
            line = data[0]
            line = line.replace('Ps%s_factor' % psList[index], 'DAQ Pre-Scale Setting %s' % psNameList[index])
            fout.write(line + ':' + data[1])

fout.close()
f.close()

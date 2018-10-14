#!/usr/bin/env python

import sys

runNo  = sys.argv[1]
evenNo = sys.argv[2]

filename = './REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_%s.report' % (runNo, evenNo)

f    = open(filename)
fout = open('output.txt','w')

objList = ['Run #', 
           'SHMS Run Length',
           'SHMS BCM1 Beam Cut Current', 'SHMS BCM1 Beam Cut Charge',
           'SHMS BCM2 Beam Cut Current', 'SHMS BCM2 Beam Cut Charge',
           'SHMS BCM4A Beam Cut Current', 'SHMS BCM4A Beam Cut Charge',
           'SHMS BCM4B Beam Cut Current', 'SHMS BCM4B Beam Cut Charge',
           'SHMS BCM4C Beam Cut Current', 'SHMS BCM4C Beam Cut Charge',
           'SHMS Unser Beam Cut Current', 'SHMS Unser Beam Cut Charge',
           'SHMS_pTRIG1 Pre-triggers', 'SHMS_pTRIG3 Pre-triggers', 'SHMS_pTRIG5 Pre-triggers',
           'SHMS_pTRIG1 Pre-scaled Pre-triggers', 'SHMS_pTRIG3 Pre-scaled Pre-triggers', 'SHMS_pTRIG5 Pre-scaled Pre-triggers',
           'Coin ROC2 pTRIG1 Accepted Triggers', 'Coin ROC2 pTRIG3 Accepted Triggers', 'Coin ROC2 pTRIG5 Accepted Triggers']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(objList) :
        if (objList[index] in data[0]) :
            if (index == 0) :
                fout.write('\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
                fout.write('Kaon-LT Report Summary')
                fout.write('\n\n=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:=:\n\n')
            fout.write(data[0] + ' : ' + data[1])
            if (index == 19) :
                COIN_RAW = data[1].split("[")
            if (index == 22) :
                COIN_ACC = data[1].split("[")
COIN_LT = float(COIN_ACC[0]) / float(COIN_RAW[0])
fout.write('Computer Live Time for COIN Trigger (%): ')
fout.write(str(COIN_LT))
f.close()

shms_file = '../REPORT_OUTPUT/SHMS/PRODUCTION/replay_shms_coin_production_%s_50000.report' % (runNo)
#print('./REPORT_OUTPUT/COIN/PRODUCTION/output_coin_production_%s_%s.report' % (runNo, evenNo))
f    = open(shms_file)
fout.write('\n')
shmsList = ['HADRON SING FID TRACK EFFIC']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(shmsList) :
        if (shmsList[index] in data[0]) :
            fout.write(data[0] + ' : ' + data[1])
f.close()

hms_file = '../REPORT_OUTPUT/HMS/PRODUCTION/replay_hms_coin_production_%s_50000.report' % (runNo)
#print('./REPORT_OUTPUT/COIN/PRODUCTION/output_coin_production_%s_%s.report' % (runNo, evenNo))
f    = open(hms_file)
#fout.write('\n')
hmsList = ['E SING FID TRACK EFFIC']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(hmsList) :
        if (hmsList[index] in data[0]) :
            fout.write(data[0] + ' : ' + data[1])
f.close()

replay_file = './REPORT_OUTPUT/COIN/PRODUCTION/output_coin_production_%s_%s.report' % (runNo, evenNo)
f    = open(replay_file)
fout.write('\n\n')
replayList = ['Missing Ref times']

for line in f:
    data = line.split(':')
    for index, obj in enumerate(replayList) :
        if (replayList[index] in data[0]) :
            fout.write(data[0] + ' : ' + data[1])
f.close()
fout.close()

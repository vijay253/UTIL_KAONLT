#!/usr/bin/env python
import time,sys,os,argparse,atexit,subprocess,math


XVALS,YVALS=[],[]
START=0
NCHAN=28


def getScalars():
    zvals=[]
    pzvals=[]
    chan=[]
    overflow=[]
    pchan=[]
    XVALS[:] = []
    YVALS[:] = []
    
    #file = open("output.txt",'r')
    #row = file.readlines()
    lines = subprocess.check_output(["getscalers","hcvme08"])
    for line in lines.splitlines():
        #print line
    #for line in row:
        info = line.split()
        info[0] = info[0].replace(':', '')
        if info[0].isdigit():
           chan.append(int (info[0])+1)
           temp  = info[1].rpartition('(')[0]
           temp2 =  info[1].rpartition('(')[2]
           temp3 =  temp2.rpartition(')')[0]
           overflow.append(int(temp3))
           zvals.append(float(temp))
           
    pzvals.append(zvals[255]) # 1MhZ
    pzvals.append(zvals[249]) # BCM4A
    pzvals.append(zvals[192]) # pTRIG1
    pzvals.append(zvals[194]) # pTRIG3
    pzvals.append(zvals[196]) # pTRIG5
    return [pzvals,overflow]


def calcRates(rates,rates2):
    left,right,maximum=0,0,0
    for ii in range(28):#len(XVALS)):
        xx,yy,zz,zz2=XVALS[ii],YVALS[ii],rates[ii],rates2[ii]
        if xx==1:left+=(zz2-zz)/10
        else : right+=(zz2-zz)/10
        if (zz2-zz)/10>maximum: maximum=(zz2-zz)/10
    return [left,right,maximum]


def makeTime():
    datime=TDatime()
    return '%d/%d/%d %.2d:%.2d:%.2d'%(datime.GetDay(),
             datime.GetMonth(),
             datime.GetYear(),
             datime.GetHour(),
             datime.GetMinute(),
             datime.GetSecond())





def main():


    timeCul = 0
    timeCulCh = 0
    chargeCul = 0
    HMSCul = 0
    SHMSCul = 0
    CoinCul = 0
    while True:

        [zvals,overflow1] = getScalars()
        time.sleep(5)
        [zvals2,overflow2] = getScalars()
        diff = zvals2[0]-zvals[0]
        if diff>0 :
          time1 = (zvals2[0]-zvals[0])/1000000.
          current = ((zvals2[1]-zvals[1])/time1-762.6)/9279.
          t1rate=  (zvals2[2]-zvals[2])/time1/1000.
          t4rate=  (zvals2[3]-zvals[3])/time1/1000.
          t6rate=  (zvals2[4]-zvals[4])/time1/1000.
          acc_rate = t1rate*t4rate*80/1000./1000.
          charge = 0
          timeCul = timeCul + time1/60.
          if current>2. : 
              charge = current*time1
              chargeCul = chargeCul + charge/1000.
              timeCulCh = timeCulCh + time1/60.
          print('Total Time = {0:10.2f} min, Beam on time = {1:10.5f} min , Total Charge = {2:10.5f} mC'.format(timeCul,timeCulCh,chargeCul))
          print('SHMS T1 rate kHz = {0:10.5f} , HMS T3 Rate kHz = {1:10.5f}'.format(t1rate,t4rate))
          print('COIN T5 Rate Hz = {0:10.5f}, COIN Acc Rate Hz = {1:10.5f} '.format(t6rate*1000,acc_rate*1000))
   
        else :
          if diff==0:
            print(' Time diff = {0} {1}, Assume Run started  and reset counters'.format(zvals2[0],zvals[0]))
            timeCul = 0
            chargeCul = 0
            timeCulCh = 0

if __name__=='__main__': main()



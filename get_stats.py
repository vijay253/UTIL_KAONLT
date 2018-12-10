#!/usr/bin/env python

import time,sys,os,argparse,atexit,subprocess,math

ANGLE = sys.argv[1]
CURRENT = sys.argv[2]

ANGLE_low = float(ANGLE)-0.3
ANGLE_high = float(ANGLE)+0.3

CURRENT_low = float(CURRENT)-1.5
CURRENT_high = float(CURRENT)+1.5

def getRunInfo():

    Run = []
    Type = [] 
    Target = [] 
    Comment=[]
    lambda_tmp1 = []
    lambda_tmp2 = []
    lamb = []
    KAONLTLIST="test_runlist_2.csv"

    f = open(KAONLTLIST)

    for line in f:
        linespace = line.strip()
        data = linespace.split("\t")
        if "#" in linespace or "Run" in linespace or not linespace.strip() or "JUNK" in linespace or "Dummy" in linespace :
            #or "Heep" in linespace or "HEEP" in linespace or "Carbon" in linespace or "C-1.5%" in linespace:
            print("----->" + str(data))
        else :
            pass
            #print(str(data))
            Run.append(data[0])
            Type.append(data[1])
            Target.append(data[2])
            #if data[1] == "Prod" or data[1] == "PROD":
            #pass
            #lambda_tmp1 = data[26].split()
            #lambda_tmp2 = lambda_tmp1[0].split("!")
            #print("Lambda " + str(lambda_tmp2))
            #if lambda_tmp2[1].isdigit() :
            #   pass
            #  print("Lambda " + lambda_tmp2[1])
            #  Comment.append(data[26])
            # lamb.append(lambda_tmp2[1])
            #else : 
            #   print("----->" + str(data))
            #print("Lambdas for run %s is %s" % (Run,lamb))
            #else : continue

    f.close()

    return[Run, Type,Target,Comment, lamb]


def getValues():
    

    P_SHMS=[] 
    Theta_SHMS=[] 
    P_HMS=[] 
    Theta_HMS=[] 
    Ebeam=[] 
    Current=[] 
    PS1=[] 
    PS3=[] 
    PS5=[] 
    HMS_Rate=[] 
    SHMS_Rate=[] 
    COIN_Rate=[]
    Charge=[] 
    Raw_coin=[] 
    SHMS_h_tracking=[] 
    pTRIG1 = []
    pTRIG3 = []
    pTRIG5 = []

    [Run, Type,Target,Comment, lamb] = getRunInfo()
    #print("Run list %s" % (Run))
    i=0
    while True :        
        #print("Run %s" % (Run[i]))        
        report_1="../REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_-1.report" % (Run[i])
        report_2="../REPORT_OUTPUT/COIN/PRODUCTION/replay_coin_production_%s_-1.report" % (Run[i])
        report_4="../MON_OUTPUT/REPORT/reportMonitor_shms_%s_50000.txt" % (Run[i])
        report_5="OUTPUT/scalers_Run%s.txt" % (Run[i])
        f    = open(report_1)
        curList = ['SHMS P Central', 'SHMS Angle', 'HMS P Central', 'HMS Angle','Beam energy',
                   'SHMS BCM4B Beam Cut Current','SHMS_pTRIG3 Pre-triggers', 'SHMS_pTRIG1 Pre-triggers', 
                   'SHMS_pTRIG5 Pre-scaled Pre-triggers', 'SHMS BCM4B Beam Cut Charge',
                   'Coin ROC2 pTRIG5 Accepted Triggers']        
        for line in f:
            data = line.split(':')
            for index, obj in enumerate(curList) :
                if (curList[index] in data[0]) : 
                    if(index == 0) :
                       moment_shms_tmp = data[1].split(" ")
                    if(index == 1) :
                       angle_shms_tmp = data[1].split(" ")
                    if(index == 2) :
                       moment_hms_tmp = data[1].split(" ")
                    if(index == 3) :
                       angle_hms_tmp = data[1].split(" ")
                    if(index == 4) :
                        beam_tmp = data[1].split(" ")
                    if(index == 5) :
                        current_tmp = data[1].split(" ")
                    if (index == 6) : 
                        HMSRATE_tmp = data[1].split(" ")
                    if (index == 7) : 
                        SHMSRATE_tmp = data[1].split(" ")
                    if (index == 8) : 
                        COINRATE_tmp = data[1].split(" ")
                    if (index == 9) : 
                        charge_tmp = data[1].split(" ")
                    if (index == 10) : 
                        RAWCOIN_tmp = data[1].split(" ")
        moment_shms = float(moment_shms_tmp[1])
        angle_shms = float(angle_shms_tmp[1])
        moment_hms = float(moment_hms_tmp[1])
        angle_hms = float(angle_hms_tmp[1])
        beam = float(beam_tmp[1])
        current=float(current_tmp[1])
        HMSRATE=float(HMSRATE_tmp[6])
        SHMSRATE=float(SHMSRATE_tmp[6])
        COINRATE=float(COINRATE_tmp[6])
        charge=float(charge_tmp[1])
        RAWCOIN=float(RAWCOIN_tmp[1])
        #print(str(moment_shms) + "-momentum_shms\n")
        #print(str(angle_shms) + "-angle_shms\n")
        #print(str(moment_hms) + "-momentum_hms\n")
        #print(str(angle_hms) + "-angle_hms\n")
        #print(str(beam) + "-beam\n")
        #print(str(current) + "-current\n")
        #print(str(HMSRATE) + "-HMSRATE\n")
        #print(str(SHMSRATE) + "-SHMSRATE\n")
        #print(str(COINRATE) + "-COINRATE\n")
        #print(str(charge) + "-charge\n")
        #print(str(RAWCOIN) + "-RAWCOIN\n")
        P_SHMS.append(moment_shms)
        Theta_SHMS.append(angle_shms)
        P_HMS.append(moment_hms)
        Theta_HMS.append(angle_hms)
        Ebeam.append(beam)
        Current.append(current)
        HMS_Rate.append(HMSRATE)
        SHMS_Rate.append(SHMSRATE)
        COIN_Rate.append(COINRATE)
        Charge.append(charge)
        Raw_coin.append(RAWCOIN)
        f.close()                    
        f    = open(report_2)        
        psList = ['Ps1_factor','Ps3_factor','Ps5_factor']        
        psActual = ['1','2','3','5','9','17','33','65','129','257','513','1025','2049','4097','8193','16385','32769']        
        psValue = ['0','1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16']        
        for line in f:
            data = line.split('=')
            for index, obj in enumerate(psList) :
                if (psList[index] in data[0]) : 
                    if (index == 0) :  
                        ps1_tmp = data[1].split(" ")
                    if (index == 1) : 
                        ps3_tmp = data[1].split(" ")
                    if (index == 2) :
                        ps5_tmp = data[1].split(" ")
        ps1=float(ps1_tmp[1])
        ps3=float(ps3_tmp[1])
        ps5=float(ps5_tmp[1])
        j=0
        for index in psActual:
            if (float(index) == ps1) :
                psv1 = str(psValue[j])
            if (float(index) == ps3) :
                psv3 = str(psValue[j])
            if (float(index) == ps5) :
                psv5 = str(psValue[j])
            j=j+1
        #print(str(psv1) + "-PS1\n")
        ##print(str(ps1) + "\n")
        #print(str(psv3) + "-PS3\n")
        ##print(str(ps3) + "\n")
        #print(str(psv5) + "-PS5\n")
        ##print(str(ps5) + "\n")
        PS1.append(psv1)
        PS3.append(psv3)
        PS5.append(psv5)
        f.close()
        f    = open(report_4)        
        monList = ['HADRON SING FID TRACK EFFIC']
        for line in f:
            data = line.split(':')
            for index, obj in enumerate(monList) :
                if (monList[index] in data[0]) :
                    if(index == 0) :  
                        hadtrack_tmp = data[1].split(" ")
        hadtrack=float(hadtrack_tmp[4])
        #print(str(hadtrack) + "-hadtrack\n")
        SHMS_h_tracking.append(hadtrack)
        f.close()
        f    = open(report_5)        
        scalList = ['SHMS_pTRIG1 Pre-scaled Pre-triggers','SHMS_pTRIG3 Pre-scaled Pre-triggers', 'SHMS_pTRIG5 Pre-triggers']        
        for line in f:
            data = line.split(':')
            for index, obj in enumerate(scalList) :
                if (scalList[index] in data[0]) :
                    if(index == 0) :  
                        ptrig1_tmp = data[1].split(" ")
                    if(index == 1) :  
                        ptrig3_tmp = data[1].split(" ")
                    if(index == 2) :  
                        ptrig5_tmp = data[1].split(" ")
        ptrig1=float(ptrig1_tmp[3])
        ptrig3=float(ptrig3_tmp[3])
        ptrig5=float(ptrig5_tmp[3])
        #print(str(ptrig1) + "-ptrig1\n")
        #print(str(ptrig3) + "-ptrig3\n")
        #print(str(ptrig5) + "-ptrig5\n")
        pTRIG1.append(ptrig1)
        pTRIG3.append(ptrig3)
        pTRIG5.append(ptrig5)
        f.close()        
        i=i+1
        if i == len(Run) :
            break

    return[P_SHMS, Theta_SHMS, P_HMS, Theta_HMS, Ebeam, Current, PS1, PS3, PS5, HMS_Rate, SHMS_Rate, COIN_Rate, Charge, Raw_coin, SHMS_h_tracking, pTRIG1, pTRIG3, pTRIG5]


def main() :

    [Run, Type,Target,Comment, lamb] = getRunInfo()
    
    [P_SHMS, Theta_SHMS, P_HMS, Theta_HMS, Ebeam, Current, PS1, PS3, PS5, HMS_Rate, SHMS_Rate, COIN_Rate, Charge, Raw_coin, SHMS_h_tracking, pTRIG1, pTRIG3, pTRIG5] = getValues()
    
    tot_charge = []
    tot_lambda = []
    comment = []
    charge_goal = 7188
    i=0
    
    print("\nAngle must be between %0.3f and %0.3f" % (ANGLE_low,ANGLE_high))
    print("Current must be between %0.1f and %0.1f\n" % (CURRENT_low,CURRENT_high))
    
    while True :
        if ANGLE_low < float(Theta_SHMS[i]) < ANGLE_high :
                if CURRENT_low < float(Current[i]) < CURRENT_high : 
                    #print("Theta_SHMS for run %s is %s" % (Run,Theta_SHMS))
                    #print("Current for run %s is %s" % (Run,Current))
                    tot_charge.append(float(Charge[i]))
                    #tot_lambda.append(float(lamb[i]))
                    #comment.append(Comment[i])
                    print("Run %s meets requirements [SHMS Angle is %s, Current is %s, Charge is %s]" % (Run[i],Theta_SHMS[i],Current[i],Charge[i]))
        i=i+1
        if i == len(Run) :
            break
        
    #print("Total Charge is  %s, Total lambdas are %s" % (sum(tot_charge),sum(tot_lambda)))
    print("\nTotal Charge is  %0.2f, %0.1f%% of stat goal\n" % (sum(tot_charge),(sum(tot_charge)/charge_goal)*100))
    print("%0.1f hours to complete setting at this current (100%% efficiency)" % (charge_goal/(float(CURRENT)*(10e-3)*60*60)))
    print("%0.1f hours to complete setting at this current (75%% efficiency)\n" % ((charge_goal)/(float(CURRENT)*.75*(10e-3)*60*60)))

if __name__=='__main__': main()

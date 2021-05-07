#! /usr/bin/python

# May 07, 2020 Vijay Kumar, University of Regina

# Import relevant packages
import uproot as up
import numpy as np
import root_numpy as rnp
import pandas as pd
import root_pandas as rpd
import ROOT
import scipy
import scipy.integrate as integrate
import matplotlib.pyplot as plt
import sys, math, os, subprocess

sys.path.insert(0, 'python/')
# Check the number of arguments provided to the script
if len(sys.argv)-1!=2:
    print("!!!!! ERROR !!!!!\n Expected 3 arguments\n Usage is with - ROOTfilePrefix RunNumber MaxEvents \n!!!!! ERROR !!!!!")
    sys.exit(1)
# Input params - run number and max number of events
runNum = sys.argv[1]
MaxEvent = sys.argv[2]

USER = subprocess.getstatusoutput("whoami") # Grab user info for file finding
HOST = subprocess.getstatusoutput("hostname")
if ("farm" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("qcd" in HOST[1]):
    REPLAYPATH = "/group/c-kaonlt/USERS/%s/hallc_replay_lt" % USER[1]
elif ("lark.phys.uregina" in HOST[1]):
    REPLAYPATH = "/home/%s/work/JLab/hallc_replay_lt" % USER[1]

# Add more path setting as needed in a similar manner
OUTPATH = "%s/UTIL_KAONLT/scripts/pid/src/PYTHON_EFFICIENCY_SCRIPTS/OUTPUT" % REPLAYPATH 
CUTPATH = "%s/UTIL_KAONLT/DB/CUTS" % REPLAYPATH
sys.path.insert(0, '%s/UTIL_KAONLT/bin/python/' % REPLAYPATH)
import kaonlt as klt # Import kaonlt module, need the path setting line above prior to importing this

print("Running as %s on %s, hallc_replay_lt path assumed as %s" % (USER[1], HOST[1], REPLAYPATH))
# Construct the name of the rootfile based upon the info we provided
rootName = "%s/UTIL_KAONLT/ROOTfiles/coin_replay_Full_%s_%s.root" % (REPLAYPATH, runNum, MaxEvent)
 
# Read stuff from the main event tree
e_tree = up.open(rootName)["T"]
CTime_eKCoinTime_ROC1           = e_tree.array("CTime.eKCoinTime_ROC1")
CTime_ePiCoinTime_ROC1          = e_tree.array("CTime.ePiCoinTime_ROC1")
CTime_epCoinTime_ROC1           = e_tree.array("CTime.epCoinTime_ROC1")
#P_hgcer_goodAdcTdcDiffTime      = e_tree.array("P.hgcer.goodAdcTdcDiffTime")
P_hgcer_goodAdcTdcDiffTime      = e_tree.array("CTime.epCoinTime_ROC1")
P_hod_goodscinhit               = e_tree.array("P.hod.goodscinhit")
P_hod_betanotrack               = e_tree.array("P.hod.betanotrack")
P_hod_goodstarttime             = e_tree.array("P.hod.goodstarttime")
P_dc_InsideDipoleExit           = e_tree.array("P.dc.InsideDipoleExit")
P_dc_ntrack                     = e_tree.array("P.dc.ntrack")
P_RF_tdcTime                    = e_tree.array("T.coin.pRF_tdcTime")
P_hod_fpHitsTime                = e_tree.array("P.hod.fpHitsTime")
H_cal_etotnorm                  = e_tree.array("H.cal.etotnorm")
P_hgcer_npe                     = e_tree.array("P.hgcer.npe")
P_cal_fly_earray                = e_tree.array("P.cal.fly.earray")
P_cal_pr_eplane                 = e_tree.array("P.cal.pr.eplane")
P_gtr_beta                      = e_tree.array("P.gtr.beta")
P_gtr_xp                        = e_tree.array("P.gtr.th") # xpfp -> Theta
P_gtr_yp                        = e_tree.array("P.gtr.ph") # ypfp -> Phi
P_gtr_p                         = e_tree.array("P.gtr.p")
P_gtr_dp                        = e_tree.array("P.gtr.dp")
P_cal_etotnorm                  = e_tree.array("P.cal.etotnorm")
P_cal_etottracknorm             = e_tree.array("P.cal.etottracknorm")
P_aero_npeSum                   = e_tree.array("P.aero.npeSum")
P_hgcer_npeSum                  = e_tree.array("P.hgcer.npeSum")
P_hgcer_xAtCer                  = e_tree.array("P.hgcer.xAtCer")
P_hgcer_yAtCer                  = e_tree.array("P.hgcer.yAtCer")
P_aero_xAtCer                   = e_tree.array("P.aero.xAtAero")
P_aero_yAtCer                   = e_tree.array("P.aero.yAtAero")
P_gtr_x                         = e_tree.array("P.gtr.x")
P_gtr_y                         = e_tree.array("P.gtr.y")
emiss                           = e_tree.array("P.kin.secondary.emiss") 
pmiss                           = e_tree.array("P.kin.secondary.pmiss")

r = klt.pyRoot()
# Specify the file which contains the cuts we want to use
fout = '%s/UTIL_KAONLT/DB/CUTS/run_type/CUT_FILE.cuts' % REPLAYPATH
# read in cuts file and make dictionary
c = klt.pyPlot(REPLAYPATH)
readDict = c.read_dict(fout,runNum)
# This method calls several methods in kaonlt package. It is required to create properly formated
# dictionaries. The evaluation must be in the analysis script because the analysis variables (i.e. the
# leaves of interest) are not defined in the kaonlt package. This makes the system more flexible
# overall, but a bit more cumbersome in the analysis script. Perhaps one day a better solution will be
# implimented.
def make_cutDict(cut,inputDict=None):

    global c

    c = klt.pyPlot(REPLAYPATH,readDict)
    x = c.w_dict(cut)
    print("%s" % cut)
    print("x ", x)
    
    if inputDict == None:
        inputDict = {}
        
    for key,val in readDict.items():
        if key == cut:
            inputDict.update({key : {}})

    for i,val in enumerate(x):
        tmp = x[i]
        if tmp == "":
            continue
        else:
            inputDict[cut].update(eval(tmp))
        
    return inputDict

# Add the cuts that we want to use from our specified file to the cut dictionary, note, we're only adding two of our three defined cuts to our cut dict
# Acceptance, beta and calorimeter cuts applied  
cutDict = make_cutDict("PION_SAMPLE")
cutDict = make_cutDict("KAON_SAMPLE", cutDict)
cutDict = make_cutDict("PROTON_SAMPLE", cutDict )
c = klt.pyPlot(REPLAYPATH,cutDict)

# Define a function to return a dictionary of the events we want
# Arrays we generate in our dict should all be of the same length (in terms of # elements in the array) to keep things simple
def SHMS_events(): 
    NoCut_Events_SHMS = [P_hgcer_goodAdcTdcDiffTime, CTime_eKCoinTime_ROC1, CTime_ePiCoinTime_ROC1, CTime_epCoinTime_ROC1, P_hod_goodscinhit, P_hod_betanotrack, P_hod_goodstarttime, P_dc_InsideDipoleExit, P_dc_ntrack, H_cal_etotnorm, P_gtr_beta, P_gtr_xp, P_gtr_yp, P_gtr_p, P_gtr_dp, P_cal_etotnorm, P_cal_etottracknorm, P_aero_npeSum, P_hgcer_npeSum, P_hgcer_xAtCer, P_hgcer_yAtCer,  P_aero_xAtCer, P_aero_yAtCer, P_cal_fly_earray, P_cal_pr_eplane, P_gtr_x, P_gtr_y, emiss, pmiss]
    SHMS_Events_Info = [(PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) for (PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) in zip(*NoCut_Events_SHMS)]

    # Create (currently empty) arrays of our SHMS events for Cut1 and Cut2, we also have a temp array of our uncut data
    Cut_Events_SHMS_tmp = NoCut_Events_SHMS
    P_Events_CUT1 = []
    P_Events_CUT2 = []
    P_Events_CUT3 = []

    #Apply our cuts to the data and save our new arrays
    for arr in   Cut_Events_SHMS_tmp:
        P_Events_CUT1.append(c.add_cut(arr, "PION_SAMPLE"))
        P_Events_CUT2.append(c.add_cut(arr, "KAON_SAMPLE"))
        P_Events_CUT3.append(c.add_cut(arr, "PROTON_SAMPLE"))
              
    # Again, strictly force this to be an array and NOT a list
    P_Events_CUT1 = [(PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) for (PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot,Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) in zip(*P_Events_CUT1)]
    P_Events_CUT2 = [(PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) for (PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole,Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot,Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) in zip(*P_Events_CUT2)]
    P_Events_CUT3 = [(PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) for (PhgcAdcTdc, CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, Pntrack, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot,Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) in zip(*P_Events_CUT3)]
    SHMS_Events = {
        "SHMS_Events": SHMS_Events_Info,
        "SHMS_PION_SAMPLE": P_Events_CUT1,
        "SHMS_KAON_SAMPLE": P_Events_CUT2,
        "SHMS_PROTON_SAMPLE": P_Events_CUT3,
    }

    return SHMS_Events

def main():
    # Run our functions and get a dict from each
    SHMS_Events_Data = SHMS_events()
    
    # This is just the list of branches we use from the initial root file for each dict
    # They're the "headers" of the data frame we create - i.e. they're going to be the branches in our new root file
    # Note - I don't like re-defining this here as it's very prone to errors if you included (or removed something) earlier but didn't modify it here
    SHMS_Data_Header = ["P_hgcer_goodAdcTdcDiffTime", "CTime_eKCoinTime_ROC1","CTime_ePiCoinTime_ROC1","CTime_epCoinTime_ROC1", "P_hod_goodscinhit", "P_hod_betanotrack", "P_hod_goodstarttime", "P_dc_InsideDipoleExit", "P_dc_ntrack", "H_cal_etotnorm", "P_gtr_beta","P_gtr_xp","P_gtr_yp","P_gtr_p","P_gtr_dp","P_cal_etotnorm", "P_cal_etottracknorm", "P_aero_npeSum", "P_hgcer_npeSum", "P_hgcer_xAtCer", "P_hgcer_yAtCer", "P_aero_xAtCer", "P_aero_yAtCer","P_cal_fly_earray", "P_cal_pr_eplane", "P_gtr_x", "P_gtr_y", "emiss", "pmiss"]
    data = {} # Create an empty dictionary

    d = SHMS_Events_Data  

    #for d in (All_Events_Data): # Convert individual dictionaries into a "dict of dicts"
    data.update(d) # For every dictionary we give above, add its keys to the new dict
    data_keys = list(data.keys()) # Create a list of all the keys in all dicts added above, each is an array of data

    for i in range (0, len(data_keys)):
        # Set the headers for our data frame
        if("SHMS_" in data_keys[i]):
            DFHeader=list(SHMS_Data_Header)
        else:
            continue
 
        if (i == 0): # For the first case, start writing to file
            pd.DataFrame(data.get(data_keys[i]), columns = DFHeader, index = None).to_root("%s/pid_%s_%s.root" % (OUTPATH, runNum, MaxEvent), key ="%s" % data_keys[i])
        elif (i != 0): # For any but the first case, append it to our file
            pd.DataFrame(data.get(data_keys[i]), columns = DFHeader, index = None).to_root("%s/pid_%s_%s.root" % (OUTPATH, runNum, MaxEvent), key ="%s" % data_keys[i], mode ='a') 
                    
if __name__ == '__main__':
    main()

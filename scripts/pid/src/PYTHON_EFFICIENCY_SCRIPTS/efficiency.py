#! /usr/bin/python

# Oct 11, 2020 Vijay Kumar, University of Regina

# A short python demo script demonstrating opening up a root file, using uproot to grab some info and then save it as a new rootfile
# This time, we also define and apply some cuts to our SHMS events

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
if len(sys.argv)-1!=3:
    print("!!!!! ERROR !!!!!\n Expected 3 arguments\n Usage is with - ROOTfilePrefix RunNumber MaxEvents \n!!!!! ERROR !!!!!")
    sys.exit(1)
# Input params - run number and max number of events
ROOTPrefix = sys.argv[1]
runNum = sys.argv[2]
MaxEvent = sys.argv[3]

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
rootName = "%s/UTIL_KAONLT/ROOTfiles/%s_%s_%s.root" % (REPLAYPATH, ROOTPrefix, runNum, MaxEvent)

# Read stuff from the main event tree, here we're just going to get some quantities for the acceptance for the HMS/SHMS
e_tree = up.open(rootName)["T"]
# SHMS info
CTime_eKCoinTime_ROC1           = e_tree.array("CTime.eKCoinTime_ROC1")
CTime_ePiCoinTime_ROC1          = e_tree.array("CTime.ePiCoinTime_ROC1")
CTime_epCoinTime_ROC1           = e_tree.array("CTime.epCoinTime_ROC1")
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
P_aero_npeSum                   = e_tree.array("P.aero.npeSum")
P_hgcer_npeSum                  = e_tree.array("P.hgcer.npeSum")
P_hgcer_xAtCer                  = e_tree.array("P.hgcer.xAtCer")
P_hgcer_yAtCer                  = e_tree.array("P.hgcer.yAtCer")
P_gtr_x                         = e_tree.array("P.gtr.x")
P_gtr_y                         = e_tree.array("P.gtr.y")

r = klt.pyRoot()
# Specify the file which contains the cuts we want to use
fout = '%s/UTIL_KAONLT/DB/CUTS/run_type/pid_eff.cuts' % REPLAYPATH
# read in cuts file and make dictionary
c = klt.pyPlot(None)
readDict = c.read_dict(fout,runNum)
# This method calls several methods in kaonlt package. It is required to create properly formated
# dictionaries. The evaluation must be in the analysis script because the analysis variables (i.e. the
# leaves of interest) are not defined in the kaonlt package. This makes the system more flexible
# overall, but a bit more cumbersome in the analysis script. Perhaps one day a better solution will be
# implimented.
def make_cutDict(cut,inputDict=None):

    global c

    c = klt.pyPlot(readDict)
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
# Pions cuts 
cutDict = make_cutDict("p_picut_eff")
cutDict = make_cutDict("p_picut_eff_no_hgcer",cutDict)
cutDict = make_cutDict("p_picut_eff_no_aero",cutDict)
cutDict = make_cutDict("p_picut_eff_no_cal",cutDict)
#Positron cuts
cutDict = make_cutDict("p_ecut_eff_no_hgcer",cutDict)
cutDict = make_cutDict("p_ecut_eff",cutDict)
# Kaons cuts
cutDict = make_cutDict("p_kcut_eff",cutDict)
cutDict = make_cutDict("p_kcut_eff_no_hgcer",cutDict)
# Protons cuts
cutDict = make_cutDict("p_pcut_eff",cutDict)
cutDict = make_cutDict("p_pcut_eff_no_hgcer",cutDict)
#SHMS cuts with no cal, hgc and cal
cutDict = make_cutDict("p_cut_eff_no_cal_hgcer",cutDict)
cutDict = make_cutDict("p_cut_eff_no_hgcer_aero_cal",cutDict)
c = klt.pyPlot(cutDict)

# Define a function to return a dictionary of the events we want
# Arrays we generate in our dict should all be of the same length (in terms of # elements in the array) to keep things simple
def SHMS_events(): 
    NoCut_Events_SHMS = [CTime_eKCoinTime_ROC1, CTime_ePiCoinTime_ROC1, CTime_epCoinTime_ROC1, H_cal_etotnorm, P_gtr_beta, P_gtr_xp, P_gtr_yp, P_gtr_p, P_gtr_dp, P_cal_etotnorm, P_aero_npeSum, P_hgcer_npeSum, P_hgcer_xAtCer, P_hgcer_yAtCer, P_cal_fly_earray, P_cal_pr_eplane, P_gtr_x, P_gtr_y]
    SHMS_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*NoCut_Events_SHMS)]

    # Create (currently empty) arrays of our SHMS events for Cut1 and Cut2, we also have a temp array of our uncut data
    Cut_Events_SHMS_tmp = NoCut_Events_SHMS
    Pion_Cut_wHGC_Events = []
    Pion_Cut_noHGC_Events = []
    Positron_Cut_wHGC_Events = []
    Positron_Cut_noHGC_Events = []
    Pion_Aero_Cut_noAero_Events = []
    Pion_Cal_Cut_noCal_Events = []
    Kaon_Cut_wHGC_Events = []
    Kaon_Cut_noHGC_Events = []
    P_Cut_wHGC_Events = []
    P_Cut_noHGC_Events = []
    P_Cut_no_Cal_HGC_Events = []
    P_Cut_no_Cal_HGC_Aero_Events = []

    #Apply our cuts to the data and save our new arrays
    for arr in   Cut_Events_SHMS_tmp:
        Pion_Cut_wHGC_Events.append(c.add_cut(arr, "p_picut_eff"))
        Pion_Cut_noHGC_Events.append(c.add_cut(arr, "p_picut_eff_no_hgcer"))
        Positron_Cut_wHGC_Events.append(c.add_cut(arr, "p_ecut_eff"))
        Positron_Cut_noHGC_Events.append(c.add_cut(arr, "p_ecut_eff_no_hgcer"))
        Pion_Aero_Cut_noAero_Events.append(c.add_cut(arr, "p_picut_eff_no_aero"))
        Pion_Cal_Cut_noCal_Events.append(c.add_cut(arr, "p_picut_eff_no_cal"))
        Kaon_Cut_wHGC_Events.append(c.add_cut(arr, "p_kcut_eff"))
        Kaon_Cut_noHGC_Events.append(c.add_cut(arr, "p_kcut_eff_no_hgcer"))
        P_Cut_wHGC_Events.append(c.add_cut(arr, "p_pcut_eff"))
        P_Cut_noHGC_Events.append(c.add_cut(arr, "p_pcut_eff_no_hgcer"))
        P_Cut_no_Cal_HGC_Events.append(c.add_cut(arr, "p_cut_eff_no_cal_hgcer"))
        P_Cut_no_Cal_HGC_Aero_Events.append(c.add_cut(arr, "p_cut_eff_no_hgcer_aero_cal"))

        
        # Again, strictly force this to be an array and NOT a list
    Pion_Cut_wHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Pion_Cut_wHGC_Events)]
    Pion_Cut_noHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Pion_Cut_noHGC_Events)]
    Positron_Cut_wHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Positron_Cut_wHGC_Events)]
    Positron_Cut_noHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Positron_Cut_noHGC_Events)]
    Pion_Aero_Cut_noAero_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Pion_Aero_Cut_noAero_Events)]
    Pion_Cal_Cut_noCal_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Pion_Cal_Cut_noCal_Events)]
    Kaon_Cut_wHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Kaon_Cut_wHGC_Events)]
    Kaon_Cut_noHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*Kaon_Cut_noHGC_Events)]
    P_Cut_wHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*P_Cut_wHGC_Events)]
    P_Cut_noHGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*P_Cut_noHGC_Events)]
    P_Cut_no_Cal_HGC_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*P_Cut_no_Cal_HGC_Events)]
    P_Cut_no_Cal_HGC_Aero_Events_Info = [(CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) for (CTeK, CTePi, CTeP, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Paernpe, Phgnpe, Pxat, Pyat, Pfly, Ppr, Pxtr, Pytr) in zip(*P_Cut_no_Cal_HGC_Aero_Events)]
    SHMS_Events = {
        "SHMS_Events": SHMS_Events_Info,
        "SHMS_Pions": Pion_Cut_wHGC_Events_Info,
        "SHMS_Positrons_Without_HGC_Cuts": Positron_Cut_noHGC_Events_Info,
        "SHMS_Positrons": Positron_Cut_wHGC_Events_Info,
        "SHMS_Pions_Without_HGC_Cuts": Pion_Cut_noHGC_Events_Info,
        "SHMS_Pions_Aero_Without_Aero_Cuts": Pion_Aero_Cut_noAero_Events_Info,
        "SHMS_Pions_Cal_Without_Cal_Cuts": Pion_Cal_Cut_noCal_Events_Info,
        "SHMS_Kaons": Kaon_Cut_wHGC_Events_Info,
        "SHMS_Kaons_Without_HGC_Cuts": Kaon_Cut_noHGC_Events_Info,
        "SHMS_Protons": P_Cut_wHGC_Events_Info,
        "SHMS_Protons_Without_HGC_Cuts": P_Cut_noHGC_Events_Info,
        "SHMS_cut_no_Cal_HGC": P_Cut_no_Cal_HGC_Events_Info,
        "SHMS_cut_no_Cal_HGC_Aero": P_Cut_no_Cal_HGC_Aero_Events_Info,
    }

    return SHMS_Events

def main():
    # Run our functions and get a dict from each
    SHMS_Events_Data = SHMS_events()
    
    # This is just the list of branches we use from the initial root file for each dict
    # They're the "headers" of the data frame we create - i.e. they're going to be the branches in our new root file
    # Note - I don't like re-defining this here as it's very prone to errors if you included (or removed something) earlier but didn't modify it here
    SHMS_Data_Header = ["CTime_eKCoinTime_ROC1","CTime_ePiCoinTime_ROC1","CTime_epCoinTime_ROC1","H_cal_etotnorm", "P_gtr_beta","P_gtr_xp","P_gtr_yp","P_gtr_p","P_gtr_dp","P_cal_etotnorm", "P_aero_npeSum", "P_hgcer_npeSum", "P_hgcer_xAtCer", "P_hgcer_yAtCer", "P_cal_fly_earray", "P_cal_pr_eplane", "P_gtr_x", "P_gtr_y"]
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
            pd.DataFrame(data.get(data_keys[i]), columns = DFHeader, index = None).to_root("%s/efficiency_%s_%s.root" % (OUTPATH, runNum, MaxEvent), key ="%s" % data_keys[i])
        elif (i != 0): # For any but the first case, append it to our file
            pd.DataFrame(data.get(data_keys[i]), columns = DFHeader, index = None).to_root("%s/efficiency_%s_%s.root" % (OUTPATH, runNum, MaxEvent), key ="%s" % data_keys[i], mode ='a') 
                    
if __name__ == '__main__':
    main()

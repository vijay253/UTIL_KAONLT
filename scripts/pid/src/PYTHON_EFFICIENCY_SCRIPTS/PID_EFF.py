#! /usr/bin/python

# DEC 16, 2020 Vijay Kumar, University of Regina

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
if len(sys.argv)-1!=2:
    print("!!!!! ERROR !!!!!\n Expected 3 arguments\n Usage is with - ROOTfilePrefix RunNumber MaxEvents \n!!!!! ERROR !!!!!")
    sys.exit(1)
# Input params - run number and max number of events
#ROOTPrefix = sys.argv[1]
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
 
############################### RF Timing is the only thing left in here ######################################                                                                                        
TimingCutFile = "%s/UTIL_KAONLT/DB/PARAM/Timing_Parameters.csv" % REPLAYPATH
TimingCutf = open(TimingCutFile)
linenum = 0 # Count line number we're on                                                                                                                                                             
TempPar = -1 # To check later                                                                                                                                                                        
for line in TimingCutf: # Read all lines in the cut file                                                                                                                                             
    linenum += 1 # Add one to line number at start of loop                                                                                                                                           
    if(linenum > 1): # Skip first line                                                                                                                                                               
        line = line.partition('#')[0] # Treat anything after a # as a comment and ignore it                                                                                                          
        line = line.rstrip()
        array = line.split(",") # Convert line into an array, anything after a comma is a new entry                                                                                                  
        if(int(runNum) in range (int(array[0]), int(array[1])+1)): # Check if run number for file is within any of the ranges specified in the cut file                                              
            TempPar += 2 # If run number is in range, set to non -1 value                                                                                                                            
            BunchSpacing = float(array[2]) # Bunch spacing in ns                                                                                                                                     
            RF_Offset = float(array[9]) # Offset for RF timing cut                                                                                                                                   
TimingCutf.close() # After scanning all lines in file, close file                                                                                                                                    
if(TempPar == -1): # If value is still -1, run number provided din't match any ranges specified so exit                                                                                              
    print("!!!!! ERROR !!!!!\n Run number specified does not fall within a set of runs for which cuts are defined in %s\n!!!!! ERROR !!!!!" % TimingCutFile)
    sys.exit(3)
elif(TempPar > 1):
    print("!!! WARNING!!! Run number was found within the range of two (or more) line entries of %s !!! WARNING !!!" % TimingCutFile)
    print("The last matching entry will be treated as the input, you should ensure this is what you want")
###############################################################################################################                                                                                      
# Read stuff from the main event tree, here we're just going to get some quantities for the acceptance for the HMS/SHMS
e_tree = up.open(rootName)["T"]
# SHMS info
CTime_eKCoinTime_ROC1           = e_tree.array("CTime.eKCoinTime_ROC1")
CTime_ePiCoinTime_ROC1          = e_tree.array("CTime.ePiCoinTime_ROC1")
CTime_epCoinTime_ROC1           = e_tree.array("CTime.epCoinTime_ROC1")
#P_hgcer_goodAdcTdcDiffTime      = e_tree.array("P.hgcer.goodAdcTdcDiffTime")
P_hod_goodscinhit               = e_tree.array("P.hod.goodscinhit")
P_hod_betanotrack               = e_tree.array("P.hod.betanotrack")
P_hod_goodstarttime             = e_tree.array("P.hod.goodstarttime")
P_dc_InsideDipoleExit           = e_tree.array("P.dc.InsideDipoleExit")
P_dc_1x1_nhit                   = e_tree.array("P.dc.1x1.nhit")
P_dc_1x2_nhit                   = e_tree.array("P.dc.1x2.nhit")
P_dc_2x1_nhit                   = e_tree.array("P.dc.2x1.nhit")
P_dc_2x2_nhit                   = e_tree.array("P.dc.2x2.nhit")
P_dc_1u1_nhit                   = e_tree.array("P.dc.1u1.nhit")
P_dc_1u2_nhit                   = e_tree.array("P.dc.1u2.nhit")
P_dc_2u1_nhit                   = e_tree.array("P.dc.2u1.nhit")
P_dc_2u2_nhit                   = e_tree.array("P.dc.2u2.nhit")
P_dc_1v1_nhit                   = e_tree.array("P.dc.1v1.nhit")
P_dc_1v2_nhit                   = e_tree.array("P.dc.1v2.nhit")
P_dc_2v1_nhit                   = e_tree.array("P.dc.2v1.nhit")
P_dc_2v2_nhit                   = e_tree.array("P.dc.2v2.nhit")
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

# Create array of mod(BunchSpacing)(RFTime - StartTime + Offset) for all events. Offset is chosen to centre the pion peak in the distribution (need to test 2ns runs)                                
RF_time = np.array([ ((RFTime-StartTime + RF_Offset)%(BunchSpacing)) for (RFTime, StartTime) in zip(P_RF_tdcTime, P_hod_fpHitsTime)]) # In python x % y is taking the modulo y of x               
r = klt.pyRoot()
# Specify the file which contains the cuts we want to use
fout = '%s/UTIL_KAONLT/DB/CUTS/run_type/Cuts_file.cuts' % REPLAYPATH
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
# Acceptance, beta and calorimeter cuts applied  
cutDict = make_cutDict("Acceptance_beta_cuts", cutDict)
c = klt.pyPlot(cutDict)

# Define a function to return a dictionary of the events we want
# Arrays we generate in our dict should all be of the same length (in terms of # elements in the array) to keep things simple
def SHMS_events(): 
    NoCut_Events_SHMS = [CTime_eKCoinTime_ROC1, CTime_ePiCoinTime_ROC1, CTime_epCoinTime_ROC1, P_hod_goodscinhit, P_hod_betanotrack, P_hod_goodstarttime, P_dc_InsideDipoleExit, P_dc_1x1_nhit,P_dc_1x2_nhit, P_dc_2x1_nhit, P_dc_2x2_nhit, P_dc_1u1_nhit, P_dc_1u2_nhit, P_dc_2u1_nhit, P_dc_2u2_nhit, P_dc_1v1_nhit,P_dc_1v2_nhit, P_dc_2v1_nhit, P_dc_2v2_nhit, P_dc_ntrack, RF_time, H_cal_etotnorm, P_gtr_beta, P_gtr_xp, P_gtr_yp, P_gtr_p, P_gtr_dp, P_cal_etotnorm, P_cal_etottracknorm, P_aero_npeSum, P_hgcer_npeSum, P_hgcer_xAtCer, P_hgcer_yAtCer,  P_aero_xAtCer, P_aero_yAtCer, P_cal_fly_earray, P_cal_pr_eplane, P_gtr_x, P_gtr_y, emiss, pmiss]
    SHMS_Events_Info = [(CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, P_dc_1x1, P_dc_1x2,P_dc_2x1,P_dc_2x2,P_dc_1u1,P_dc_1u2,P_dc_2u1,P_dc_2u2,P_dc_1v1,P_dc_1v2,P_dc_2v1,P_dc_2v2,Pntrack, RFtime, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) for (CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, P_dc_1x1, P_dc_1x2,P_dc_2x1,P_dc_2x2,P_dc_1u1,P_dc_1u2,P_dc_2u1,P_dc_2u2,P_dc_1v1,P_dc_1v2,P_dc_2v1,P_dc_2v2,Pntrack, RFtime, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) in zip(*NoCut_Events_SHMS)]

    # Create (currently empty) arrays of our SHMS events for Cut1 and Cut2, we also have a temp array of our uncut data
    Cut_Events_SHMS_tmp = NoCut_Events_SHMS
    SHMS_Events_wCuts = []

    #Apply our cuts to the data and save our new arrays
    for arr in   Cut_Events_SHMS_tmp:
        SHMS_Events_wCuts.append(c.add_cut(arr, "Acceptance_beta_cuts"))
              
    # Again, strictly force this to be an array and NOT a list
    P_Events_wCuts = [(CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, P_dc_1x1, P_dc_1x2,P_dc_2x1,P_dc_2x2,P_dc_1u1,P_dc_1u2,P_dc_2u1,P_dc_2u2,P_dc_1v1,P_dc_1v2,P_dc_2v1,P_dc_2v2,Pntrack, RFtime, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot, Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) for (CTeK, CTePi, CTeP, Phodgood, Phodbet, Phodgoodstime, Pdcexitdipole, P_dc_1x1, P_dc_1x2,P_dc_2x1,P_dc_2x2,P_dc_1u1,P_dc_1u2,P_dc_2u1,P_dc_2u2,P_dc_1v1,P_dc_1v2,P_dc_2v1,P_dc_2v2,Pntrack, RFtime, HCal, PBeta, Pxp, Pyp, PP, PDel, Ptot,Ptottrack, Paernpe, Phgnpe, Pxat, Pyat, Paeroxat, Paeroyat, Pfly, Ppr, Pxtr, Pytr, Pemiss, Ppmiss) in zip(*SHMS_Events_wCuts)]
    SHMS_Events = {
        "SHMS_Events": SHMS_Events_Info,
        "SHMS_Events_wCuts": P_Events_wCuts,
    }

    return SHMS_Events

def main():
    # Run our functions and get a dict from each
    SHMS_Events_Data = SHMS_events()
    
    # This is just the list of branches we use from the initial root file for each dict
    # They're the "headers" of the data frame we create - i.e. they're going to be the branches in our new root file
    # Note - I don't like re-defining this here as it's very prone to errors if you included (or removed something) earlier but didn't modify it here
    SHMS_Data_Header = ["CTime_eKCoinTime_ROC1","CTime_ePiCoinTime_ROC1","CTime_epCoinTime_ROC1", "P_hod_goodscinhit", "P_hod_betanotrack", "P_hod_goodstarttime", "P_dc_InsideDipoleExit", "P_dc_1x1_nhit","P_dc_1x2_nhit", "P_dc_2x1_nhit", "P_dc_2x2_nhit", "P_dc_1u1_nhit", "P_dc_1u2_nhit", "P_dc_2u1_nhit", "P_dc_2u2_nhit", "P_dc_1v1_nhit","P_dc_1v2_nhit", "P_dc_2v1_nhit", "P_dc_2v2_nhit", "P_dc_ntrack","RF_time", "H_cal_etotnorm", "P_gtr_beta","P_gtr_xp","P_gtr_yp","P_gtr_p","P_gtr_dp","P_cal_etotnorm", "P_cal_etottracknorm", "P_aero_npeSum", "P_hgcer_npeSum", "P_hgcer_xAtCer", "P_hgcer_yAtCer", "P_aero_xAtCer", "P_aero_yAtCer","P_cal_fly_earray", "P_cal_pr_eplane", "P_gtr_x", "P_gtr_y", "emiss", "pmiss"]
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

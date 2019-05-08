#!/bin/bash

### Template for a batch running script from Richard, modify with your username and with the script you want to run on the final eval line
### If you encounter errors, try commenting/uncommenting L18

echo "Starting Kaon Yield Estimation"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=-1
#MAXEVENTS=50000
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi

#Initialize enviroment
#export OSRELEASE="Linux_CentOS7.2.1511-x86_64-gcc5.2.0"
source /site/12gev_phys/softenv.sh 2.1

#Initialize hcana
cd "/u/group/c-kaonlt/hcana/"
source "/u/group/c-kaonlt/hcana/setup.sh"
cd "/u/group/c-kaonlt/USERS/${USER}/hallc_replay_kaonlt"
source "/u/group/c-kaonlt/USERS/${USER}/hallc_replay_kaonlt/setup.sh"

echo -e "\n\nStarting Replay Script\n\n"
eval "/u/group/c-kaonlt/USERS/${USER}/hallc_replay_kaonlt/hcana -l -q \"SCRIPTS/COIN/PRODUCTION/HMSHodo_Calib_Coin_Pt1.C($RUNNUMBER,$MAXEVENTS)\""
ROOTFILE="/u/group/c-kaonlt/USER/${USER}/hallc_replay_kaonlt/ROOTfilesHodoCalibPt1/hms_Hodo_Calib_Coin_Pt1_"$RUNNUMBER"_-1.root"
OPT="coin"
cd "/group/c-kaonlt/USERS/sjdkay/hallc_replay_kaonlt/CALIBRATION/hms_hodo_calib/"
root -lq "timeWalkHistos.C (\"$ROOTFILE\", $RUNNUMBER, \"$OPT\")"
root -lq "timeWalkCalib.C"

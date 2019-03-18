#!/bin/bash

echo "Starting p(e,e'p) Yield Estimation"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=$2
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi
if [[ $2 -eq "" ]]; then
    echo "Only Run Number entered...I'll assume -1 events!" 
    MAXEVENTS=-1 
fi
cd ../
#echo -e "\n\nStarting Scaler Replay Script\n\n"
#hcana -q "SCRIPTS/COIN/SCALERS/replay_coin_scalers.C($RUNNUMBER,100000)"
#cd CALIBRATION/bcm_current_map/
#root -b<<EOF
#.x run.C("../../ROOTfiles/coin_replay_scalers_${RUNNUMBER}_100000.root")
#EOF
#mv bcmcurrent_$RUNNUMBER.param ../../PARAM/HMS/BCM/CALIB/bcmcurrent_$RUNNUMBER.param
#cd ../../
echo -e "\n\nStarting Replay Script\n\n"
./hcana -q "UTIL_KAONLT/scripts_Replay/replay_production_coin.C($RUNNUMBER,$MAXEVENTS)"
cd UTIL_KAONLT/scripts_KaonYield/
echo -e "\n\nYield Calculation\n\n"
root -l "run_peepYield.C($RUNNUMBER,$MAXEVENTS,0,0)"
if [[ -e "OUTPUT/scalers_Run$RUNNUMBER.txt" ]]; then
    while true; do
	read -p "Would you like to update the run list as well? (Please answer yes or no) " yn
	case $yn in
            [Yy]* ) break;;
            [Nn]* ) exit;;
            * ) echo "Please answer yes or no.";;
	esac
    done

    read -p "What type of production was this run? (e.g. Prod, Heep, ect.)" runType
    read -p "What was the target? (Dummy, LH2 ..?)" target
    
    fillrunList="./fill_runList $RUNNUMBER $runType $target"
    
    eval ${fillrunList}
    
fi

#!/bin/bash

echo "Starting Kaon Yield Estimation"
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
#./hcana -q "SCRIPTS/COIN/SCALERS/replay_coin_scalers.C($RUNNUMBER,150000)"
#cd CALIBRATION/bcm_current_map/
#root -b<<EOF
#.L ScalerCalib.C+
#.x run.C("../../ROOTfiles/coin_replay_scalers_${RUNNUMBER}_150000.root")
#EOF
#mv bcmcurrent_$RUNNUMBER.param ../../PARAM/HMS/BCM/CALIB/bcmcurrent_$RUNNUMBER.param
#cd ../../
echo -e "\n\nStarting Replay Script\n\n"
./hcana -q "UTIL_KAONLT/scripts_Replay/replay_production_coin.C($RUNNUMBER,$MAXEVENTS)"
cd UTIL_KAONLT/scripts_KaonYield/
echo -e "\n\nYield Calculation\n\n"
root -l "run_KaonYield.C($RUNNUMBER,$MAXEVENTS,0,0)"

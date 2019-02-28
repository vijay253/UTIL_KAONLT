#! /bin/csh

echo "Starting Tracking Test replay Script"
echo "I take as arguments the Run Number and max number of events!"
set RUNNUMBER=$1
set MAXEVENTS=$2
if ($1 == "") then
    echo "I need a Run Number!";
    exit 2
endif
if ($2 == "" ) then
    echo "Only Run Number entered...I'll assume -1 events!";
    set MAXEVENTS=-1
endif
cd ../
echo -e "\n\nStarting Scaler Replay Script\n\n"
hcana -q "SCRIPTS/COIN/SCALERS/replay_coin_scalers.C($RUNNUMBER,-1)"
cd CALIBRATION/bcm_current_map/
root -b<<EOF
.L ScalerCalib.C+
.x run.C("../../ROOTfiles/coin_replay_scalers_${RUNNUMBER}_-1.root")
EOF
mv bcmcurrent_$RUNNUMBER.param ../../PARAM/HMS/BCM/CALIB/bcmcurrent_$RUNNUMBER.param
cd ../../
echo -e "\n\nStarting Replay Script\n\n"
hcana -q "UTIL_KAONLT/scripts_TrackingTest/replay_production_coin_TT.C($RUNNUMBER,$MAXEVENTS)"
cd UTIL_KAONLT/scripts_TrackingTest/
echo -e "\n\nTracking Calculation\n\n"
root -l "run_TrackingTest.C($RUNNUMBER,$MAXEVENTS,5,1)"
exit 0

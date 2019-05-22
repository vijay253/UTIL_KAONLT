#!/bin/bash

echo "Starting Kaon Yield Estimation"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=-1
# MAXEVENTS=50000
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi

#Initialize enviroment
export OSRELEASE="Linux_CentOS7.2.1511-x86_64-gcc5.2.0"
#source /site/12gev_phys/softenv.sh 2.0

#Initialize hcana
cd "/w/hallc-scifs17exp/kaon/sjdkay/hcana/"
source "/w/hallc-scifs17exp/kaon/sjdkay/hcana/setup.sh"
cd "/w/hallc-scifs17exp/kaon/sjdkay/hallc_replay_lt"
source "/w/hallc-scifs17exp/kaon/sjdkay/hallc_replay_lt/setup.sh"

# cd ../
#   Load params for BCM
#   const char* CurrentFileNamePattern = "PARAM/HMS/BCM/CALIB/bcmcurrent_%d.param";
#   gHcParms->Load(Form(CurrentFileNamePattern, RunNumber));
# When we comment out the below bit ONLY when the bit above is commented out in replay_production_coin.C
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
#eval "/w/hallc-scifs17exp/kaon/sjdkay/hallc_replay_lt/hcana -l -q \"UTIL_KAONLT/scripts_Replay/replay_production_coin.C($RUNNUMBER,$MAXEVENTS)\""
eval "/w/hallc-scifs17exp/kaon/sjdkay/hallc_replay_lt/hcana -l -q \"SCRIPTS/COIN/PRODUCTION/replay_production_coin_hElec_pProt.C($RUNNUMBER,$MAXEVENTS)\""                                                            
# cd UTIL_KAONLT/scripts_KaonYield/
# echo -e "\n\nYield Calculation\n\n"
# root -l "run_KaonYield.C($RUNNUMBER,$MAXEVENTS,5,1)"
# cd ../

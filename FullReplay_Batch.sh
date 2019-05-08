#!/bin/bash

echo "Starting Replay script"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=-1
# MAXEVENTS=50000
if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi

#Initialize enviroment
source /site/12gev_phys/softenv.sh 2.1

#Initialize hcana
cd "/u/group/c-kaonlt/hcana"
source "/u/group/c-kaonlt/hcana/setup.sh"
cd "/u/group/c-kaonlt/USERS/sjdkay/hallc_replay_kaonlt"
source "/u/group/c-kaonlt/USERS/sjdkay/hallc_replay_kaonlt/setup.sh"

echo -e "\n\nStarting Replay Script\n\n"
eval "/u/group/c-kaonlt/USERS/sjdkay/hallc_replay_kaonlt/hcana -l -q \"SCRIPTS/COIN/PRODUCTION/FullReplay.C ($RUNNUMBER,$MAXEVENTS)\""                                                            

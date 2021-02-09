#!/bin/bash

echo "Starting PID Script"

# Set path depending upon hostname. Change or add more as needed  
if [[ "${HOSTNAME}" = *"farm"* ]]; then  
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"                         
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
    if [[ "${HOSTNAME}" != *"ifarm"* ]]; then
	source /site/12gev_phys/softenv.sh 2.3
	
    fi
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh"
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh"
fi

cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/PYTHON_EFFICIENCY_SCRIPTS/OUTPUT/
root -b -q  "${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/ROOT_EFFICIENCY_SCRIPTS/SHMS_pid.C(\"PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilo.root\", \"PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilo_OUT\")"

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
#To run the SHMS_pid.C script

#cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/ROOT_EFFICIENCY_SCRIPTS/
#root -b -q "SHMS_pid.C(\"PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon.root\", \"PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon_OUT\")"

#Run EFFICIENCY.C script 

cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/ROOT_EFFICIENCY_SCRIPTS/
root -b -q  "SCRIPT_PION_PID.C(\"PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon.root\", \"PION_PID_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon_OUT\")"
root -b -q  "SCRIPT_KAON_PID.C(\"PID_E_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon.root\", \"KAON_PID_8p18_Q2_3p0_W_3p14_P_shms_6p053_low_epsilon_OUT\")"
#root -b -q "PID_SCRIPT_PASS2.C(\"pid_8046_-1.root\", \"PID_8046_OUT\")"
#root -b -q "SCRIPT_PION_PID.C(\"pid_8046_-1.root\", \"PION_PID_8046_OUT\")"
#root -b -q "SCRIPT_KAON_PID.C(\"pid_8046_-1.root\", \"KAON_PID_8046_OUT\")"

#To run the chain script

#cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/ROOT_EFFICIENCY_SCRIPTS/
#root -b -q chain_files.C

#!/bin/bash

echo "Starting Particle ID Script"
echo "I take as arguments the Run Number and max number of events!"
RUNNUMBER=$1
MAXEVENTS=$2
# MAXEVENTS=50000

if [[ $1 -eq "" ]]; then
    echo "I need a Run Number!"
    exit 2
fi

if [[ $2 -eq "" ]]; then
    echo "Only Run Number entered...I'll assume -1 events!" 
    MAXEVENTS=-1 
fi

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
elif [[ "${HOSTNAME}" = *"qcd"* ]]; then
    REPLAYPATH="/group/c-kaonlt/USERS/${USER}/hallc_replay_lt"
    source /site/12gev_phys/softenv.sh 2.3
    cd "/group/c-kaonlt/hcana/"
    source "/group/c-kaonlt/hcana/setup.sh" 
    cd "$REPLAYPATH"
    source "$REPLAYPATH/setup.sh" 
elif [[ "${HOSTNAME}" = *"cdaq"* ]]; then
    REPLAYPATH="/home/cdaq/hallc-online/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"phys.uregina.ca"* ]]; then
    REPLAYPATH="/home/${USER}/work/JLab/hallc_replay_lt"
elif [[ "${HOSTNAME}" = *"trottar"* ]]; then
    REPLAYPATH="/home/trottar/Analysis/hallc_replay_lt"
fi

source /apps/root/6.18.04/setroot_CUE.bash

cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/PYTHON_EFFICIENCY_SCRIPTS/
python3  PID_EFF.py ${RUNNUMBER} ${MAXEVENTS}

#python3 test.py ${RUNNUMBER} ${MAXEVENTS}

#cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/PYTHON_EFFICIENCY_SCRIPTS/OUTPUT/
#root -b -q  "${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/PYTHON_EFFICIENCY_SCRIPTS/OUTPUT/PION_MM.C(\"pid_eff_${RUNNUMBER}_${MAXEVENTS}.root\", \"PION1_MM_${RUNNUMBER}_${MAXEVENTS}\")"
 
#cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/OUTPUTS/
#convert MMK_${RUNNUMBER}.png noID_shms_hgcer_${RUNNUMBER}.png PID_shms_hgcer_${RUNNUMBER}.png pid_plots_${RUNNUMBER}.pdf
#rm -rf *.png

#cd ${REPLAYPATH}/UTIL_KAONLT/scripts/pid/src/
#python3 csv2root.py

#!/bin/bash

##Select angle (left, center)##
angle=$1

if [[ ${angle} == "" ]]; then
    echo "Please select an angle setting..."
    exit 2
fi
if [[ ${angle} = "left" ]]; then
    ## Chain runs script ##
    script_Q2p115W2p95="../scripts_Summaries/Q2p115W2p95left.C"
    run_script_Q2p115W2p95="root -l \"${script_Q2p115W2p95}\""
    echo "Running ${script_Q2p115W2p95}"
    eval ${run_script_Q2p115W2p95}
    mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_leftQ2p115W2p95.pdf
    echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ2p115W2p95.pdf"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "CHAIN AT LEFT ANGLE COMPLETE"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
fi
if [[ ${angle} = "center" ]]; then
    ## Chain runs script ##
    script_Q2p115W2p95="../scripts_Summaries/Q2p115W2p95center.C"
    run_script_Q2p115W2p95="root -l \"${script_Q2p115W2p95}\""
    echo "Running ${script_Q2p115W2p95}"
    eval ${run_script_Q2p115W2p95}
    mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q2.115_W2.95_x0.21_lowe/Kinematics_centerQ2p115W2p95.pdf
    echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ2p115W2p95.pdf"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "CHAIN AT CENTER ANGLE COMPLETE"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
fi

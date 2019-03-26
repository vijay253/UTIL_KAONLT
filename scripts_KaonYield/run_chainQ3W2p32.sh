#!/bin/bash

##Select angle (left, center)##
angle=$1

if [[ ${angle} == "" ]]; then
    echo "Please select an angle setting..."
    exit 2
fi
if [[ ${angle} = "left" ]]; then
    ## Chain runs script ##
    script_Q3W2p32="../scripts_Summaries/Q3W2p32left.C"
    run_script_Q3W2p32="root -l \"${script_Q3W2p32}\""
    echo "Running ${script_Q3W2p32}"
    eval ${run_script_Q3W2p32}
    mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q3.0_W2.32_x0.40_lowe/Kinematics_leftQ3W2p32.pdf
    echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_leftQ3W2p32.pdf"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "CHAIN AT LEFT ANGLE COMPLETE"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
fi
if [[ ${angle} = "center" ]]; then
    ## Chain runs script ##
    script_Q3W2p32="../scripts_Summaries/Q3W2p32center.C"
    run_script_Q3W2p32="root -l \"${script_Q3W2p32}\""
    echo "Running ${script_Q3W2p32}"
    eval ${run_script_Q3W2p32}
    mv ../OUTPUT/Kinematics_1uA_allPlots.pdf ../OUTPUT/Q3.0_W2.32_x0.40_lowe/Kinematics_centerQ3W2p32.pdf
    echo "Kinematics_1uA_allPlots.pdf changed to Kinematics_centerQ3W2p32.pdf"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "CHAIN AT CENTER ANGLE COMPLETE"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
fi

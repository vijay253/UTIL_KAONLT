#! /bin/bash

#Input run numbers                                                                                                 
inputFile="inputRuns"                                                                              
                                                                                                                   
while IFS='' read -r line || [[ -n "$line" ]];                                                                     
do                                                                                                                 
    echo "Run number read from file: $line"                                                                        

#Which run                                                                                                         
runNum=$line                                                                                                       
                                                                                                                   
#Number of events                                                                                                  
numEvts=-1 

#Script to run
script="run_LumiYield.C" 

#Parameters for script 
runScript="root -l -b -q \"${script}(${runNum},${numEvts})\""

#Excecute                                                                                                          
{ 

echo "Running ${script} for run  ${runNum}"
eval ${runScript}

echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"          
echo "END OF RUN ${runNum}"                                                                                        
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" 

}

done < "$inputFile" 

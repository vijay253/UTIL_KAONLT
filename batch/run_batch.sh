#! /bin/bash                                                                                                                                                                                                       

##### A batch submission script by Richard, insert the required script you want to batch run on line 51                                                                                                           
##### Modify required resources as needed!                                                                                                                                   

echo "Running as ${USER}"

##Output history file##                                                                                                                                                                                           
historyfile=hist.$( date "+%Y-%m-%d_%H-%M-%S" ).log

##Output batch script##                                                                                                                                                                                           
batch="${USER}_Job.txt"

##Input run numbers##                                                                                                                                                                                             
inputFile="/u/group/c-kaonlt/USERS/${USER}/hallc_replay_kaonlt/UTIL_KAONLT/batch/inputRuns"

## Tape stub                                                                                                                                                                                                      
MSSstub='/mss/hallc/spring17/raw/coin_all_%05d.dat'

auger="augerID.tmp"

while true; do
    read -p "Do you wish to begin a new batch submission? (Please answer yes or no) " yn
    case $yn in
        [Yy]* )
            i=-1
            (
            ##Reads in input file##                                                                                                                                                                                
            while IFS='' read -r line || [[ -n "$line" ]]; do
                echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
                echo "Run number read from file: $line"
                echo ""
                ##Run number#                                                                                                                                                                                     
                runNum=$line
                tape_file=`printf $MSSstub $runNum`
                tmp=tmp
                ##Finds number of lines of input file##                                                                                                                                                           
                numlines=$(eval "wc -l < ${inputFile}")
                echo "Job $(( $i + 2 ))/$(( $numlines +1 ))"
                echo "Running ${batch} for ${runNum}"
                cp /dev/null ${batch}
                ##Creation of batch script for submission##                                                                                                                                                       
                echo "PROJECT: c-kaonlt" >> ${batch}
                echo "TRACK: analysis" >> ${batch}
                #echo "TRACK: debug" >> ${batch} ### Use for testing                                                                                                                                              
                echo "JOBNAME: KaonLT_${runNum}" >> ${batch}
                #echo "DISK_SPACE: 20 GB" >>${batch}                                                                                                                                                              
                echo "MEMORY: 2500 MB" >> ${batch}
                echo "OS: centos7" >> ${batch}
                echo "CPU: 1" >> ${batch} ### hcana single core, setting CPU higher will lower priority!                                                                                                                           #echo "TIME: 1" >> ${batch} 
                echo "COMMAND:/u/group/c-kaonlt/USERS/${USER}/hallc_replay_kaonlt/UTIL_KAONLT/SCRIPT.sh${runNum}" >> ${batch} ### Insert your script at end!                                            
                echo "MAIL: ${USER}@jlab.org" >> ${batch}
                echo "Submitting batch"
                eval "jsub ${batch} 2>/dev/null"
                echo " "
                i=$(( $i + 1 ))
                string=$(cat ${inputFile} |tr "\n" " ")
                ##Converts input file to an array##                                                                                                                                                               
                rnum=($string)
                #echo "array is ${rnum[@]}"                                                                                                                                                                       
                eval "jobstat -u ${USER} 2>/dev/null" > ${tmp}
                ##Loop to find ID number of each run number##   
		for j in "${rnum[@]}"
		do
		    if [ $(grep -c $j ${tmp}) -gt 0 ]; then
			ID=$(echo $(grep $j ${tmp}) | head -c 8)
			#ID=$(echo $(grep $j ${tmp}) | head -c 8) 
			augerID[$i]=$ID
			echo "${augerID[@]}" >> $auger
		    fi	
		done   
		#echo "${augerID[@]}"
		echo "${rnum[$i]} has an AugerID of ${augerID[$i]}" 
		if [ $i == $numlines ]; then
		    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		    echo " "
		    echo "###############################################################################################################"
		    echo "############################################ END OF JOB SUBMISSIONS ###########################################"
		    echo "###############################################################################################################"
		    echo " "	
		    k=-1
		    ##Prints all ID numbers##
      		    for j in "${augerID[@]}"
		    do
			k=$(( $k + 1 ))
			echo "${rnum[$k]} has an AugerID of $j"
		    done
		    ##While there are jobs still remaining it will print all jobs status every 30 seconds##
		    while [  $(eval "wc -l < ${tmp}") != 1 ]; do
			cp /dev/null ${tmp}
			sleep 30
			echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
			eval "jobstat -u ${USER} 2>/dev/null"
			eval "jobstat -u ${USER} 2>/dev/null" > ${tmp}
			echo " "  
			if [ $(( $(eval "wc -l < ${tmp}") - 1 )) = 1 ]; then
			    echo "There is $(( $(eval "wc -l < ${tmp}") - 1 )) job remaining"
			else
			    echo "There are $(( $(eval "wc -l < ${tmp}") - 1 )) jobs remaining"
			fi
		    done
		    l=-1
		    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
		    sleep 30
		    ##For each run it checks that the .err file has been made and copies it to another file along with job info##
		    for j in "${augerID[@]}"
		    do
			l=$(( $l + 1 ))
			output=KaonLT_${rnum[$l]}.out
			check="/home/${USER}/.farm_out/KaonLT_${rnum[$l]}.$j.err"	   
			if [ -e "$check" ]; then
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "Errors..." >> ${output}
			    echo " " >> ${output}
			    cat /home/${USER}/.farm_out/KaonLT_${rnum[$l]}.$j.err >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "Job info..." >> ${output}
			    echo " " >> ${output}
			    eval "jobinfo $j 2>/dev/null" >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}		
			    memused[$l]=$(cut -d "=" -f2 <<< $(grep -oh -m 1 "\w*resources_used.vmem=\w*" batch_OUTPUT/${output}))
			    memlist[$l]=$(cut -d "=" -f2 <<< $(grep -oh -m 1 "\w*Resource_List.vmem=\w*" batch_OUTPUT/${output}))
			    echo "_"
			    echo "|ID-$j (run ${rnum[$l]}) has printed batch job information to file"
			    echo "|Amount of allocated memory used: ${memused[$l]}/${memlist[$l]}"
			else
			    echo "Batch job information not found [ID-$j]"		      
			fi
		    done	
		fi
		cp /dev/null ${tmp}
		

	    done < "$inputFile"

	    ##All output text in terminal is copied to a file##
	    ) 2>&1 | tee ${historyfile}

	    echo ""
	    echo "###############################################################################################################"
	    echo "############################################# ALL JOBS COMPLETED ##############################################"
	    echo "###############################################################################################################"

	    break;;
        [Nn]* ) 
	    while IFS='' read -r line || [[ -n "$line" ]]; do
		echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		echo ""
		augerID=$line
	    done < "$auger"
	    i=-1
	    echo "Retrieving batch job submission list..."
	    echo
	    ##Reads in input file##
	    while IFS='' read -r line || [[ -n "$line" ]]; do
		##Run number#
		runNum=$line
		tmp=tmp 
		##Finds number of lines of input file##
		numlines=$(eval "wc -l < ${inputFile}")
		i=$(( $i + 1 ))
		string=$(cat ${inputFile} |tr "\n" " ")
		##Converts input file to an array##
		rnum=($string)
		eval "jobstat -u ${USER} 2>/dev/null" > ${tmp} 
		##Loop to find ID number of each run number## 
		#echo "${augerID[@]}"
		echo "${rnum[$i]} has an AugerID of ${augerID[$i]}" 
		if [ $i == $numlines ]; then
		    k=-1
		    ##Prints all ID numbers##
      		    for j in "${augerID[@]}"
		    do
			k=$(( $k + 1 ))
			echo "${rnum[$k]} has an AugerID of $j"
		    done
		    ##While there are jobs still remaining it will print all jobs status every 30 seconds##
		    while [  $(eval "wc -l < ${tmp}") != 1 ]; do
			cp /dev/null ${tmp}
			sleep 30
			echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
			eval "jobstat -u ${USER} 2>/dev/null"
			eval "jobstat -u ${USER} 2>/dev/null" > ${tmp}
			echo " "  
			if [ $(( $(eval "wc -l < ${tmp}") - 1 )) = 1 ]; then
			    echo "There is $(( $(eval "wc -l < ${tmp}") - 1 )) job remaining"
			else
			    echo "There are $(( $(eval "wc -l < ${tmp}") - 1 )) jobs remaining"
			fi
		    done
		    l=-1
		    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  
		    sleep 30
		    ##For each run it checks that the .err file has been made and copies it to another file along with job info##
		    for j in "${augerID[@]}"
		    do
			l=$(( $l + 1 ))
			output=KaonLT_${rnum[$l]}.out
			check="/home/${USER}/.farm_out/KaonLT_${rnum[$l]}.$j.err"	   
			#echo "error file is $check"
			if [ -e "$check" ]; then
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "Errors..." >> ${output}
			    echo " " >> ${output}
			    cat /home/${USER}/.farm_out/KaonLT_${rnum[$l]}.$j.err >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "Job info..." >> ${output}
			    echo " " >> ${output}
			    eval "jobinfo $j 2>/dev/null" >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}
			    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" >> ${output}			    
			    memused[$l]=$(cut -d "=" -f2 <<< $(grep -oh -m 1 "\w*resources_used.vmem=\w*" batch_OUTPUT/${output}))
			    memlist[$l]=$(cut -d "=" -f2 <<< $(grep -oh -m 1 "\w*Resource_List.vmem=\w*" batch_OUTPUT/${output}))
			    echo "_"
			    echo "|ID-$j (run ${rnum[$l]}) has printed batch job information to file"
			    echo "|Amount of allocated memory used: ${memused[$l]}/${memlist[$l]}"
			    else
			    echo "Batch job information not found [ID-$j]"      
			    fi
		    done
		    fi
		cp /dev/null ${tmp}
		

		    done < "$inputFile"
	        exit;;
        * ) echo "Please answer yes or no.";;
    esac
done
i=-1
(


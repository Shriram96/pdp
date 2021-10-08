#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --clusters=ub-hpc
#SBATCH --qos=general-compute
#SBATCH --exclusive
#SBATCH --mem=23000
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="changeme"
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --time=02:00:00

# your app invocation should follow
# ...

# helpFunction()
# {
#    echo ""
#    echo "Usage: $0 -t threads -n rows -m columns"
#    echo -e "\t-t Number of threads"
#    echo -e "\t-n Number of rows"
#    echo -e "\t-m Number of columns"
#    exit 1 # Exit script after printing help
# }

# while getopts "t:n:m:" opt
# do
#    case "$opt" in
#       t ) threads="$OPTARG" ;;
#       n ) rows="$OPTARG" ;;
#       m ) columns="$OPTARG" ;;
#       ? ) helpFunction ;; # Print helpFunction in case parameter is non-existent
#    esac
# done

# # Print helpFunction in case parameters are empty
# if [ -z "$threads" ] || [ -z "$rows" ] || [ -z "$columns" ]
# then
#    echo "Some or all of the parameters are empty";
#    helpFunction
# fi

# # Begin script in case all parameters are correct
# echo "Threads = $threads"
# echo "Rows = $rows"
# echo "Columns = $columns"

module load gcc/10.2.0
cd "/user/shriramr/pdp/Project-1/A0"
# make clean all
threads=( 1 2 4 8 16 32 64 128 )
volumes=( 100 500 1000 5000 10000 )
for i in "${volumes[@]}"
do
	for j in "${threads[@]}"
   do
      echo "Threads = $j"
      echo "Rows = $i"
      echo "Columns = $i"
      echo "\n############################################################\n"
      for (( k = 0; k < 20; k++ ))
      do
         OMP_NUM_THREADS="$j" ./a0 "$i" "$i"
      done
      echo "\n############################################################\n"
   done
done
# OMP_NUM_THREADS="$threads" ./a0 "$rows" "$columns"
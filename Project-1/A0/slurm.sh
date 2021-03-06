#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --clusters=faculty
#SBATCH --partition=planex
#SBATCH --qos=planex
#SBATCH --account=cse570f21
#SBATCH --exclusive
#SBATCH --mem=64000
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="shriramr-a0"
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=20
#SBATCH --time=02:00:00

# module load gcc
# make clean all
threads=( 1 2 4 6 8 10 )
volumes=( 1000 2000 4000 6000 8000 10000 )
tests=3
for i in "${volumes[@]}"
do
	for j in "${threads[@]}"
   do
      echo "Threads = $j"
      echo "Rows = 100000"
      echo "Columns = $i"
      echo "START:############################################################"
      for (( k = 0; k < "$tests"; k++ ))
      do
         OMP_NUM_THREADS="$j" ./a0 100000 "$i"
         OMP_NUM_THREADS="$j" ./a0 "$i" 100000
      done
      echo "END:############################################################"
   done
done

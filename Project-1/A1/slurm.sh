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
#SBATCH --job-name="shriramr"
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=10
#SBATCH --time=00:15:00

module load gcc
module load intel-mpi
# make clean all

keys=( 2 3 4 5 6 7 8 9 10 )
base=10
tests=3
for i in "${keys[@]}"
do
    echo "Nodes = 10"
    echo "Keys = $i"
    echo "START:############################################################"
    for (( k = 0; k < "$tests"; k++ ))
    do
        srun --mpi=pmi2 ./a1 $[$base**$i]
    done
    echo "END:############################################################"
done
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
srun --mpi=pmi2 ./a1 100000
#!/bin/bash

####### PLANEX SPECIFIC - DO NOT EDIT THIS SECTION
#SBATCH --clusters=ub-hpc
#SBATCH --qos=general-compute
#SBATCH --exclusive
#SBATCH --mem=64000
#SBATCH --output=%j.stdout
#SBATCH --error=%j.stderr

####### CUSTOMIZE THIS SECTION FOR YOUR JOB
#SBATCH --job-name="shriramr-a3"
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=32
#SBATCH --gres=gpu:1
#SBATCH --time=02:00:00

module load gcc
module load cuda/11.3.1
# make clean all
nvcc --version
nvidia-smi
volumes=( 1 2 3 4 5 6 7 8 9 10 )
tests=1
base=10
h=19.97

for i in "${volumes[@]}"
do
   echo "Threads = Get it from device query (CUDA)"
   echo "Volume = $i"
   echo "START:############################################################"
   for (( k = 0; k < "$tests"; k++ ))
   do
      ./a3 $[$base**$i] "$h"
   done
   echo "END:############################################################"

   echo "PROFILE START:############################################################"
   sudo /usr/local/cuda-11/bin/nvprof ./a3 $[$base**$i] "$h"
   echo "PROFILE END:############################################################"
done

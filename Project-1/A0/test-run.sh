#!/bin/bash
sbatch slurm.sh -t 1 -n 1000 -m 1000
sbatch slurm.sh -t 2 -n 1000 -m 1000
sbatch slurm.sh -t 4 -n 1000 -m 1000
sbatch slurm.sh -t 8 -n 1000 -m 1000
sbatch slurm.sh -t 16 -n 1000 -m 1000
# sbatch slurm.sh -t 32 -n 1000 -m 1000

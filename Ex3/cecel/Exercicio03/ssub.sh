#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=24
#SBATCH --ntasks=12
#SBATCH --cpus-per-task=1
#SBATCH -p sequana_cpu_dev
#SBATCH -J V_12
#SBATCH --time=00:01:00
#SBATCH --output=/scratch/csc642023/marcel.silva/src/OutTempo_12MPI.out
#SBATCH --exclusive

cd $SLURM_SUBMIT_DIR
ulimit -s unlimited
export OMP_NUM_THREADS=1
srun -n $SLURM_NTASKS --mpi=openmpi -c $SLURM_CPUS_PER_TASK /scratch/csc642023/marcel.silva/src/Tempo.exe 

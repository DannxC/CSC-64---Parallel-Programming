#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=24
#SBATCH -p sequana_cpu_dev
#SBATCH -J C_24
#SBATCH --time=00:04:00
#SBATCH --output=/scratch/csc642023/daniel.cavassani/CrivoParaOpenMP/Out_Primos_24.txt
#SBATCH --exclusive

cd $SLURM_SUBMIT_DIR
ulimit -s unlimited
export OMP_NUM_THREADS=24
srun -n $SLURM_NTASKS /scratch/csc642023/daniel.cavassani/CrivoParaOpenMP/Primos.exe
exit

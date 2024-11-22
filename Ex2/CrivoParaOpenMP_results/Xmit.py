import os
import sys

nNodes=1
nTasksPerNode=1
nTasks=1
if len(sys.argv) < 2:
    raise ValueError("faltou argumento numero de threads")
nThreads=sys.argv[1]
queue="sequana_cpu_dev"
execTime="00:04:00"

pwd=os.getcwd()
execName=pwd+"/Primos.exe"
if len(nThreads)==1:
   job="C_0"+nThreads
   outFile=pwd+"/Out_Primos_0"+nThreads+".txt"
else:
   job="C_"+nThreads
   outFile=pwd+"/Out_Primos_"+nThreads+".txt"

fOut=open("ssub.sh","w")
strOut="#!/bin/bash\n"
strOut+="#SBATCH --nodes="+str(nNodes)+"\n"
strOut+="#SBATCH --ntasks-per-node="+str(nTasksPerNode)+"\n"
strOut+="#SBATCH --ntasks="+str(nTasks)+"\n"
strOut+="#SBATCH --cpus-per-task="+nThreads+"\n"
strOut+="#SBATCH -p "+queue+"\n"
strOut+="#SBATCH -J "+job+"\n"
strOut+="#SBATCH --time="+execTime+"\n"
strOut+="#SBATCH --output="+outFile+"\n"
strOut+="#SBATCH --exclusive\n"
strOut+="\n"
strOut+="cd $SLURM_SUBMIT_DIR\n"
strOut+="ulimit -s unlimited\n"
strOut+="export OMP_NUM_THREADS="+nThreads+"\n"
strOut+="srun -n $SLURM_NTASKS "+execName+"\n"
strOut+="exit\n"
fOut.write(strOut)
fOut.close()

os.system("chmod +x "+pwd+"/ssub.sh")
os.system("sbatch ssub.sh")

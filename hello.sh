#!/bin/sh

#PBS -q u-lecture
#PBS -N hello
#PBS -l select=1:mpiprocs=4
#PBS -Wgroup_list=gt29
#PBS -l walltime=00:05:00
#PBS -e err
#PBS -o hello.lst
#PBS -M user8715@gmail.com

#cd $PBS_O_WORKDIR
source /etc/profile.d/modules.sh || echo "no modules"

export I_MPI_PIN_DOMAIN=socket
export I_MPI_PERHOST=8
mpirun ./impimap.sh ./a.out

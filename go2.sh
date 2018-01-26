#!/bin/sh

#PBS -q u-lecture
#PBS -N test
#PBS -l select=1:mpiprocs=2
#PBS -Wgroup_list=gt29
#PBS -l walltime=00:05:00
#PBS -e err
#PBS -o test.lst

cd $PBS_O_WORKDIR
. /etc/profile.d/modules.sh

export I_MPI_PIN_DOMAIN=socket
export I_MPI_PERHOST=2
mpirun ./impimap.sh ./a.out

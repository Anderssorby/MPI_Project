#!/bin/sh

#PBS -q u-lecture
#PBS -N 1-36
#PBS -l select=1:mpiprocs=36
#PBS -Wgroup_list=gt29
#PBS -l walltime=00:10:00
#PBS -e err
#PBS -o S2-out1-36.lst


cd $PBS_O_WORKDIR
. /etc/profile.d/modules.sh

export I_MPI_PIN_DOMAIN=socket
export I_MPI_PERHOST=36
mpirun ./impimap.sh ./a.out

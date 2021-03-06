#!/bin/sh

#PBS -q u-lecture
#PBS -N test
#PBS -l select=1:mpiprocs=4
#PBS -Wgroup_list=gt29
#PBS -l walltime=00:05:00
#PBS -e err
#PBS -o test.lst
#PBS -M user8715@gmail.com

cd $PBS_O_WORKDIR
. /etc/profile.d/modules.sh

export I_MPI_PIN_DOMAIN=socket
export I_MPI_PERHOST=4
mpirun ./impimap.sh ./a.out

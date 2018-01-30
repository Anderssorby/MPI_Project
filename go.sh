#!/bin/sh

#PBS -q u-lecture
#PBS -N 1d
#PBS -l select=8:mpiprocs=32
#PBS -Wgroup_list=gt29
#PBS -l walltime=00:10:00
#PBS -e err
#PBS -o go-out.lst

#export PROJECT=`pwd`

cd $PBS_O_WORKDIR
. /etc/profile.d/modules.sh

#cd $PROJECT
export I_MPI_PIN_DOMAIN=socket
export I_MPI_PERHOST=32
mpirun ./impimap.sh ./a.out

#include <stdio.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char **argv){
    int i;
    int PeTot, MyRank;
    MPI_Comm SolverComm;
    double TimeStart, TimeEnd;
    double vec[8];
    double sum0;
    char FileName[80];
    FILE *fp;
    double normsum;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &PeTot);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

    TimeStart = MPI_Wtime();

    sprintf(FileName, "a1.%d", MyRank);

    fp = fopen(FileName, "r");
    if(fp == NULL) MPI_Abort(MPI_COMM_WORLD, -1);
    for(i=0;i<8;i++){
        fscanf(fp, "%lf", &vec[i]);
    }

    for(i=0;i<8;i++){
        sum0 += vec[i]*vec[i];
        /**printf("%5d%5d%10.0f\n", MyRank, i+1, vec[i]);*/
    }
    printf("Rank(%d) = %10.0f\n", MyRank, sum0);


    MPI_Allreduce(&sum0, &normsum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    if (MyRank == 0) {
        printf("||x||^2 = %10.0f\n", normsum);
        normsum = sqrt(normsum);

        printf("||x|| = %10.0f\n", normsum);
    }

    TimeEnd = MPI_Wtime();
    printf("Time (%5d) %16.6E\n", MyRank, TimeEnd - TimeStart);

    MPI_Finalize();

    return 0;
}

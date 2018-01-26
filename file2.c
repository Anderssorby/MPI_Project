#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

int main(int argc, char **argv){
    int i;
    int PeTot, MyRank;
    MPI_Comm SolverComm;
    double *vec, *vec2, *vecg;
    int *Count, *CountIndex;
    double TimeStart, TimeEnd;
    int num;
    double sum0, sum;
    char filename[80];
    FILE *fp;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &PeTot);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);


    TimeStart = MPI_Wtime();

    sprintf(filename, "a2.%d", MyRank);
    fp = fopen(filename, "r");
    assert(fp != NULL);

    fscanf(fp, "%d", &num);
    vec = malloc(num * sizeof(double));

    for(i =0;i<num;i++){
        fscanf(fp, "%lf", &vec[i]);
    }

    for(i=0;i<num;i++){
        sum0 = vec[i]*vec[i];
        printf(" %5d%5d%5d%10.0f\n", MyRank, i+1, num, vec[i]);
    }

    printf("\n");

    Count = calloc(PeTot, sizeof(int));
    CountIndex = calloc(PeTot+1, sizeof(int));
    MPI_Allgather(&num, 1, MPI_INT, Count, 1, MPI_INT, MPI_COMM_WORLD);

    MPI_Allreduce(&sum0, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    if (MyRank == 0) {
        sum = sqrt(sum);
        printf("||x|| = %10.3f\n", sum);
    }

    TimeEnd = MPI_Wtime();
    printf("Time (%5d) %16.6E\n", MyRank, TimeEnd - TimeStart);

    MPI_Finalize();

    return 0;
}

#include <stdio.h>
#include <math.h>
#include "mpi.h"

double f(const double x) {
    return 4.0/(1+x*x);
}

int main(int argc, char **argv){
    double a = 0, b = 1;
    int parts = 2000;
    int i;
    int PeTot, MyRank;
    MPI_Comm SolverComm;
    double TimeStart, TimeEnd;
    double sum0;
    double sum;

    MPI_Init(&argc, &argv);
    TimeStart = MPI_Wtime();
    MPI_Comm_size(MPI_COMM_WORLD, &PeTot);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

    if (MyRank==0) {
        printf("parts=%d, PeTot=%d\n", parts, PeTot);
    }

    /*int_0^1(4/(1+x^2)dx)*/

    int parts0 = (parts)/PeTot;
    double partition = (b-a)/(PeTot);
    double dx = partition/parts0;
    double start = a + MyRank*partition;
    /**printf("dx = %5f\n", dx);*/

    double xi = start+dx;
    /** Compute sum over interior points **/
    for(i=0;i < parts0;i++) {
        /**printf("f(xi=%f)=%f\n", xi, f(xi));*/
        sum0 += f(xi);
        xi += dx;
    }
    /**printf("Rank(%d) = %10.0f\n", MyRank, sum0);*/


    MPI_Allreduce(&sum0, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    if (MyRank == 0) {
        // Add endpoints
        sum = dx/2*(f(a) + 2*sum - f(b));

        printf("Trapeziodal = %10.15f\n", sum);
    }

    TimeEnd = MPI_Wtime();
    printf("Time (%5d) %16.6E\n", MyRank, TimeEnd - TimeStart);

    MPI_Finalize();

    return 0;
}

#include <stdio.h>
#include <math.h>
#include "mpi.h"

double f(const double x) {
    return 4.0/(1+x*x);
}

int main(int argc, char **argv){
    double a = 0, b = 1;
    int parts = 20;
    int i;
    int PeTot, MyRank;
    MPI_Comm SolverComm;
    double sum0;
    double sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &PeTot);
    /**printf("PeTot=%d\n", PeTot);*/
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

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
        sum0 += f(xi + dx/2);
        xi += dx;
    }
    /**printf("Rank(%d) = %10.0f\n", MyRank, sum0);*/


    MPI_Allreduce(&sum0, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    if (MyRank == 0) {
        // Add endpoints
        sum = (b-a)/6*(f(a) + 4*sum - 3*f(b));

        printf("Simpsons = %10.15f\n", sum);
    }

    MPI_Finalize();

    return 0;
}

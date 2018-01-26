#include <mpi.h>
#include <cstdio>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int myid, numprocs;

	MPI::Init(argc, argv);
	MPI::Intracomm comm(MPI::COMM_WORLD);

	numprocs = comm.Get_size();
	myid = comm.Get_rank();

	cout << "Hello World " << myid << endl;
	MPI::Finalize();
}

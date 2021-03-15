//妤把抉忍把忘技技忘 4.2
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include "mpi.h"
using namespace std;
int ProcRank, ProcNum;

void DataInitialization(double x[], int N) {
	for (int i = 0; i < N; i++) {
		x[i] = i + 1.0;
	}
}

int main(int argc, char* argv[]) {
	double x[11] = {0}, TotalSum, ProcSum = 0.0;
	int N = 10;
	MPI_Status Status;
	//cout << 1;
	//init
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	//cout << 1;
	//prepare
	if (ProcRank == 0) DataInitialization(x, N);

	//broadcast data to all processors
	MPI_Bcast(x, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	//cout << 1;
	//calculation of partial sum at each processor
	//at each processor sum from xi_1 to x_i2
	int k = N / ProcNum;//number of elements for each processor
	int i1 = k * ProcRank;
	int i2 = k * (ProcRank + 1);
	if (ProcRank == ProcNum - 1) i2 = N;//the last processor
	for (int i = i1; i < i2; i++)
		ProcSum = ProcSum + x[i];
	//cout << 1;
	//collect all partial sums to processor with rank 0 
	if (ProcRank == 0) {
		TotalSum = ProcSum;
		for (int i = 1; i < ProcNum; i++) {
			MPI_Recv(&ProcSum, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &Status);
			TotalSum = TotalSum + ProcSum;
		}
	}
	//other processors send partial sum to processor 0
	else MPI_Send(&ProcSum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	//cout << 1;
	//results
	if (ProcRank == 0) printf("\nTotal Sum= %10.lf", TotalSum);
	//cout << 1;
	MPI_Finalize();
	return 0;
}
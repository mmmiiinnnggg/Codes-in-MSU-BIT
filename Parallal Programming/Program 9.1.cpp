// 妤把抉忍把忘技技忘 9.1 - Gauss algorithm for solving systems of linear equations
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

int ProcNum; // The number of the available processes
int ProcRank; // The rank of the current process
int* pParallelPivotPos; // The number of rows selected as the pivot ones
int* pProcPivotIter; // The number of iterations, at which the processor
// rows were used as the pivot ones

// Function for the execution of the parallel Gauss algorithm
void ParallelResultCalculation(double* pProcRows, double* pProcVector,
	double* pProcResult, int Size, int RowNum) {
	ParallelGaussianElimination(pProcRows, pProcVector, Size, RowNum);
	ParallelBackSubstitution(pProcRows, pProcVector, pProcResult,
		Size, RowNum);
}

void ParallelGaussianElimination(double* pProcRows, double* pProcVector,
	int Size, int RowNum) {
	double MaxValue; // The value of the pivot element of th快 process
	int PivotPos; // The Position of the pivot row in the stripe
	// of th快 process
	// Structure for the pivot row selection
	struct { double MaxValue; int ProcRank; } ProcPivot, Pivot;
	// pPivotRow is used for storing the pivot row and the corresponding
	// element of the vector b
	pPivotRow = new double[Size + 1];
	// The iterations of the Gaussian elimination stage
	for (int i = 0; i < Size; i++) {
		// Calculating the local pivot row
		double MaxValue = 0;
		for (int j = 0; j < RowNum; j++) {
			if ((pProcPivotIter[j] == -1) &&
				(MaxValue < fabs(pProcRows[j * Size + i]))) {
				MaxValue = fabs(pProcRows[j * Size + i]);
				PivotPos = j;
			}
		}
		ProcPivot.MaxValue = MaxValue;
		ProcPivot.ProcRank = ProcRank;
		// Finding the pivot process
		// (process with the maximum value of MaxValue)
		MPI_Allreduce(&ProcPivot, &Pivot, 1, MPI_DOUBLE_INT, MPI_MAXLOC,
			MPI_COMM_WORLD);
		// Broadcasting the pivot row
		if (ProcRank == Pivot.ProcRank) {
			pProcPivotIter[PivotPos] = i; //iteration number
			pParallelPivotPos[i] = pProcInd[ProcRank] + PivotPos;
		}
		MPI_Bcast(&pParallelPivotPos[i], 1, MPI_INT, Pivot.ProcRank,
			MPI_COMM_WORLD);
		if (ProcRank == Pivot.ProcRank) {
			// Fill the pivot row
			for (int j = 0; j < Size; j++) {
				pPivotRow[j] = pProcRows[PivotPos * Size + j];
			}
			pPivotRow[Size] = pProcVector[PivotPos];
		}
		MPI_Bcast(pPivotRow, Size + 1, MPI_DOUBLE, Pivot.ProcRank,
			MPI_COMM_WORLD);
		ParallelEliminateColumns(pProcRows, pProcVector, pPivotRow, Size,
			RowNum, i);
	}
}

void ParallelBackSubstitution(double* pProcRows, double* pProcVector,
	double* pProcResult, int Size, int RowNum) {
	int IterProcRank; // The rank of the process with the current pivot row
	int IterPivotPos; // The position of the pivot row of the process
	double IterResult; // The calculated value of the current unknown
	double val;
	// Iterations of the back substitution stage
	for (int i = Size - 1; i >= 0; i--) {
		// Calculating the rank of the process, which holds the pivot row
		FindBackPivotRow(pParallelPivotPos[i], Size, IterProcRank,
			IterPivotPos);
		// Calculating the unknown
		if (ProcRank == IterProcRank) {
			IterResult =
				pProcVector[IterPivotPos] / pProcRows[IterPivotPos * Size + i];
			pProcResult[IterPivotPos] = IterResult;
		}
		// Broadcasting the value of the current unknown
		MPI_Bcast(&IterResult, 1, MPI_DOUBLE, IterProcRank, MPI_COMM_WORLD);
		// Updating the values of the vector b
		for (int j = 0; j < RowNum; j++)
			if (pProcPivotIter[j] < i) {
				val = pProcRows[j * Size + i] * IterResult;
				pProcVector[j] = pProcVector[j] - val;
			}
	}
}


void main(int argc, char* argv[]) {
	double* pMatrix; // The matrix of the linear system
	double* pVector; // The right parts of the linear system
	double* pResult; // The result vector
	double* pProcRows; // The Rows of matrix A on the process
	double* pProcVector; // The Elements of vector b on the process
	double* pProcResult; // The Elements of vector x on the process
	int Size; // The Sizes of the initial matrix and vector
	int RowNum; // The Number of the matrix rows on the current
	// process
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	if (ProcRank == 0)
		printf("Parallel Gauss algorithm for solving linear systems\n");
	// Memory allocation and definition of object elements
	ProcessInitialization(pMatrix, pVector, pResult,
		pProcRows, pProcVector, pProcResult, Size, RowNum);
	// The execution of the parallel Gauss algorithm
	DataDistribution(pMatrix, pProcRows, pVector, pProcVector, Size, RowNum);
	ParallelResultCalculation(pProcRows, pProcVector, pProcResult, Size,
		RowNum);
	ResultCollection(pProcResult, pResult);
	// Computational process termination
	ProcessTermination(pMatrix, pVector, pResult, pProcRows, pProcVector,
		pProcResult);
	MPI_Finalize();
}
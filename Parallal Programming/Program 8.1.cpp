// 妤把抉忍把忘技技忘 8.1 - Fox's matrix multiplication algorithm - block data representation
// Program execution conditions: all matrices are square, 
// the size of blocks and their number horizontally and vertically is the same, 
// processors form a square lattice

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

int ProcNum = 0; // Number of available processes
int ProcRank = 0; // Rank of current process
int GridSize; // Size of virtual processor grid
int GridCoords[2]; // Coordinates of current processor in grid
MPI_Comm GridComm; // Grid communicator
MPI_Comm ColComm; // Column communicator
MPI_Comm RowComm; // Row communicator

// Creation of two-dimensional grid communicator
// and communicators for each row and each column of the grid
void CreateGridCommunicators() {
	int DimSize[2]; // Number of processes in each dimension of the grid
	int Periodic[2]; // =1, if the grid dimension should be periodic
	int Subdims[2]; // =1, if the grid dimension should be fixed
	DimSize[0] = GridSize;
	DimSize[1] = GridSize;
	Periodic[0] = 0;
	Periodic[1] = 0;
	// Creation of the Cartesian communicator
	MPI_Cart_create(MPI_COMM_WORLD, 2, DimSize, Periodic, 1, &GridComm);
	// Determination of the cartesian coordinates for every process
	MPI_Cart_coords(GridComm, ProcRank, 2, GridCoords);
	// Creating communicators for rows
	Subdims[0] = 0; // Dimensionality fixing
	Subdims[1] = 1; // The presence of the given dimension in the subgrid
	MPI_Cart_sub(GridComm, Subdims, &RowComm);
	// Creating communicators for columns
	Subdims[0] = 1;
	Subdims[1] = 0;
	MPI_Cart_sub(GridComm, Subdims, &ColComm);
}

// Function for memory allocation and data initialization
void ProcessInitialization(double*& pAMatrix, double*& pBMatrix,
	double*& pCMatrix, double*& pAblock, double*& pBblock, double*& pCblock,
	double*& pTemporaryAblock, int& Size, int& BlockSize) {
	if (ProcRank == 0) {
		do {
			printf("\nEnter size of the initial objects: ");
			scanf("%d", &Size);
			if (Size % GridSize != 0) {
				printf("Size of matricies must be divisible by the grid size! \n");
			}
		} while (Size % GridSize != 0);
	}
	MPI_Bcast(&Size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	BlockSize = Size / GridSize;
	pAblock = new double[BlockSize * BlockSize];
	pBblock = new double[BlockSize * BlockSize];
	pCblock = new double[BlockSize * BlockSize];
	pTemporaryAblock = new double[BlockSize * BlockSize];
	for (int i = 0; i < BlockSize * BlockSize; i++) {
		pCblock[i] = 0;
	}
	if (ProcRank == 0) {
		pAMatrix = new double[Size * Size];
		pBMatrix = new double[Size * Size];
		pCMatrix = new double[Size * Size];
		RandomDataInitialization(pAMatrix, pBMatrix, Size);
	}
}




// Broadcasting matrix A blocks to process grid rows
void ABlockCommunication(int iter, double* pAblock, double* pMatrixAblock,
	int BlockSize) {
	// Defining the leading process of the process grid row
	int Pivot = (GridCoords[0] + iter) % GridSize;
	// Copying the transmitted block in a separate memory buffer
	if (GridCoords[1] == Pivot) {
		for (int i = 0; i < BlockSize * BlockSize; i++)
			pAblock[i] = pMatrixAblock[i];
	}
	// Block broadcasting
	MPI_Bcast(pAblock, BlockSize * BlockSize, MPI_DOUBLE, Pivot, RowComm);
}

// Matrix block multiplication
void BlockMultiplication(double* pAblock, double* pBblock,
	double* pCblock, int BlockSize) {
	// calculating the product of matrix blocks
	for (int i = 0; i < BlockSize; i++) {
		for (int j = 0; j < BlockSize; j++) {
			double temp = 0;
			for (int k = 0; k < BlockSize; k++)
				temp += pAblock[i * BlockSize + k] * pBblock[k * BlockSize + j]
				pCblock[i * BlockSize + j] += temp;
		}
	}
}

// Cyclic shift of matrix B blocks in the process grid columns
void BblockCommunication(double* pBblock, int BlockSize) {
	MPI_Status Status;
	int NextProc = GridCoords[0] + 1;
	if (GridCoords[0] == GridSize - 1) NextProc = 0;
	int PrevProc = GridCoords[0] - 1;
	if (GridCoords[0] == 0) PrevProc = GridSize - 1;
	MPI_Sendrecv_replace(pBblock, BlockSize * BlockSize, MPI_DOUBLE,
		NextProc, 0, PrevProc, 0, ColComm, &Status);
}

void ParallelResultCalculation(double* pAblock, double* pMatrixAblock,
	double* pBblock, double* pCblock, int BlockSize) {
	for (int iter = 0; iter < GridSize; iter++) {
		// Sending blocks of matrix A to the process grid rows
		ABlockCommunication(iter, pAblock, pMatrixAblock, BlockSize);
		// Block multiplication
		BlockMultiplication(pAblock, pBblock, pCblock, BlockSize);
		// Cyclic shift of blocks of matrix B in process grid columns
		BblockCommunication(pBblock, BlockSize);
	}
}

void main(int argc, char* argv[]) {
	double* pAMatrix; // The first argument of matrix multiplication
	double* pBMatrix; // The second argument of matrix multiplication
	double* pCMatrix; // The result matrix
	int Size; // Size of matricies
	int BlockSize; // Sizes of matrix blocks on current process
	double* pAblock; // Initial block of matrix A on current process
	double* pBblock; // Initial block of matrix B on current process
	double* pCblock; // Block of result matrix C on current process
	double* pMatrixAblock;
	double Start, Finish, Duration;
	setvbuf(stdout, 0, _IONBF, 0);
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	GridSize = sqrt((double)ProcNum);
	if (ProcNum != GridSize * GridSize) {
		if (ProcRank == 0) {
			printf("Number of processes must be a perfect square \n");
		}
	}
	else {
		if (ProcRank == 0)
			printf("Parallel matrix multiplication program\n");
		// Creating the cartesian grid, row and column communcators
		CreateGridCommunicators();
		// Memory allocation and initialization of matrix elements
		ProcessInitialization(pAMatrix, pBMatrix, pCMatrix, pAblock, pBblock,
			pCblock, pMatrixAblock, Size, BlockSize);
		DataDistribution(pAMatrix, pBMatrix, pMatrixAblock, pBblock, Size,
			BlockSize);
		// Execution of Fox method
		ParallelResultCalculation(pAblock, pMatrixAblock, pBblock,
			pCblock, BlockSize);
		ResultCollection(pCMatrix, pCblock, Size, BlockSize);
		TestResult(pAMatrix, pBMatrix, pCMatrix, Size);
		// Process Termination
		ProcessTermination(pAMatrix, pBMatrix, pCMatrix, pAblock, pBblock,
			pCblock, pMatrixAblock);
	}
	MPI_Finalize();
}
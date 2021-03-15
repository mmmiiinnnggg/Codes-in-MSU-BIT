#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define N 2
using namespace std;

double DoubleRnd() {
	return rand() / 32767.0;
}

////////////////SMALL MATRIX////////////////////////
class Matrix {
private:
	int nDim;
	double* Matr;
public:
	Matrix() { nDim = N; Matr = new double[nDim * nDim]; }
	Matrix(int nDim);
	Matrix(Matrix& m);
	~Matrix() { delete[] Matr; }
	void Set(int nX, int nY, double r) { Matr[MakeIndex(nX, nY)] = r; }
	double Get(int nX, int nY) { return Matr[MakeIndex(nX, nY)]; }
	int GetDim() { return nDim; }
	void Add(int nX, int nY, double r) { Matr[MakeIndex(nX, nY)] += r; }
	void Minus(int nX, int nY, double r){ Matr[MakeIndex(nX, nY)] -= r; }
//private:
	void InitMemory() { Matr = new double[nDim * nDim]; }
	int MakeIndex(int nX, int nY) { return (nX - 1) * nDim + (nY - 1); }
	void Set0(int nX, int nY) { Set(nX, nY, 0); }
	void Set1(int nX, int nY) { Set(nX, nY, 1); }
public:
	void InitNul();
	void InitOne();
	void InitRnd();
	friend ostream& operator <<(ostream& os, Matrix& m);
	void Print();
	Matrix& operator*(const Matrix& m1);
	Matrix& operator+(Matrix& m1);
	Matrix& operator-(Matrix& m1);
	void operator+=(Matrix& m1);
	void operator-=(Matrix& m1);
	void operator=(Matrix& m1);
	bool Mult(Matrix& m1, Matrix& m2);
};

////////////IMPLEMENTATION/////////////////

Matrix::Matrix(int nDim) {
	this->nDim = nDim;
	InitMemory();
}

Matrix::Matrix(Matrix& m) {
	nDim = m.nDim;
	InitMemory();
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			Set(i, j, m.Get(i, j));
}

void Matrix::InitNul() {
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			Set0(i, j);
}

void Matrix::InitOne() {
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++) {
			Set0(i, j);
			if (i != j) continue;
			Set1(i, j);
		}
}

void Matrix::InitRnd() {
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			Set(i, j, DoubleRnd());
}

Matrix& Matrix::operator*(const Matrix& m1) {
	int nDim = GetDim();
	Matrix M;
	M.InitNul();
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			for (int k = 1; k <= nDim; k++) {
				//cout <<i<<" "<<j<<" "<<k<< endl;
				//cout << nDim << endl;
				double tmp = Matr[MakeIndex(i, k)] * m1.Matr[MakeIndex(k, j)];
				M.Add(i, j, tmp);
			}
	return M;
}

Matrix& Matrix::operator+(Matrix& m1) {
	Matrix m2(GetDim());
	m2.InitNul();
	if (nDim != m1.GetDim()) exit(0);
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			m2.Add(i,j,m1.Matr[MakeIndex(i,j)]);
	return m2;
}

Matrix& Matrix::operator-(Matrix& m1) {
	Matrix m2(GetDim());
	m2.InitNul();
	if (nDim != m1.GetDim()) exit(0);
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			m2.Minus(i, j, m1.Matr[MakeIndex(i, j)]);
	return m2;
}

void Matrix::operator+=(Matrix& m1) {
	if (nDim != m1.GetDim()) exit(0);
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			Add(i, j, m1.Get(i, j));
}

void Matrix::operator-=(Matrix& m1) {
	if (nDim != m1.GetDim()) exit(0);
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++) {
			double tmp = (-1) * m1.Get(i, j);
			Add(i, j, tmp);
		}
}

void Matrix::operator=(Matrix& m1) {
	int nDim = GetDim();
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			//Matr[MakeIndex(i, j)] = m1.Matr[MakeIndex(i, j)];
			Set(i, j, m1.Get(i, j));
}

ostream& operator<<(ostream& os, Matrix& m) {
	//os << m.nDim << endl;
	for (int i = 1; i <= m.nDim; i++) {
		for (int j = 1; j <= m.nDim; j++) {
			os.width(10);
			os.precision(3);
			os << m.Get(i, j) << " ";
		}
		os << endl;
	}
	return os;
}

void Matrix::Print() {
	cout << "Size: "<<nDim << endl;
	for (int i = 1; i <= nDim; i++) {
		for (int j = 1; j <= nDim; j++) {
			cout.width(10);
			cout.precision(3);
			cout << Get(i, j) << " ";
		}
		cout << endl;
	}
}

bool Matrix::Mult(Matrix& m1, Matrix& m2) {
	int nDim = GetDim();
	if (nDim != m1.GetDim() || nDim != m2.GetDim()) return false;
	InitNul();
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			for (int k = 1; k <= nDim; k++)
				Add(i, j, m1.Get(i, k) * m2.Get(k, j));
	return true;
}

////////////BIGMATRIX///////////
class HardMatrix : public Matrix{
private:
	int BigDim;
	Matrix* BigMatr;
public:
	HardMatrix(int nDim, int Dim) :Matrix(nDim) { BigDim = Dim;  BigMatr = new Matrix[nDim * nDim]; }
	HardMatrix(int Dim) { BigDim = Dim; HardInitMemory();}
	HardMatrix(HardMatrix& m);
	~HardMatrix() { delete[] BigMatr; }
	void HardSet(int nX, int nY, Matrix& r) { BigMatr[MakeIndex(nX, nY)] = r; }
	Matrix& HardGet(int nX, int nY) { return BigMatr[MakeIndex(nX, nY)]; }
	void HardAdd(int nX, int nY, Matrix& r) { BigMatr[MakeIndex(nX, nY)] += r; }
	int HardGetDim() { return BigDim; }
//private:
	void HardInitMemory() { BigMatr = new Matrix [BigDim * BigDim]; }
	int MakeIndex(int nX, int nY) { return (nX - 1) * BigDim + (nY - 1); }
	int Change(int i, int j) { return (i - 1) * BigDim + (j - 1); } /*the same with MakeIndex but to differ*/
	//void HardSet0(int nX, int nY) { HardSet(nX, nY, 0); }
public:
	void HardInitNul();
	void HardInitRnd();
	void HardPrint();
	bool HardMult(HardMatrix& m1, HardMatrix& m2);
	bool HardMultKN(HardMatrix& m1, HardMatrix& m2);
	bool HardMultSC(HardMatrix& m1, HardMatrix& m2);
};

/////////////IMPLEMENTATION//////////////

HardMatrix::HardMatrix(HardMatrix& m) {
	BigDim = m.BigDim;
	HardInitMemory();
	for (int i = 1; i <= BigDim; i++)
		for (int j = 1; j <= BigDim; j++)
			HardSet(i, j, m.HardGet(i, j));
}

void HardMatrix::HardInitNul(){
	Matrix m1;
	m1.InitNul();
	for (int i = 1; i <= BigDim; i++)
		for (int j = 1; j <= BigDim; j++)
			HardSet(i, j, m1);
}

void HardMatrix::HardInitRnd() {
	for (int i = 1; i <= BigDim; i++)
		for (int j = 1; j <= BigDim; j++) {
			Matrix Rnd;
			Rnd.InitRnd();
			HardSet(i, j, Rnd);
		}
}

void HardMatrix::HardPrint() {
	cout << "BigSize: " << BigDim << endl;
	for (int i = 1; i <= BigDim; i++) {
		for (int j = 1; j <= BigDim; j++) {
			cout << "Number:(" << i << ',' << j << ')' << endl;
			cout.width(10);
			cout << HardGet(i, j) << " ";
			cout << endl;
		}
		//cout << endl ;
	}
}

bool HardMatrix::HardMult(HardMatrix& m1, HardMatrix& m2) {
	int nDim = HardGetDim();
	if (nDim != m1.HardGetDim() || nDim != m2.HardGetDim()) return false;
	HardInitNul();
	for (int i = 1; i <= nDim; i++)
		for (int j = 1; j <= nDim; j++)
			for (int k = 1; k <= nDim; k++) {
				Matrix Tmp;
				Tmp.Mult(m1.HardGet(i, k), m2.HardGet(k, j));
				HardAdd(i, j, Tmp);
			}
	return true;
}

bool HardMatrix::HardMultKN(HardMatrix& m1, HardMatrix& m2) {
	//Init 
	int* OrdA; int *OrdB;
	OrdA = new int[BigDim * BigDim]; OrdB = new int[BigDim * BigDim];
	for (int i = 1; i <= BigDim; i++) 
		for (int j = 1; j <= BigDim; j++) {
			OrdA[MakeIndex(i, j)] = Change(i, j);
			OrdB[MakeIndex(i, j)] = Change(i, j);
		}

	//Init move: i-1,j-1
	for (int i = 1; i <= BigDim; i++)
		for (int j = 1; j <= BigDim; j++) {
			int move_a; int move_b;
			if ((j - (i - 1)) < 1) move_a = BigDim + (j - (i - 1)); else move_a = j - (i - 1);
			if ((i - (j - 1)) < 1) move_b = BigDim + (i - (j - 1)); else move_b = i - (j - 1);
			OrdA[MakeIndex(i, j)] = Change(i, move_a); 
			OrdB[MakeIndex(i, j)] = Change(move_b, j);
		}

	//first mutiple
	for (int i = 1; i <= BigDim; i++)
		for (int j = 1; j <= BigDim; j++) {
			Matrix Tmp;
			Tmp.Mult(m1.BigMatr[OrdA[MakeIndex(i, j)]], m2.BigMatr[OrdB[MakeIndex(i, j)]]);
			HardSet(i, j, Tmp);
		}
	
	//following mutiple
	for (int cycle = 1; cycle < BigDim; cycle++) {
		//change
		//All blocks of A left move 1
		for (int i = 1; i <= BigDim; i++) {
			int tmpA = OrdA[MakeIndex(i, 1)];
			for (int j = 1; j < BigDim; j++) {
				OrdA[MakeIndex(i, j)] = OrdA[MakeIndex(i, j + 1)];
			}
			OrdA[MakeIndex(i, BigDim)] = tmpA;
		}
		//All blocks of B up move 1
		for (int j = 1; j <= BigDim; j++) {
			int tmpB = OrdB[MakeIndex(1, j)];
			for (int i = 1; i < BigDim; i++) {
				OrdB[MakeIndex(i, j)] = OrdB[MakeIndex(i+1, j)];
			}
			OrdB[MakeIndex(BigDim, j)] = tmpB;
		}
		
		//mutiple
		for (int i = 1; i <= BigDim; i++)
			for (int j = 1; j <= BigDim; j++) {
				Matrix Tmp;
				Tmp.Mult(m1.BigMatr[OrdA[MakeIndex(i, j)]], m2.BigMatr[OrdB[MakeIndex(i, j)]]);
				HardAdd(i, j, Tmp);
			}
	}

	//print
		/*
		for (int i = 1; i <= BigDim; i++) {
			for (int j = 1; j <= BigDim; j++) {
				cout << OrdA[MakeIndex(i, j)] << " ";
			}
			cout << endl;
		}
		for (int i = 1; i <= BigDim; i++) {
			for (int j = 1; j <= BigDim; j++) {
				cout << OrdB[MakeIndex(i, j)] << " ";
			}
			cout << endl;
		}

		cout << "--------" << endl;
		*/

	return true;

}

bool HardMatrix::HardMultSC(HardMatrix& m1, HardMatrix& m2) {
	if (BigDim != 2) { cout << "Error with BigDim!" << endl; return false; }
	Matrix P1, P2, P3, P4, P5, P6, P7;
	Matrix tmp; Matrix tmp2; 

	//----------------//

	tmp.InitNul(); tmp2.InitNul();
	tmp += m1.BigMatr[MakeIndex(1, 1)]; tmp += m1.BigMatr[MakeIndex(2, 2)];
	tmp2 += m2.BigMatr[MakeIndex(1, 1)]; tmp2 += m2.BigMatr[MakeIndex(2, 2)];
	P1.Mult(tmp, tmp2);
	
	tmp.InitNul(); tmp2.InitNul();
	tmp += m1.BigMatr[MakeIndex(2, 1)]; tmp += m1.BigMatr[MakeIndex(2, 2)];
	tmp2 += m2.BigMatr[MakeIndex(1, 1)];
	P2.Mult(tmp, tmp2);
	
	tmp.InitNul(); tmp2.InitNul();
	tmp += m1.BigMatr[MakeIndex(1, 1)];
	tmp2 += m2.BigMatr[MakeIndex(1, 2)]; tmp2 -= m2.BigMatr[MakeIndex(2, 2)];
	P3.Mult(tmp, tmp2);
	
	tmp.InitNul(); tmp2.InitNul();
	tmp += m1.BigMatr[MakeIndex(2, 2)];
	tmp2 += m2.BigMatr[MakeIndex(2, 1)]; tmp2 -= m2.BigMatr[MakeIndex(1, 1)];
	P4.Mult(tmp, tmp2);
	
	tmp.InitNul(); tmp2.InitNul();
	tmp += m1.BigMatr[MakeIndex(1, 1)]; tmp += m1.BigMatr[MakeIndex(1, 2)];
	tmp2 += m2.BigMatr[MakeIndex(2, 2)];
	P5.Mult(tmp, tmp2);
	
	tmp.InitNul(); tmp2.InitNul();
	tmp += m1.BigMatr[MakeIndex(2, 1)]; tmp -= m1.BigMatr[MakeIndex(1, 1)];
	tmp2 += m2.BigMatr[MakeIndex(1, 1)]; tmp2 += m2.BigMatr[MakeIndex(1, 2)];
	P6.Mult(tmp, tmp2);
	
	tmp.InitNul(); tmp2.InitNul();
	tmp += m1.BigMatr[MakeIndex(1, 2)]; tmp -= m1.BigMatr[MakeIndex(2, 2)];
	tmp2 += m2.BigMatr[MakeIndex(2, 1)]; tmp2 += m2.BigMatr[MakeIndex(2, 2)];
	P7.Mult(tmp, tmp2);

	/*
	C_11=P1 + P4 - P5 + P7
	C_12=P3 + P5
	C_21=P2 + P4
	C_22=P1 - P2 + P3 + P6
	*/

	tmp.InitNul(); tmp += P1; tmp += P4; tmp -= P5; tmp += P7; HardAdd(1, 1, tmp);
	tmp.InitNul(); tmp += P3; tmp += P5; HardAdd(1, 2, tmp);
	tmp.InitNul(); tmp += P2; tmp += P4; HardAdd(2, 1, tmp);
	tmp.InitNul(); tmp += P1; tmp -= P2; tmp += P3; tmp += P6; HardAdd(2, 2, tmp);

	return true;
}

class Process : public Matrix {
private:
	int ProDim;
	double* MatrA;
	double* MatrB;
	int A_i; int A_j;
	int B_i; int B_j;
public:
	Process(int nDim, int Dim, int A_I, int A_J, int B_I, int B_J) :Matrix(nDim)
	{
		ProDim = Dim;  MatrA = new double[ProDim * ProDim]; MatrB = new double[ProDim * ProDim];
		A_i = A_I; A_j = A_J; B_i = B_I; B_j = B_J;
	}
	//Process(int Dim) {ProDim = Dim; ProInitMemory(); }
	Process(Process& m);
	~Process() { delete[] MatrA; }
	int MakeIndex(int nX, int nY) { return (nX - 1) * ProDim + (nY - 1); }
	void ProInitMemory() { MatrA = new double[ProDim * ProDim]; MatrB = new double[ProDim * ProDim]; }
	void ProInitNul(int AI, int AJ, int BI, int BJ);
	void ProPrint();

};

Process::Process(Process& m) {
	ProDim = m.ProDim;
	ProInitMemory();
	for (int i = 1; i <= ProDim; i++)
		for (int j = 1; j <= ProDim; j++) {
			MatrA[MakeIndex(i, j)] = m.MatrA[MakeIndex(i, j)];
			MatrB[MakeIndex(i, j)] = m.MatrB[MakeIndex(i, j)];
			A_i = m.A_i;
			A_j = m.A_j;
			B_i = m.B_i;
			B_j = m.B_j;
		}		
}

void Process::ProInitNul(int AI, int AJ, int BI,int BJ) {
	for (int i = 1; i <= ProDim; i++)
		for (int j = 1; j <= ProDim; j++) {
			MatrA[MakeIndex(i, j)] = 0;
			MatrB[MakeIndex(i, j)] = 0;
			A_i = AI;
			A_j = AJ;
			B_i = BI;
			B_j = BJ;
		}
}

void Process::ProPrint() {
	cout << "Pronumber: A" << A_i << A_j << " B" << B_i << B_j << endl;
	cout << "ProSize: " << ProDim << endl;
	cout << " MatrA" << endl;
	for (int i = 1; i <= ProDim; i++) {
		for (int j = 1; j <= ProDim; j++) {
			cout.width(10);
			cout << MatrA[MakeIndex(i,j)] << " ";
		}
		cout << endl ;
	}
	cout << "MatrB" << endl;
	for (int i = 1; i <= ProDim; i++) {
		for (int j = 1; j <= ProDim; j++) {
			cout.width(10);
			cout << MatrB[MakeIndex(i, j)] << " ";
		}
		cout << endl;
	}
}


int main() {
	/*
	cout << "----------M1-----------" << endl;
	Matrix M1(2); M1.InitRnd(); M1.Print();
	cout << "----------M2-----------" << endl;
	Matrix M2(2); M2.InitRnd(); M2.Print();
	Matrix M(2); M.Mult(M1, M2); M.Print();
	cout << "----------M3-----------" << endl;
	Matrix M3(2); M3.InitNul(); M3 -= M1; M3.Print();
	*/
	
	cout << "----------MM1-----------" << endl;
	HardMatrix MM1(2, 2); MM1.HardInitRnd(); MM1.HardPrint();
	cout << "----------MM2-----------" << endl;
	HardMatrix MM2(2, 2); MM2.HardInitRnd(); MM2.HardPrint();
	cout << "----------MM-----------" << endl;
	HardMatrix MM(2, 2); MM.HardMult(MM1, MM2); MM.HardPrint();
	
	cout << "--------MMKN-----------" << endl;
	HardMatrix MMKN(2, 2); MMKN.HardMultKN(MM1, MM2); MMKN.HardPrint();
	cout << "--------MMSC-----------" << endl;
	HardMatrix MMSC(2, 2); MMSC.HardInitNul();  MMSC.HardMultSC(MM1, MM2); MMSC.HardPrint();
	
	return 0;
	
}
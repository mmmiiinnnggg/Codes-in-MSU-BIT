#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

class Error{
    int i;
public:
    Error(int i=-1){
		this->i=i;
    }
    void Watch(){
        switch(i){
            case 0: cout<<"Sizes of matrices are not equal when operating"<<endl; break;
	        case 1: cout<<"Need square matrix to calculate inverse matrix (determinant)"<<endl; break;
	        case 2: cout<<"Need n equations with n unknowns, please check your system"<<endl; break;
	        case 3: cout<<"The system has inf solutions"<<endl; break;
	        case 4: cout<<"Not exist the element you want in matrix"<<endl; break;
        }
    }
};

class matrix: public Error {
	int n,m;//rows&columns
	double **mat;
	void init();//initiation
	static const double EPS = 1e-10;
public:
    matrix();//constructor by silence
    ~matrix();//destructor
    matrix(const matrix&);//constructor copier
    matrix& operator=(const matrix&);//give value

    //4.1
	matrix(int,int);//1---size of n*m
	matrix(double);//2---matrix with one element
	matrix(double*,int);//3---row-matrix
	matrix(int,double*);//4---column-matrix
	matrix(char*);//5---matrix in char
	static matrix identity(int);//6---identity matrix
	static matrix diagonal(double*,int);//7---diagonal matrix
	int rows();//9---number of rows
	int columns();//10---number of columns
	void setval(int,int,double);//11---give value to mat[i][j]
	matrix& operator[](int);//12,13---overload of []
	matrix operator*(double);//14---matrix times scalar with *
	void operator*=(double);//14---matrix times scalar with *=
	friend ostream& operator<<(ostream&,const matrix&);//15---overload of <<
	//4.2
	matrix operator+(const matrix&);//16---matrix + matrix
	void operator+=(const matrix&);//17---matrix += matrix
	matrix operator-(const matrix&);//18---matrix - matrix
	void operator-=(const matrix&);//19---matrix -= matrix
	double times(const matrix,const matrix,int,int);//20---i row * j column
	matrix operator*(const matrix&);//20---matrix * matrix
	void operator*=(const matrix&);//21---matrix *= matrix
	matrix operator-();//22---opposite matrix
	bool operator==(const matrix&);//23---matrix == matrix
	bool operator!=(const matrix&);//24---matrix != matrix
	matrix operator|(const matrix&);//25---matrix | matrix
	matrix operator/(const matrix&);//26---matrix / matrix
	//4.3
	void change_and_decline(int);//27,28,29---help function
	matrix& operator~();//27---inverse matrix
	double determinant();//28---determinant
	matrix solve();//29---solve equation
};

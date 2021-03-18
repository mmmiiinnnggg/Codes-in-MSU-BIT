#include <iostream>
#include <cstdlib>
#include <math.h>

using namespace std;

const int N=5;

class Matrix{
public:
	double MMM[N][N];	
public:
	Matrix(){Init0();}
	Matrix(Matrix&M);//constructor Matrix
	double GetR(int I1,int I2) {return MMM[I2][I1]/MMM[I1][I1];}//porprotion
	void Init0();//0 Matrix
	void Init1();//1 Matrix
	void InitRnd();//Random Matrix
	void Print();
	void MinusString(int I1,int I2,double R);
	
}; 

class Column{
public:	
	double AAA[N];
	void InitRnd();
	void InitMul(Matrix&,Column&);
	void Print();
};

class SLAU:public Matrix{
public:
	Column B;
	
	void InitRnd(); 
	void Print();
	void Forward();// Zero
	void BackWard();
};

//Methods:
Matrix::Matrix(Matrix &M){
	for(int i=0;i<N;i++)
	  for(int j=0;j<N;j++)
	    MMM[i][j]=M.MMM[i][j];
}

void Matrix::Init0(){
	for(int i=0;i<N;i++)
	  for(int j=0;j<N;j++)
	    MMM[i][j]=0;
}

void Matrix::Init1(){
	for(int i=0;i<N;i++)
	  for(int j=0;j<N;j++)
	    MMM[i][j]=(i==j)?1:0;
}

void Matrix::InitRnd(){
	for(int i=0;i<N;i++)
	  for(int j=0;j<N;j++)
	    MMM[i][j]=rand()/65536.0;
}

void Matrix::Print(){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
		//	cout.width(10);//设置字符宽度 
			cout.precision(3);//浮点数小数点后保留3位 
	    	cout<<MMM[i][j]<<" ";	
		} 
		cout<<endl;
	}
	cout<<endl;
}

//Row I2-I1
void Matrix::MinusString(int I2,int I1,double R){ 
	for(int i=0;i<N;i++)
		MMM[I2][i] -= R*MMM[I1][i]; 
}

void Column::InitRnd(){
	for(int i=0;i<N;i++)
	    AAA[i]=rand()/32767.0;
}

//Matrix M * Column C
// CHECK FUNCTION
void Column::InitMul(Matrix &M,Column &C){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			AAA[i]=0;
			AAA[i]+=M.MMM[i][j]*C.AAA[j];
		}
	}
}

void Column::Print(){
	for(int i=0;i<N;i++)
	  cout<<AAA[i]<<" ";
	cout<<endl;
}

void SLAU::Forward(){
	for(int i1=0;i1<N-1;i1++)
		for(int i2=i1+1;i2<N;i2++){
			double R=MMM[i2][i1]/MMM[i1][i1];
			MinusString(i2,i1,R);
			B.AAA[i2]-=R*B.AAA[i1];//Column B
		}
}

void SLAU::BackWard(Column&BBB){
	for(int i=N-1;i>=0;i--){
		double Mid=BBB.AAA[i];
		for(int j=N-1;j>i;j--)
		  Mid-=MMM[i][j]*B.AAA[j];
		B.AAA[i]=Mid/MMM[i][i];
	}
}

int main(){
//	Matrix A;
	SLAU A;
	Column B;
	Column X;
	A.InitRnd();
	B.InitRnd();
	A.Print();
	B.Print();
	
	A.Forward();
	A.Print();

	return 0;
} 

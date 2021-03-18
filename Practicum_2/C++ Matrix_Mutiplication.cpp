#include<iostream>

using namespace std;

class Matrix2{
	public:
		double a1,a2,b1,b2;
		Matrix2();
		Matrix2(double,double,double,double); 
		Matrix2(const Matrix2&,const Matrix2&);
		
		void Print();
	//	void det(const Matrix2&);
};

Matrix2::Matrix2(double a1,double a2,double b1,double b2){
	this->a1=a1;
	this->a2=a2;
	this->b1=b1;
	this->b2=b2;
}

Matrix2::Matrix2(const Matrix2&m1,const Matrix2&m2){
	a1=m1.a1*m2.a1+m1.a2*m2.b1;
	a2=m1.a1*m2.a2+m1.a2*m2.b2;
	b1=m1.b1*m2.a1+m1.b2*m2.b1;
	b2=m1.b1*m2.a2+m1.b2*m2.b2;
}

/*void Matrix2::det(const Matrix2&n1){
	int result;
	result=n1.a1*n1.b2-n1.a2*n1.b1;
	cout<<result<<;
}
*/
void Matrix2::Print(){
	cout<<'('<<a1<<' '<<a2<<','<<b1<<' '<<b2<<')';
}

int main(){
	Matrix2 m1(1,6,-2,7);
	Matrix2 m2(2,1,1,0);
	m1.Print();cout<<"*";m2.Print();
	Matrix2 m12(m1,m2);cout<<"=";
	
	m12.Print();cout<<endl;
/*	
	Matrix2 n1(1,6,-2,7);
	cout<<"det";n1.Print();cout<<"=";
    n1.det(n1);
*/	
	return 0; 
}



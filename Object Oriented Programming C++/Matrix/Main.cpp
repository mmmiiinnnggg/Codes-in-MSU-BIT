#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "ADT.h"
#include "ADT.cpp"

using namespace std;

int main(){
    //1
	matrix m1(5,5);
	cout<<"m1 with 0:"<<endl<<m1<<endl;
    //2
	matrix m2(2019);
	cout<<"m2 with 2019:"<<endl<<m2<<endl;
    //3
	double s[5]={1,2,3,4,5};
	matrix m3(s,5);
	cout<<"m3 row-matrix:"<<endl<<m3<<endl;
    //4
	matrix m4(5,s);
	cout<<"m4 column-matrix:"<<endl<<m4<<endl;
    //5
	char S[100]="{{1,0,0},{0,1,0.5},{1,2,3}}";
	matrix m5(S);
	cout<<"m5 from array char S"<<endl<<m5<<endl;
    //6
	matrix m6=matrix::identity(3);
	cout<<"m6 identity:"<<endl<<m6<<endl;
    //7
	matrix m7=matrix::diagonal(s,5);
	cout<<"m7 diagonal:"<<endl<<m7<<endl;
    //9
	cout<<"m5 row number:"<<endl<<m5.rows()<<endl;
    //10
	cout<<"m5 column number:"<<endl<<m5.columns()<<endl;
	//11
	try{m5.setval(6,3,4);cout<<"m5 change m5[2][3] to 4"<<endl<<m5<<endl;}
	catch(Error& e){e.Watch();}
    //12
	cout<<"m5[2] the 2-nd row of m5:"<<endl<<m5[2]<<endl;
    //13
	cout<<"m3[2] the 2-nd element of m2:"<<endl<<m3[2]<<endl;
    //14
	matrix m14=m5*2;
	cout<<"m14 m5 times 2:"<<endl<<m14<<endl;
	m14*=2;
	cout<<"m14 m14 times 2 itself:"<<endl<<m14<<endl;
	cout<<"------------------------------------"<<endl;


	char s1[100]="{{1,1.5,2},{0,1,0.5},{1,2,3}}";
	char s2[100]="{{1,2},{2,3},{3,4}}";
	matrix mm1(s1);
	matrix mm2(s2);
	cout<<"mm1:"<<endl<<mm1<<endl;
	cout<<"mm2:"<<endl<<mm2<<endl;

	//16
	try{cout<<"mm1+mm2:"<<endl<<(mm1+mm2)<<endl;}
        catch(Error& e){e.Watch();}
	//17
	try{mm1+=mm2;cout<<"mm1+=mm2(Now this is mm1):"<<endl<<mm1<<endl;}
        catch(Error& e){e.Watch();}
	//18
	try{cout<<"mm1-mm2:"<<endl<<(mm1-mm2)<<endl;}
        catch(Error& e){e.Watch();}
	//19
	try{mm1-=mm2;cout<<"mm1-=mm2(Now this is mm1):"<<endl<<mm1<<endl;}
        catch(Error& e){e.Watch();}
	//20
	try{cout<<"mm1*mm2:"<<endl<<(mm1*mm2)<<endl;}
        catch(Error& e){e.Watch();}
	//21
	try{cout<<"mm1*=mm2(Now this is mm1):"<<endl<<mm1<<endl;}
        catch(Error& e){e.Watch();}
	mm1*=mm2;
	//22
	cout<<"-mm1:"<<endl<<(-mm1)<<endl;
	//23
	try{cout<<"mm1==mm2:"<<endl<<(mm1==mm2)<<endl;}
        catch(Error& e){e.Watch();}
	//24
	try{cout<<"mm1!=mm2:"<<endl<<(mm1!=mm2)<<endl;}
        catch(Error& e){e.Watch();}
	//25
	try{cout<<"mm1|mm2:"<<endl<<(mm1|mm2)<<endl;}
        catch(Error& e){e.Watch();}
	//26
	try{cout<<"mm1/mm2:"<<endl<<(mm1/mm2)<<endl;}
        catch(Error& e){e.Watch();}
	cout<<"------------------------------------"<<endl;

	char m[100]="{{1,1,1},{2,3,4},{4,9,16}}";
	matrix M(m);
	//27
	cout<<"M:"<<endl<<M<<endl;
	try{cout<<"Det of M:"<<endl<<M.determinant()<<endl;}
        catch(Error& e){e.Watch();}
	//28
	try{cout<<"inverse of M:"<<endl<<~M<<endl;}
        catch(Error& e){e.Watch();}
	//29
	char a[100]="{{1,1,1},{0,1,1},{0,0,1}}";
	matrix A(a);
	char B[100]="{{1},{2},{3}}";
	matrix b(B);
	try{cout<<"Solve the system:"<<endl<<(A|b)<<endl;}
        catch(Error& e){e.Watch();}
    matrix x;
    try{x=(A|b).solve();}
        catch(Error& e){e.Watch();}
	cout<<"The solution is:"<<endl<<x<<endl;
	return 0;
}

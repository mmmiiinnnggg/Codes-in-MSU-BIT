#include<iostream>
using namespace std;
/*
double PowerSimple(double A,int B){
 int Degree2[10]={1,2,4,8,16,32,64,128,256,512};
 double DegreeA[10];
 DegreeA[0]=A;
 for(int i=1;i<=9;i++) DegreeA[i]=DegreeA[i-1]*DegreeA[i-1];
 double Return =1;
 for(int i=9;i>=0;i--){
   if(B<Degree2[i]) continue;
   B=B-Degree2[i];
   Return=Return*DegreeA[i];
   }
   return Return;
   }
   
*/   
class complex{
public:
 int x,y;
 complex(){};//to build a matrix
 complex(int ,int);
 complex(const complex&,const complex&);
 complex(const complex&);
 complex(const complex&, int);
 void Print();
};
complex::complex(int x,int y){
 this->x=x;
 this->y=y;
}
complex::complex(const complex&c1,const complex&c2){
 x=c1.x*c2.x-c1.y*c2.y;
 y=c1.x*c2.y+c1.y*c2.x;
}
complex::complex(const complex& c){
 x=c.x*c.x-c.y*c.y;
 y=2*c.x*c.y;
}
complex::complex(const complex&c3, int B){
 int Degree2[10]={1,2,4,8,16,32,64,128,256,512};
 complex DegreeA[10];
 DegreeA[0]=c3;
 for(int i=1;i<=9;i++) DegreeA[i]=complex(DegreeA[i-1]);
 complex Return(1,0);
 for(int i=9;i>=0;i--){
   if(B<Degree2[i]) continue;
   B=B-Degree2[i];
   Return = complex(Return,DegreeA[i]);//product of two number 
   }
   
 x=Return.x;
 y=Return.y;
}
void complex::Print(){
 cout<<'('<<x<<','<<y<<')'; 
}

int main(){
 complex c1(2,3);
 complex c2(3,-5);
 c1.Print(); cout<<"*";c2.Print(); cout<<"=";
 complex c3(c1,c2);
 
 c3.Print(); cout<< endl;
 complex c4(c2);
 c4.Print(); cout<< endl;
 
 c1.Print();cout<<"^21=";
 complex c53(c1,21);
 c53.Print();cout<<endl;
 
 return 0;
}   

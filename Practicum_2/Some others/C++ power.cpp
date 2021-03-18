nclude<iostream>

using namespace std;

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

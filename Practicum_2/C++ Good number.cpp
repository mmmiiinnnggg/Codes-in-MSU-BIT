#include<iostream>

using namespace std;

class Bil{
	public:
		int Max;
		int Arr[100];
		Bil(){Max=0;}
		
		void Init10();
		void Print();
		void Multi2(const Bil&,const Bil&);
		int AnswerSquare();
};

void Bil::Init10(){
	for(int i=0;i<10;i++) Arr[i]=1;
	Max=9;
} 

void Bil::Multi2(const Bil&B1,const Bil&B2){
	Max=B1.Max+B2.Max;
	for(int i=0;i<=Max;i++) Arr[i]=0;
	for(int i1=0;i1<=B1.Max;i1++) 
	  for(int i2=0;i2<=B2.Max;i2++)
	    Arr[i1+i2]=Arr[i1+i2]+B1.Arr[i1]*B2.Arr[i2];
}

int Bil::AnswerSquare(){
	int Return=0;
	for(int i=0;i<=Max;i++)
	  Return =Return +Arr[i]*Arr[i];
	  return Return;
}

void Bil::Print(){
	for(int i=0;i<=Max;i++) cout<<i<<':'<<Arr[i]<<' ';
}

int main()
{
	Bil BB1,BB1a,BB2,BB3;
	BB1.Init10();BB1.Print();cout<<endl;
	BB1a.Init10();
	BB2.Multi2(BB1,BB1a); BB2.Print();cout<<endl;
	BB3.Multi2(BB1,BB2); BB3.Print();cout<<endl;
	cout<<"前三位和等于后三位的六位数的个数： ";
	cout<<BB3.AnswerSquare()<<endl;
	
	return 0;
}



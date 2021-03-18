#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
const int Digit=3;

bool Grr[Digit];

int pow(int n,int Digit){
	int Res=1;
	for(int i=0;i<Digit;i++){
		Res*=n;
	}
	return Res;
}

//Gray code
void GrayInit(){
	for(int i=0;i<Digit;i++) Grr[i]=false;
}

//digit of change(reverse order):0 1 0 2 0 1 0 2 
int GrayNext(int M){
	return (M%2==0)?0:1+GrayNext(M/2);
} 

void GrrPrint(){
	for(int i=0;i<Digit;i++) printf("%d ",Grr[i]);
	printf("\n");
}

int Gray(){
	GrayInit();
	int N=pow(2,Digit);
	for(int i=0;i<N;i++){
		GrrPrint();
		int n=Digit-1-GrayNext(i);
		Grr[n]=!Grr[n];
	}
}

int main(){
	Gray();
	return 0;
}

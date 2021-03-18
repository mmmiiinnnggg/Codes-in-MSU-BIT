#include <stdio.h>
#include <stdlib.h>

const int N=3;
int A[N];

int Pow2(){
	int Res=1;
	for(int i=0;i<N;i++)
	    Res*=2;
	return Res; 
}

void Init(){
	for(int i=0;i<N;i++)
	    A[i]=i;
}

void Bin(int Binary[],int M){
	for(int i=N-1;i>=0;i--){
		Binary[i]=M%2;
	    M/=2;
	}  	    
}

void Subset(int Binary[]){
	int k=Pow2();
	int M=0;
	while(M<k){
		Bin(Binary,M);
		for(int i=0;i<N;i++)
		  if(Binary[i]) printf("%d ",A[i]);
		printf("\n");
		M++;
	}
}

int main(){
	int k=Pow2();
	int Binary[k];
	for(int i=0;i<N;i++)
	    Binary[i]=0;
	Init();
	printf("The subsets of %d numbers:\n",N);
	Subset(Binary);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> 

#define N 30 

int Frr[N];
int Par[N];

int min(int A,int B){
	if(A<=B) return A;
	return B;
}

//Finbonaqii
void FrrInit(){
	Frr[0]=1;
	Frr[1]=1;
	for(int i=2;i<N;i++) Frr[i]=-1;
}

int Fibo(int M){
	if(M<=1) return 1;
	if(Frr[M]<0) Frr[M]=Fibo(M-1)+Fibo(M-2);
	return Frr[M];
}

//Partition (with repeat)
int Partition(int NN){
	if(NN<=1) return 1;
	int S=0;
	for(int i=1;i<=NN;i++)
		S+=Partition(NN-i);
	return S;
}

//PartitionPro  (reduce recursion)
void ParInit(){
	Par[1]=1;
	for(int i=2;i<=N;i++) Par[i]=-1;
}

int PartitionPro(int NN){
    if(NN<=1) return 1;
	if(Par[NN]<0){
		Par[NN]=0;
		for(int i=1;i<=NN;i++)
		Par[NN]+=PartitionPro(NN-i);
	}
	return Par[NN];
}

//Partition (without repeat)
//M - number ,Max - biggest adder in M
int Parti(int M,int Max){
	if(M<=1) return 1;
	int S=0;
	for(int i=1;i<=min(M,Max);i++)
		S+=Parti(M-i,i);
	return S;
}

int main(){
	printf("Number:30\n");
	printf("\n");
	
	//Finbonaqii
	printf("Finbonaqii number:\n");
	FrrInit();
	for(int i=2;i<N;i++)
	  Frr[i]=Fibo(i);
	for(int j=0;j<N;j++)
	  printf("%d ",Frr[j]);
	printf("\n");
	printf("\n");
	
	//Partition of number N(repeat)(recursion)
	double Start1=clock();
	printf("Partition():\n");
	printf("%d\n",Partition(N));
	double End1=clock();
	printf("RunTime:%f\n",(End1-Start1)/CLOCKS_PER_SEC);
	printf("\n");
	
	//Partition of number N(reduce recursion)
	double Start2=clock();
	ParInit();
	printf("PartitionPro():\n");
	for(int i=0;i<=N;i++)
	  Par[i]=PartitionPro(i);
    printf("%d",Par[N]);
    printf("\n");
	double End2=clock();
    printf("RunTime:%f\n",(End2-Start2)/CLOCKS_PER_SEC);
	printf("\n");
	
	//Parti of number N
	printf("Parti():\n");
	printf("%d",Parti(N,N));
	return 0;
} 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define N 4

int A[N];
bool Dir[N];//false - left; true - right
void Init(){
	for(int i=0;i<N;i++)
	    A[i]=i+1;
}

void InitDir(){
	for(int i=0;i<N;i++)
	    Dir[i]=false;
}

void SwapA(int i,int j){
	int Tmp=A[i];
	A[i]=A[j];
	A[j]=Tmp;
}

void SwapDir(int i,int j){
	int Tmp=Dir[i];
	Dir[i]=Dir[j];
	Dir[j]=Tmp;
}

void Print(){
	for(int i=0;i<N;i++)
	    printf("%d ",A[i]);
	printf("\n");
}
bool MoveActive(){
	int Max=1;//max number
	int Index=-1;//position of max number
	//find the biggest active number
	for(int i=0;i<N;i++){
		if(A[i]<Max) continue;
		if( (i<N-1&&A[i]>A[i+1]&&Dir[i]) || (i>0&&A[i]>A[i-1]&&!Dir[i]) ){
			Max=A[i];
			Index=i;
		}
	}
	
	if(Index==-1) return false;//no active number
	
	//Swap [Index]==true - right exchange [Index]==false - left exchange
	if(Dir[Index]){
		SwapA(Index,Index+1);
		SwapDir(Index,Index+1);
	}
	else{
		SwapA(Index,Index-1);
		SwapDir(Index,Index-1);
	}
	
	//Change all direction of number which bigger than biggest active number
	for(int i=0;i<N;i++)
	    if(A[i]>Max) Dir[i]=!Dir[i];
	
	return true;
}

int main(){
	Init();
	InitDir();
	printf("The Permutation with exchange:\n");
	do{
		Print();
	} while(MoveActive());

    return 0;
}

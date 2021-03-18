#include <stdio.h>
#include <stdbool.h>

// m     m
//C     A
// n     n
const int n=5,m=3; 
const int num=100;
int a[num];
int M=m;
int Binary[n];

void Init(){
	for(int i=0;i<n;i++)
    a[i]=i+1;
}

void InitBinary(int n,int r){
	for(int i=0;i<r;i++)
		Binary[i]=1;
	for(int i=r;i<n;i++)
	    Binary[i]=0;
}

void Print(){
	for(int i=0;i<m;i++)
	    printf("%d ",a[i]);
	printf("\n");
}

void PrintPermu(int *b,int End){
	for(int i=0;i<=End;i++)
	  printf("%d ",b[i]);
	printf("\n");
}

void SwapBinary(int i,int j){
	int Tmp=Binary[i];
	Binary[i]=Binary[j];
	Binary[j]=Tmp;
}

void Swap(int *c,int *d){
	int Tmp=*c;
	*c=*d;
	*d=Tmp;
}

//递归：n位排列来源于n-1位排列 
void Permu(int *b,int Beg,int End){
	if(Beg>=End) PrintPermu(b,End);
	else{
		for(int i=Beg;i<=End;i++){
			Swap(&b[Beg],&b[i]);//交换头 
			Permu(b,Beg+1,End);
			Swap(&b[Beg],&b[i]);//交换末尾 
		}
	}
}

//1 - Combination with recursion
void combination(int n,int m,int flag){
	if(m<1) {
		if(flag=='A'){
			int Arr[M];
		    for(int i=0;i<M;i++)
		    Arr[i]=a[i];
		    Permu(Arr,0,M-1);
	  	    printf("\n");
		    return;	
		}
		else{
		    Print();
	    	return;	
		}	
	}
	
	for(int i=n;i>=m;i--){
		a[m-1]=i;//chhose the last one
		combination(i-1,m-1,flag);
	}
}

//2 - Combination with Binary 
void CombiBinary(int n,int m,int flag){
	if(m>n) return;
	InitBinary(n,m);
	bool bFind=true;	
	while(bFind){
		if(flag=='A'){
			int Arr[m];
		    int index=0;//Matrix of Permutation
		    for(int i=0;i<n;i++)
			if(Binary[i]){
				Arr[index]=a[i];
			    index++;
			}
		Permu(Arr,0,m-1);  
		printf("\n");
	    }
		else{
			for(int i=0;i<n;i++)
			if(Binary[i])
			    printf("%d ",a[i]);
		    printf("\n");
		}
		
		bFind=false;

		for(int i=0;i<n-1;i++)
		  if(Binary[i]==1&&Binary[i+1]==0){
			SwapBinary(i,i+1);
			bFind=true; 
			if(Binary[0]==0){
			   for(int k=0,j=0;k<i;k++)
			       if(Binary[k]){
			       	SwapBinary(k,j);
			       	j++;
			       }
			} 
			break;
		  }
	}
}

int main() {
	if(m>n) printf("input error!");
	char A='A';
	char C='C';
	printf("Combination with recursion without order:\n");
	Init();
	combination(n,m,C);
	printf("\n");
	printf("Combination with Binary without order:\n");
	Init();
	CombiBinary(n,m,C);
	
	printf("Combination with recursion with order:\n");
	Init();
	combination(n,m,A);
	printf("\n");
	printf("Combination with Binary with order:\n");
	Init();
	CombiBinary(n,m,A);
	return 0;
} 


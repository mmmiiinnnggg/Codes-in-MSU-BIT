#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#define N 32
#define Base 11//size of unsigned int array

unsigned char AAA[N];
unsigned char CCC[N];
unsigned char DDD[N];
unsigned char MAX[N];
    
//Initialization
void Init(unsigned char Tmp[N],unsigned int n){
    for(int i=0;i<N;i++){
 	    Tmp[i]=n%256;
 	    n/=256;
    }
} 

//Copy from B to A
void Copy(unsigned char A[N],unsigned char B[N]){
	for(int i=0;i<N;i++)
	    A[i]=B[i];
}

//Print
void Print(unsigned char X[N]){
	for(int i=N-1;i>=0;i--)
	  printf("%X ",X[i]);
	printf("\n");
}

//Addition:C=A+B
void Add(unsigned char C[N],unsigned char A[N],unsigned char B[N]){
	int Digits=0;
	int Res;
	for(int i=0;i<N;i++){
		Res=Digits+A[i]+B[i];
		C[i]=Res%256;
		Digits=Res/256;
	}
}

//Multiplication of dight:C=A*B
void MulDigit(unsigned char C[N],unsigned char A[N],unsigned char B){
	Init(C,0);
	int Dights=0;
	int Res;
	for(int i=0;i<N;i++){
		Res=Dights+A[i]*B;
		C[i]=Res%256;
		Dights=Res/256;
	}
}

//Digit shift forward k position
void Shift(unsigned char A[N],int k){
    for(int i=N-1;i>=k;i--)
    	A[i]=A[i-k];
    for(int j=k-1;j>=0;j--)
    	A[j]=0;	
}

//Multiplication:C=A+B
void Multi(unsigned char C[N],unsigned char A[N],unsigned char B[N]){
	Init(C,0);
	for(int i=0;i<N;i++){
		unsigned char Tmp[N];
		MulDigit(Tmp,A,B[i]);
		Shift(Tmp,i);
		Add(C,C,Tmp);
	}
}

//The Signal number
void Max(unsigned char MAX[N]){
	for(int i=0;i<=N-2;i++)
	    MAX[i]=255;
	MAX[N-1]=22;//63*4=252<256 for 3^N
}

//A<B ->true; A>=B ->false
bool Less(unsigned char A[N],unsigned char B[N]){
	for(int i=N-1;i>=0;i--){
		if(A[i]<B[i]) return true; 
		if(A[i]>B[i]) return false;	
	}
	return true;
}

void Number(){
	Init(AAA,Base);
	Init(CCC,1);
	Print(AAA);
	Print(CCC);
	for(int i=1;;i++){
		printf("%d ",i);
		Multi(DDD,CCC,AAA); 
		Copy(CCC,DDD);
		if(!Less(CCC,MAX)){
			printf("Bigger ");
			Print(CCC);
			break;
		} 
		else
		    printf("Smaller ");
            Print(CCC);	
	    } 	    
}

int main(){
	Max(MAX);
	Print(MAX);
    Number();
	return 0;
}




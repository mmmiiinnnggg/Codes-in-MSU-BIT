#include <stdio.h>
#include <stdlib.h>

#define N 32//size of unsigned int array

unsigned char AAA[32];
unsigned char BBB[32];
unsigned char CCC[32];
unsigned char DDD[32];

//Initialization
void Init(unsigned char Tmp[N],long long n){
  int i=0;
  while(n/256){
  	Tmp[i++]=n%256;
  	n=n/256;
  }
  Tmp[i]=n;
} 

//Print
void Print(unsigned char X[N]){
	for(int i=N-1;i>=0;i--)
	  printf("%X ",X[i]);
}

//Addition 
void Add(unsigned char C[N],unsigned char A[N],unsigned char B[N]){
	for(int i=0;i<N;i++){
		//if have number carrying
		if(A[i]+B[i]+C[i]>=256){    
			C[i]+=A[i]+B[i]-256;     
			C[i+1]+=1;              
		}
		else C[i]+=A[i]+B[i];
	}
}

//Multiplication 
void Multi(unsigned char C[N],unsigned char A[N],unsigned char B[N]){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(A[j]*B[i]+C[j+i]>=256){
			    C[j+i]+=(A[j]*B[i])%256;
			    C[j+i+1]+=(A[j]*B[i])/256;
		    }
		    else C[j+i]+=A[j]*B[i];
		}
	}
}
 
int main(){
	long long int m,n;
	printf("Input 1st number:\n");
	scanf("%lld",&m);
	printf("Input 2nd number:\n");
	scanf("%lld",&n);
	Init(AAA,m);
	Init(BBB,n);
	
	printf("New form of m:\n");
	Print(AAA);
	printf("\n");
	printf("New form of n:\n");
	Print(BBB);
    printf("\n");
    
	printf("The sum of m and n:\n");
	Add(CCC,AAA,BBB);
	Print(CCC);
	printf("\n");
	
	printf("The mutil of m and n:\n");
	Multi(DDD,AAA,BBB); 
	Print(DDD);
	
	return 0;
}




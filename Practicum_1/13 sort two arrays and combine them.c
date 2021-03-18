#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 20
#define M 40

void bubble(int x[],int n)
{
	int i,j,tmp;
	for(i=1;i<n;i++)
	 for(j=n-1;j>=i;j--)
	   if(x[j-1]>x[j])
	   {
	   	  tmp=x[j];
	   	  x[j]=x[j-1];
	   	  x[j-1]=tmp;
	   }
}

int main()
{
	int C[N],D[N],E[M];
	int i,j;
	srand(time(NULL));
	for(i=0;i<N;i++)
	  C[i]=rand()%21;
    for(j=0;j<N;j++)
      D[j]=rand()%21;
      
    printf("The first matrix:\n");
    for(i=0;i<N;i++)
	  printf("%d ",C[i]);
	printf("\n");
	printf("The second matrix:\n");
    for(j=0;j<N;j++)
      printf("%d ",D[j]);//generate 2 matrix with random numbers and print out
    printf("\n");  
      
    for(i=0;i<N;i++)
      E[i]=C[i];
    for(j=20;j<M;j++)
      E[j]=D[j-20];
    
	bubble(E,M);
	printf("The final matrix:\n");
	for(i=0;i<M;i++)
      printf("%d ",E[i]);//print out new matrix E
      
    return 0;
} 

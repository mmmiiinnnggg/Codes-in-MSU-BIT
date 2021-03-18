#include<stdio.h>
#define N 1000

int main()
{
	float x[N],y[N];
	int n,i,j,k,judge1=0,judge2=0;
	printf("Please type in the size of matrixs:\n");
	scanf("%d",&n);
	
	printf("Please type in the first matrix:\n");
	for(i=0;i<n;i++)
	  scanf("%f",&x[i]);
	printf("Please type in the second matrix:\n");
	for(j=0;j<n;j++)
	  scanf("%f",&y[j]);
	  
	if(x[0]>=y[0])
    {
    	for(k=0;k<n;k++)
	       if(x[k]>=y[k]) judge1++;   
    }
    
    if(x[0]<=y[0])
    {
    	for(k=0;k<n;k++)
    	  if(x[k]<=y[k]) judge2++;
    }
    //printf("%d %d",judge1,judge2);
    if(judge1==n) printf("X dominates Y.");
    if(judge2==n) printf("Y dominates X.");
    if(judge1!=n&&judge2!=n) printf("No relation.");
    
    return 0;
} 

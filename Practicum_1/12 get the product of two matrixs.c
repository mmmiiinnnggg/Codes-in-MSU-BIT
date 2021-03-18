#include<stdio.h>

int main()
{
    int a[100][100],b[100][100],c[100][100];
	int n,i,j,k;
	printf("Please type in a number:\n");
	scanf("%d",&n);
	printf("Please type in matrix a with size of n*n:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	
	printf("Please type in matrix b with size of n*n:\n");
    for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&b[i][j]);
		}
	}
	
    for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
			    c[i][j]+=a[i][k]*b[k][j];	
			}
		}
	}
	
	printf("The result is:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",c[i][j]);
		}	
		
		printf("\n");
	}
	
	return 0;
}

/*
#include<stdio.h>        //12.
#define maxn 1000
int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn];
int main( )
{
	int n,i,j,k;
	scanf("%d",&n);
	for (i=0;i<n;i++) 
	   for (j=0;j<n;j++) scanf("%d",&a[i][j]);
	for (i=0;i<n;i++) 
	   for (j=0;j<n;j++) scanf("%d",&b[i][j]);
	for (i=0;i<n;i++)
	   for (j=0;j<n;j++) 
	      for (k=0;k<n;k++) c[i][j]+=a[i][k]*b[k][j];
	for (i=0;i<n;i++)
	   {
		for (j=0;j<n;j++) printf("%d ",c[i][j]);
		printf("\n");
	   }
	return 0;
}
*/ 

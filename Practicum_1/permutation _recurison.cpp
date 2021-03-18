#include<stdio.h>
#define N 100
int num=1;

void print(int a[],int n)
{
	int i;
	printf("%d£º",num++);
	for(i=0;i<n;i++)
	  printf("%d",a[i]);
	printf("\n");
} 

void genper(int a[],int msk[],int n,int i)
{
	if(i==n) print(a,n);
	else
	{
		int j;
		for(j=0;j<n;j++)
		  if(msk[j]==0)
		  {
			msk[j]=1;
			a[i]=j+1;
			genper(a,msk,n,i+1);
			msk[j]=0;
		  }
	}
}

int main()
{
	int a[N],n,msk[N]={0},i=0;
	printf("Please type in the size of matrix n:");
	scanf("%d",&n);
	genper(a,msk,n,i);
	return 0;
}

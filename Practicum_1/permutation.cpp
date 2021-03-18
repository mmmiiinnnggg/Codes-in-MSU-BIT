#include<stdio.h>
#define N 100
 int num=1;
void swap(int a[],int i,int j)//function of change 
{
	int s=a[i];
	a[i]=a[j];
	a[j]=s;
}
void print(int a[],int n)//function of print
{
	
	printf("%d:",num++);
	for(int i=0;i<n;i++)
	  printf("%d",a[i]);
	printf("\n");
}

int next(int a[],int n)//THe next permutation
{
	int j=n-2;
	while((j!=-1)&&(a[j]>=a[j+1])) j--;
	if(j==-1) return 0;
	int k=n-1;
		//print(a,n);
	while(a[j>=a[k]]) k--;
	swap(a,j,k);
	int l=j+1,r=n-1;
	while(l<r) swap(a,l++,r--);
	return 1;
}


int main()
{
	int a[]={1,2,3,4},n=4;
	print(a,n);
	while(next(a,n)) print(a,n);
	return 0;
}

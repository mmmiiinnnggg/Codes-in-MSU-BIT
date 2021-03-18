#include<stdio.h>
#define N 1000

void choose(int a[],int n)
{
	int i,j,min,imin;
	for(i=0;i<n-1;i++)
	{
		min=a[i];
		imin=i;
		for(j=i+1;j<n;j++)
	    if(min>a[j])
	    {
	    	min=a[j];
	    	imin=j;
	    }
	    a[imin]=a[i];
	    a[i]=min;  
	}  
}
	
int main()
{
	int i,j,ia=0,ib=0,n,m[N],a[N],b[N],mnew[N];
	printf("Please type in the size of matrix:\n");
	scanf("%d",&n);
	printf("Pleae type in the elements of matrix:\n");
	for(i=0;i<n;i++)
	  scanf("%d",&m[i]);//type in original matrix  
	for(i=0;i<n;i++)
	{
      if(m[i]>=0) a[ia++]=m[i];
	  else b[ib++]=m[i];
	}//divide into two parts
	
	choose(a,ia);
	choose(b,ib);//put numbers in order
	
	/*
	for(i=0;i<ia;i++)
      printf("%d ",a[i]);
    printf("\n");
    for(i=0;i<ib;i++)
      printf("%d ",b[i]);
    printf("\n");
	*/
	
	for(i=0;i<ia;i++)
      mnew[i]=a[i];
    for(i=ia;i<n;i++)
      mnew[i]=b[i-ia];//combine two matrixs
    
    printf("The final matirx:\n");
	for(i=0;i<n;i++)
      printf("%d ",mnew[i]);
      
    return 0;
} 

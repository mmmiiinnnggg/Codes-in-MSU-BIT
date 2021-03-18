#include<stdio.h>
#define N 100

void sort_quick_index( int a[], int ind[], int n, int l, int r) { 
  int i=l, j=r, mid=(l+r)/2, tmp; 
  do { while ( a[ind[i]]<a[ind[mid]] ) i++;  
       while ( a[ind[j]]>a[ind[mid]] ) j--; 
       if (i<=j) { 
         if (mid==i) mid=j; 
         else if (mid==j) mid=i;
         tmp = ind[i]; ind[i]=ind[j]; ind[j]=tmp; 
         i++; j--; 
       }; 
  } while (i<j); 
    if (l<j) sort_quick_index(a,ind,n,l,j); 
    if (i<r) sort_quick_index(a,ind,n,i,r); 
}

int main()
{
	int a[N],ind[N],n,l,r,i;
	scanf("%d",&n);
	l=0;r=n-1;
	for(i=0;i<n;i++)
	  scanf("%d",&a[i]);
	for(i=0;i<n;i++)
	  ind[i]=i;
	  
	sort_quick_index(a,ind,n,l,r);
	for(i=0;i<n;i++)
	  printf("%d ",a[ind[i]]);
	  
	return 0;
}

#include<stdio.h>
#define N 10



int main()
{
	int x,tmp,a[N]={2,9,7,4,5,1,3,8,6,4};
	int i,j,l,r=N-1,s=0,low[N],high[N];
	low[0]=0;high[0]=N-1;
	while(s>=0)
	{
	  l=low[s];
	  r=high[s];
	  s--;
	  while(l<r)
	  {
	  	i=l;j=r;
	  	x=a[(l+r)/2];
	  	while(i<=j)
	    {
		  while(a[i]<x) i++;
		  while(a[j]>x) j--;
		  if(i<=j) {tmp=a[i];a[i]=a[j];a[j]=tmp;i++;j--;}
	    }
	    if(i<r) {s++;low[s]=i;high[s]=r;}
	    r=j;
	  }
	}

    for(i=0;i<N;i++) printf("%d",a[i]);
	return 0;
		
}

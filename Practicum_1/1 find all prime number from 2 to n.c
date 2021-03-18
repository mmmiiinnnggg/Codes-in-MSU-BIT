#include<stdio.h>
 
int main()//from 2 to n
{
	int i,j,n;
	printf("Please type in n to get the prime numbers from 2 to n.\n");
	scanf("%d",&n);
	int a[n+1];
	for(i=2;i<n+1;i++) 
	  a[i]=1;//将a【2】至a【n】的数记为1
	   
	for(i=2;i<n+1;i++)
	  {
	  	if(a[i])//如果指数未被删去，可以执行下列语句 
	  	  {
			for(j=2;i*j<n;j++)
	  	      a[i*j]=0;//将指数为合数对应的值改为0 
	  	  }
	  }	
	  
	  for(i=2;i<n+1;i++)
	  {
	  	if(a[i])
	  	  printf("%d ",i);//将质数打印出来 
	  }
	return 0;
}




 

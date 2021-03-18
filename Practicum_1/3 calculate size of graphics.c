#include<stdio.h>

/*float x5(float x)
{
	float y;
	y=x*x*x*x*x; 
	return y;
}*/
float x5(float x)
{
	float y=1;
	for(int i=1;i<=5;i++)
	{
		y=y*x;
	}
	
	return y;
}

/*float sizeofgra(float a,float b,float eps)
{
	float sum=0,s,i;
	for(i=a;i<=b;i=i+eps)
	{
		s=0.5*eps*fabs(x5(i)+x5(i+eps));
		sum=sum+s;
	}
	return sum;
}*/

float sizeofgra(float a,float b,float eps)
{
	float sum=0,s;
	while(a<b)
	{
		s=0.5*eps*fabs(x5(a)+x5(a+eps));
		sum=sum+s;
		a=a+eps;
	}
	return sum;
}
int main()
{
	float a,b,eps;
	printf("Please type in a,b and eps:\n");
	scanf("%f%f%f",&a,&b,&eps);
	printf("sum=%f",sizeofgra(a,b,eps));
	return 0;
}

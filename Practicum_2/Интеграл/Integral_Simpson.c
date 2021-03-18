#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Func(double x){
    return x*x;
}

double Integral_Simpson(double a,double b,double eps){
   double S1=0,S2=0;
   int N=1,i,j;
   double interval=b-a;
   double Intergal;
   while(interval>eps){
      N=2*N;
      interval=(b-a)/N;
   }

   for(i=1;i<N;i++)
      S1+=Func(a+i*interval);
   for(j=0;j<N;j++)
      S2+=Func(a+interval/2+j*interval);
   return interval/6*(Func(a)+Func(b)+2*S1+4*S2);
}

int main()
{
    double a=0;
    double b=1;
    printf("%lf",Integral_Simpson(a,b,0.0000001));
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Func(double x){
    return x*x;
}

double Integral_Left_Rec(double a,double b,double eps){
   double S=0;
   int N=1,i;
   double interval=b-a;
   double Intergal;
   while(interval>eps){
      N=2*N;
      interval=(b-a)/N;
   }

   for(i=0;i<N;i++)
      S+=Func(a+i*interval);
   Intergal=interval*S;

   return Intergal;
}

int main()
{
    double a=0;
    double b=1;
    printf("%lf",Integral_Left_Rec(a,b,0.0000001));
    return 0;
}



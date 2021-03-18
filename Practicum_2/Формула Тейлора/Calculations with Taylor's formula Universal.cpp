#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
//对于exp(x),sin(x),cos(x),ln(1+x),arctg(x)通用的泰勒计算公式 
double Uni(double X,double eps,bool Diff,bool Jump,bool Sign,bool Fac){
	//Diff：从1开始还是从X开始 
	//Jump：指数有没有间隔 
	//Sign：符号有没有改变
	//Fac：分母是阶乘还是递增 
	double R;
	double Elem=Diff?1:X;
	int N=Diff?0:1;
	while(Elem>eps){
		R+=Elem;
		Elem*=X;
	    N++;
		    Elem=Fac? Elem/N : Elem*N/(N+1);//Elem/=N;
		    if(Jump){
			    Elem*=X;
		        N++;
		        Elem=Fac? Elem/N : Elem*N/(N+1);
	    	}
			if(Sign) Elem=-Elem;
	}
	return R;
}

int main(){
    Uni(); 
	return 0;
}

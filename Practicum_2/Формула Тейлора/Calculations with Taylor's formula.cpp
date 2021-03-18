#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//float -> (double) 
float Eps[6];

void GenerateEps(){
	Eps[0]=0.1;
	for(int i=1;i<6;i++)
	  Eps[i]=Eps[i-1]/10;
}
float ConvertToRadian(float theta){
	return theta*3.1415926/180;
}

//Calculate next element
//n - index, x - exponent, Curr - current element
float ExpNext(int n,float x,float Curr){
	return Curr*(x/(n+1));
}

float SinCosNext(int n,float x,float Curr){
	return (-1)*Curr*((x*x)/((n+2)*(n+1)));
}

float LnNext(int n,float x,float Curr){
	return (-1)*Curr*x*n/(n+1);
}

float ArctgNext(int n,float x,float Curr){
	return (-1)*Curr*x*x*n/(n+2);
}

//functions
float Exp1(float x,float eps){
	float sum=1.0;//The result
	int n=0;//exponent 
	float Curr=1.0;//current element 
	while(fabs(Curr)>eps){
		Curr=ExpNext(n,x,Curr);//next element
		sum+=Curr;
		n++;
	}
	return sum;
} 

float Sin1(float theta,float eps){
	float x=ConvertToRadian(theta);
	float sum=x;//The result
	int n=1;//exponent 
	float Curr=x;//current element 
	while(fabs(Curr)>eps){
		Curr=SinCosNext(n,x,Curr); //next element
		sum+=Curr;
		n+=2;
	}
	return sum;
} 


float Cos1(float theta,float eps){
	float x=ConvertToRadian(theta);
	float sum=1.0;//The result
	int n=0;//exponent 
	float Curr=1.0;//current element 
	while(fabs(Curr)>eps){
		Curr=SinCosNext(n,x,Curr); //next element
		sum+=Curr;
		n+=2;
	}
	return sum;
} 

float Ln1(float x,float eps){
	float sum=x;//The result
	int n=1;//exponent 
	float Curr=x;//current element 
	while(fabs(Curr)>eps){
		Curr=LnNext(n,x,Curr); //next element
		sum+=Curr;
		n++;
	}
	//printf("%d\n",n);
	return sum;
} 

float Arctg1(float x,float eps){
	float sum=x;//The result
	int n=1;//exponent 
	float Curr=x;//current element 
	while(fabs(Curr)>eps){
		Curr=ArctgNext(n,x,Curr); //next element
		sum+=Curr;
		n+=2;
	}
	return sum;
} 

int main(){
	float x;
	int choose;
	printf("1: e^x\n");
	printf("2: sin(x)\n");
	printf("3: cos(x)\n");
	printf("4: ln(1+x)\n");
	printf("5: arctg(x)\n");
    printf("\n");
    //scanf("%d",&choose);
    GenerateEps();
    
    int arr1[]={-3,-2,0,2,3};
    int arr2[]={15,30,45,60,90};
    float arr3[5]={-0.5,-0.25,0,0.5,1};
    
    printf("Exp(x):");
    for(int i=0;i<5;i++){
    	printf("\n");
    	printf("x No.%d:\n",i+1);
    	for(int j=0;j<6;j++)
        	printf("%f\n",Exp1(arr1[i],Eps[j]));
    }printf("\n");
    
    printf("Sin(x):");
     for(int i=0;i<5;i++){
    	printf("\n");
    	printf("x No.%d:\n",i+1);
    	for(int j=0;j<6;j++)
        	printf("%f\n",Sin1(arr2[i],Eps[j]));
    }printf("\n");
    
    printf("Cos(x):");
     for(int i=0;i<5;i++){
    	printf("\n");
    	printf("x No.%d:\n",i+1);
    	for(int j=0;j<6;j++)
        	printf("%f\n",Cos1(arr2[i],Eps[j]));
    }printf("\n");
    
    printf("Ln(1+x):");
     for(int i=0;i<5;i++){
    	printf("\n");
    	printf("x No.%d:\n",i+1);
    	for(int j=0;j<6;j++)
        	printf("%f\n",Ln1(arr3[i],Eps[j]));
    }printf("\n");
    
    printf("Arctg(x):");
     for(int i=0;i<5;i++){
    	printf("\n");
    	printf("x No.%d:\n",i+1);
    	for(int j=0;j<6;j++)
        	printf("%f\n",Arctg1(arr3[i],Eps[j]));
    }printf("\n");

	return 0;
}

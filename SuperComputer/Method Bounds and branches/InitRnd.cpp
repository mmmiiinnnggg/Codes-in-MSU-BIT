#include<iostream>
#include<time.h>
#include<cstdlib>
#include<cstdio>

using namespace std;

const int nInfty = 99999;
const int dim = 23;

double f(double x){ // 3/5*f(x)
	return 1.0/2*(1+x*x*x*x);
}

double Rnd(){ 
	int x;
	x=rand()%100;
	return x/100.0;
}

double GetRnd(){
	double u1,u2;
	while(1){
		u1=Rnd();
		u2=Rnd();
		if(u2<=f(u1))
			return u1;
	}
}

int main(){
	FILE* fp1;
	if ((fp1 = fopen("test23.txt", "w+")) == NULL){
    //if ((err= fopen_s(&fp1,"test1.txt", "r")) == 0) {
        printf("Cannot open test file\n");
        exit(0);
    }
    int rnd;
    char str[6];
    srand(time(NULL));
    for(int i=1;i<=dim;i++){
    	for(int j=1;j<=dim;j++){
    		if(i==j){
    			itoa(nInfty,str,10);
    			fputs(str,fp1);
    			if(j!=dim) {fputs(" ",fp1);}
    		}
    		else{
    			rnd = GetRnd()*100;
    			itoa(rnd,str,10);
    			fputs(str,fp1);
    			if(j!=dim) fputs(" ",fp1);
    		}
    	}
    	fputs("\n",fp1);
    }

    fclose(fp1);
	return 0;
}
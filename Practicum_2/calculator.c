#include <stdio.h>
#include <setjmp.h>

jmp_buf begin;
char curlex;
void getlex(void);
double fpow(double n,double p);
double expr(void);
double add(void);
double mult(void);
double minus(void);
double div(void);
double powe(void);
void error(void);

int main(){
	double result;
	if(setjmp(begin)==0)
		printf("==>");
	else 
		printf("again\n==>");
	getlex();
	result=expr();
	if(curlex!='\n') 
		error();
	printf("%lf\n",result);
	return 0;
}

void getlex(void){ 
	while((curlex=getchar())==' ');
}

void error(void){
	printf("wrong!\n");
	while(getchar()!='\n');
	longjmp(begin,1);
}

double fpow(double n,double p){
	double np=1;
	int i=0;
	for(i=0;i<p;++i)
		np*=n;
	return np;
}

double expr(void){
	double e=add();
	while (curlex =='+'){
		getlex();
		e+=add();
	}
	return e;
}

double add(void){
	double a=minus();
	while(curlex=='-'){
		getlex();
		a-=minus();
	}
	return a;
}

double minus(void){
	double a=mult();
	while(curlex=='*'){
		getlex();
		a*=mult();
	}
	return a;
}

double mult(void){
	double a=div();
	while(curlex=='/'){
		getlex();
		a/=div();
	}
	return a;
}

double div(void){
	double a=powe();
	while(curlex=='^'){
		getlex();
		a=fpow(a,div());
	}
	return a;
}

double powe(void){
	double m;
	switch(curlex){
		case '0':case '1':case '2':case '3':case '4':case '5':
		case '6':case '7':case '8':case '9':m=curlex-'0';break;
		case '(':getlex();m=expr();if(curlex == ')')break;
		default : error();
	}
	getlex();
	return m;
}

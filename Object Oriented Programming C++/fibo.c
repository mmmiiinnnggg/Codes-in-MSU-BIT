#include <stdio.h>

int fibo(int N){
	if(N==1) return 1;
	if(N==2) return 1;
	return fibo(N-1)+fibo(N-2);
}
int main(){
	int N,F;
	scanf("%d",&N);
	printf("F=%d",fibo(N));
	return 0;
}

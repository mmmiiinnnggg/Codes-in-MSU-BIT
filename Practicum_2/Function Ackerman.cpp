#include <stdio.h>

int Acker(int m,int n){
	if(m==0) return n+1;
	if(m>0&&n==0) return Acker(m-1,1);
	if(m>0&&n>0) return Acker(m-1,Acker(m,n-1));
}

int main(){
	printf("%d",Acker(4,4));
	return 0;
}

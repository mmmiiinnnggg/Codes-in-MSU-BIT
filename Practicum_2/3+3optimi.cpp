#include <iostream>
#include <stdio.h>
using namespace std;

int main(){
	int i=0, sum, sum1=0;
	for(int i=0; i<=27; i++){
        sum =0;
        for(int a=0; a<=9; a++)
            for(int b=0; b<=9; b++)
                for(int c=0; c<=9; c++)
                    if(i == a+b+c) sum++;
        sum1 += sum*sum;
	}
	cout << sum1 << endl;
	return 0;
}

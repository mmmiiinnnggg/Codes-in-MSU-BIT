#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define SIZE 100
//Программа. В файле записана непустая последовательность целых чисел, являющихся числами Фибоначчи. Приписать еще одно, очередное число Фибоначчи.

int main(){
  FILE *f1;
  int fib[SIZE];
  int k=0,i,a;
  if((f1=fopen("finbo.txt","r"))==NULL) exit(-1); 
  while((fscanf(f1,"%d",&a)>0)) fib[k++]=a;
  for(i=0;i<k;i++) printf("%d ",fib[i]);
  printf("Next fibo number =%d\n",fib[k-1]+fib[k-2]);
  fseek(f1,0,SEEK_END);
  fprintf(f1,"%d",fib[k-1]+fib[k-2]);
  fclose(f1);
  return 0;
}
//finish


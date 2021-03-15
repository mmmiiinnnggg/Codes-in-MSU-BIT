#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define SIZE 1000
//Написать программу, определяющую какой символ чаще других встречается в данном файле. Имя файла задается в командной строке.
int main(int argc,char **argv){
  FILE *f1;
  int i=0,q[123]={0};
  char c;//symbol
  if(argc!=2) {perror("Error input instructions\n");exit(-1);}
  if((f1=fopen(argv[1],"r"))==NULL) exit(-1); 

  while((c=fgetc(f1))!=EOF){//stop when meet end of file
    for(i=65;i<=90;i++) if(i==c) q[i]++;//65-90:A-Z 
    for(i=97;i<=122;i++) if(i==c) q[i]++;//97-123:a-z
  }
  
  int countmax=q[65];//max number of symbol c
  for(i=65;i<=122;i++) if(q[i]>countmax) {countmax=q[i];c=i;}
  printf("countmax=%d,symbol=%c\n",countmax,c);
  fclose(f1);
  return 0;
}
//finish




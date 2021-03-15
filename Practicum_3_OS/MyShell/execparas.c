#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char cmd[30];
char buf[10][10];
int command[30]={0};//mark the command line in 2-dim buf

//put command line to a 2-dim matrix
int collect(){ 
  int i=0,j=0,k=0,index=0;
  char a,b;
  fgets(cmd,30,stdin);
  while((a=cmd[index])!='\n')
    switch(a){
      case '>': if((b=cmd[index+1])=='>') {i++;j=0;buf[i][j]=a;j++;buf[i][j]=b;command[i]=1;i++;j=0;index+=2;break;}//>>
                else {i++;j=0;buf[i][j]=a;command[i]=2;i++;j=0;buf[i][j]=b;j++;index+=2;break;}//>
      case '|': if((b=cmd[index+1])=='|') {i++;j=0;buf[i][j]=a;j++;buf[i][j]=b;command[i]=3;i++;j=0;index+=2;break;}//||
                else {i++;j=0;buf[i][j]=a;command[i]=4;i++;j=0;buf[i][j]=b;j++;index+=2;break;}//|
      case '<': {i++;j=0;buf[i][j]=a;command[i]=5;i++;j=0;index++;break;}
      case '&': {i++;j=0;buf[i][j]=a;command[i]=6;i++;j=0;index++;break;}
      case ';': {i++;j=0;buf[i][j]=a;command[i]=7;i++;j=0;index++;break;}
      case '(': if(index==0) {buf[i][j]=a;command[i]=8;index++;break;}
                else {i++;j=0;buf[i][j]=a;command[i]=8;index++;break;}
      case ')': if(index==0) {buf[i][j]=a;command[i]=8;index++;break;}
                else {i++;j=0;buf[i][j]=a;command[i]=9;index++;break;}
      case ' ': if((b=cmd[index+1])=='&') {i++;j=0;buf[i][j]=a;command[i]=10;i++;j=0;buf[i][j]=b;command[i]=6;i++;j=0;index+=2;break;}//||
                else {i++;j=0;buf[i][j]=a;command[i]=10;i++;j=0;buf[i][j]=b;j++;index+=2;break;}//|
      default : if((cmd[index-1]!='(')&&(cmd[index-1]!=')')) {buf[i][j]=a;j++;index++;break;}
                else {i++;j=0;buf[i][j]=a;j++;index++;break;}
    }
    return i;//i-lines
}

//run with parameters
void exepara(int st,int N){//N-number of paras.
  char para[10][10];
  int pos=st+2;
  for(int i=0;i<N;i++){
    strcpy(para[i],buf[pos]);
    pos+=2;
  }
  execlp(buf[st],buf[st],para,NULL);
  perror("error run with paras");
  exit(1);
}

int main(){
  collect();
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++)
      printf("%c",buf[i][j]);
    printf("\n");
  }
  exeparas(0,2);
  return 0;
}

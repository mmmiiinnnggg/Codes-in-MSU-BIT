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

void backRun(int st){/*position of &*/
  int pid,i,*status;
  if(0>(pid=fork())) {perror("error fork1");exit(1);}
  else if(pid) wait(status);//father
  else{//son
    if(0>(pid=fork())) {perror("error fork2");exit(1);}
    else if(pid) printf("child is going to finish");//son
    else{/*grandchild*/
      sleep(3);//grandchild wait for the finish of child and become background to run
      if(command[st-3]==1||command[st-3]==2||command[st-3]==5) execlp(buf[st-4],buf[st-4],NULL);//check changedir
      else execlp(buf[st-2],buf[st-2],NULL);
      perror("error exec");
      exit(1);
    }
  }
}

int main(){
  collect();
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++)
      printf("%c",buf[i][j]);
    printf("\n");
  }
  backRun(2);
  return 0;
}

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

void dir1(int st) // dir <
{
    int pid,fd,*status;
    if((pid=fork())==0){//son
      if(0>(fd=open(buf[st+2], O_RDWR, 0664))) {perror("open");exit(1);}
      dup2(fd,0); //dup2(oldfd, newfd);
      close(fd);
      execlp(buf[st],buf[st],NULL);
      perror("run right dir");
      exit(1);
    }
    wait(status);  //wait death of one son and recycle
}

void dir2(int st) // st=start of command dir >
{
    int pid,fd,*status;
    if((pid=fork())==0){//son
      if(0>(fd=open(buf[st+2], O_RDWR, 0664))) {perror("open");exit(1);}
      dup2(fd,1); //dup2(oldfd, newfd);
      close(fd);
      if(command[st-1]==5) {execlp(buf[st-2],buf[st-2],NULL);perror("run right dir");exit(1);}//pr1<data>res
      else {execlp(buf[st],buf[st],NULL);perror("run right dir");exit(1);}
    }
    wait(status);  //wait death of one son and recycle
}

void dir3(int st) // dir >>
{
    int pid,fd,*status;
    if((pid=fork())==0){//son
      if(0>(fd=open(buf[st+2], O_RDWR, 0664))) {perror("open");exit(1);}
      lseek(fd,0L,SEEK_END);
      dup2(fd,1); //dup2(oldfd, newfd);
      close(fd);
      execlp(buf[st],buf[st],NULL);
      perror("run right dir");
      exit(1);
    }
    wait(status);  //wait death of one son and recycle
}

int main(){
  collect();
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++)
      printf("%c",buf[i][j]);
    printf("\n");
  }
  //dir1(0);
  //dir2(0);
  dir3(0);
  return 0;
}

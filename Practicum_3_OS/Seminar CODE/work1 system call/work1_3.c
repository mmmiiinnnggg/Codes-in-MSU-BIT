#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define BUFSIZE 10

// 在文件f末尾添加f文件的内容
//Написать программу, приписывающую в конец файла f его содержимое.

int main(int argc,char **argv){
  int n_r,fd1,fd2;
  char buf[BUFSIZE];
  if(argc!=3) {perror("Error instruction input");exit(-1);}
  if(0>(fd1=open(argv[1],O_RDWR))) {perror("Error open f");exit(-1);}
  if(0>(fd2=open(argv[2],O_RDWR))) {perror("Error open f");exit(-1);}

  do{
    if(0>(n_r=read(fd1,buf,BUFSIZE))){perror("Error read from f to g");exit(-1);}
    if(n_r!=write(fd2,buf,n_r)){perror("Error write from f to g");exit(-1);}
  }while(n_r);
  
  if(0>(lseek(fd2,0L,0))) {perror("Error seek");exit(-1);}
  
  do{
    if(0>(n_r=read(fd2,buf,BUFSIZE))){perror("Error read from g to f");exit(-1);}
    if(n_r!=write(fd1,buf,n_r)){perror("Error write from g to f");exit(-1);}
  }while(n_r);

  close(fd1);
  close(fd2);
  return 0;
}
//finish

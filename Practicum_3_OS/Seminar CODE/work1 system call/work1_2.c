#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define BUFSIZE 10

// 在文件f末尾添加g文件的内容
//Программа. В конец файла f приписать содержимое файла g.

int main(int argc,char **argv){
  int n_r,fd1,fd2;
  char *filename1=argv[1];
  char *filename2=argv[2];
  char buf[BUFSIZE];
  if(argc!=3) {perror("Error instruction input");exit(-1);}
  if(0>(fd1=open(filename1,O_RDWR))) {perror("Error open f");exit(-1);}

  if(0>lseek(fd1,0L,SEEK_END)) {perror("Error seek f");exit(-1);}

  if(0>(fd2=open(filename2,O_RDONLY))) {perror("Error open g");exit(-1);}
  do{
    if(0>(n_r=read(fd2,buf,BUFSIZE))){perror("Error read from g to f");exit(-1);}
    if(n_r!=write(fd1,buf,n_r)){perror("Error write from g to f");exit(-1);}
  }while(n_r);
    close(fd1);
    close(fd2);
    return 0;
    }
//finish

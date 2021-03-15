#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define BUFSIZE 10
//写一个函数get，从文件f的pos位开始读n位 
//Описать функцию char *get (char *f, int n, int pos), читающую n байт из файла f, начиная с позиции pos.
char buf[BUFSIZE];

char *get(char *f,int n,int pos) 
{ 
  int fd;
  if(0>(fd=open(f,O_RDONLY))){perror("Error open\n");exit(-1);}
  if(0>lseek(fd,pos,0)) {perror("Error seek\n");exit(-1);}
  if(0>read(fd,buf,n)){perror("Error read\n");exit(-1);}
  return buf;
}

int main(int argc, char**argv){
  int fd,n_r,f;
  int pos=*argv[2]-'0';
  int n=*argv[3]-'0';
  if(argc!=4) {perror("Error instruction input");exit(-1);}	
  if(0>(fd=open(argv[1],O_RDONLY))) {perror("Error open f");exit(-1);}
  get(argv[1],n,pos);
  close(fd);
  puts(buf);
  return 0;
}
//finish

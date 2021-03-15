#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define SIZE 10
//在文件f末尾添加1234或者end
//Программа. В конец файла f приписать
//a)число 1234; b)строку “end”;

int main(int argc,char **argv){
  int fd,i=0;
  const char buf[SIZE]={'1','2','3','4'};//char buf[SIZE]={'e','n','d'};
  if(argc!=2) {perror("Error instruction input");exit(-1);}
  if(0>(fd=open(argv[1],O_RDWR))) {perror("Error open file");exit(-1);}
  while(buf[i]!='\0'){
    lseek(fd,0L,SEEK_END);
    if(1!=(write(fd,buf+i,1))){perror("Error write to file");exit(-1);}
    i++;
    }
  close(fd);
  return 0;
  }
//finish


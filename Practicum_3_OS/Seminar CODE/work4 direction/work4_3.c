#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

//cat f1>>f2
int main(){
  int fd1,fd2;
  if(0>(fd1=open("f1.txt",O_WRONLY|O_CREAT,0644))) {perror("open");exit(1);}
  if(0>(fd2=open("f2.txt",O_WRONLY|O_CREAT,0644))) {perror("open");exit(1);}
  lseek(fd2,0L,SEEK_END);
  dup2(fd2,1);
  close(fd2);
  execlp("cat","cat","f1.txt",NULL);
  perror("exec");
  return 0;
}

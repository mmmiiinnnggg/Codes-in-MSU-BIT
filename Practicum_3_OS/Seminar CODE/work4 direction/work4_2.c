#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

//ls>>f1
int main(){
  int fd;
  if(0>(fd=open("f1.txt",O_WRONLY|O_CREAT,0644))) {perror("open");exit(1);}
  lseek(fd,0L,SEEK_END);
  dup2(fd,1);
  close(fd);
  execlp("ls","ls",NULL);
  perror("exec");
  return 0;
}

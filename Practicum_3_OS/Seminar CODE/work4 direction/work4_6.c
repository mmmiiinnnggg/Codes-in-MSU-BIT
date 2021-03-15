#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

//ls -l -a>f1
int main(){
  int fd;
  if(0>(fd=open("f1.txt",O_WRONLY|O_CREAT,0644))) {perror("open");exit(1);}
  dup2(fd,1);
  close(fd);
  execlp("ls","ls","-l","-a",NULL);
  perror("exec");
  return 0;
}

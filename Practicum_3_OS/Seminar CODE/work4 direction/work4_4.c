#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

//wc -w f1>f2
int main(){
  int fd;
  if(0>(fd=open("f2.txt",O_WRONLY|O_CREAT,0644))) {perror("open");exit(1);}
  dup2(fd,1);
  close(fd);
  execlp("wc","wc","-w","f1.txt",NULL);
  perror("exec");
  return 0;
}

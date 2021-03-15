#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define SIZE 10

// 将几个文件的内容连接起来 ，放到新建的first中
//Программа. Создать файл, являющийся конкатенацией других файлов. Имена файлов задаются в командной строке . 
int main(int argc,char **argv){
  int i=3,n_r,fir,n,fd;
  char buf[SIZE];
  n=*argv[2]-'0';
  if(argc!=(n+3)){perror("error instruction input\n");exit(-1);}
  if(0>(fir=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0644))) {perror("error create first\n");exit(-1);}
  while(i<argc){
    if(0>(fd=open(argv[i],O_RDONLY))) {perror("error open file\n");exit(-1); }
    do{
      if(0>(n_r=read(fd,buf,SIZE))) {perror("error read file\n");exit(-1);}
      if(0>(n_r!=write(fir,buf,n_r))) {perror("error write file\n");exit(-1);}
    }while(n_r);

    close(fd);
    i++;
    }
   close(fir);
    return 0;
}
//finish

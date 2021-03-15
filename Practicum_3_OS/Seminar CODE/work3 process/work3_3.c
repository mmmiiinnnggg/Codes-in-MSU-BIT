#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#define SIZE 1
//Написать программу в которой два процесса параллельно выполняют:
//-родитель выводит сколько вхождений буквы ‘a’ в файле 
//-сын выводит сколько вхождений буквы ‘b’ в файле 
//	Имя файла задается в командной строке.


int main(int argc,char **argv){
  int pid,fd,counta=0,countb=0,n_r;
  char buf[SIZE];
  if(0>(fd=open(argv[1],O_RDONLY))) {perror("Error open file");exit(-1);}
  if((pid=fork())!=0){
    lseek(fd,0L,SEEK_SET);
    do{
      n_r=read(fd,buf,1);
      if(*buf=='a') counta++;
    }while(n_r);
    printf("There are %d 'a' in the file\n",counta);
  }
  else{
    lseek(fd,0L,SEEK_SET);
    do{
      n_r=read(fd,buf,1);
      if(*buf=='b') countb++;
    }while(n_r);
    printf("There are %d 'b' in the file\n",countb);
  }
  return 0;
}
//finish

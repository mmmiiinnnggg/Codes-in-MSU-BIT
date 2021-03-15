#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#define SIZE 10

//Программа. Содержимое файлов, длина которых меньше N байт, переписать в новый файл-результат и удалить такие файлы. Файлы, длина которых больше либо равна N байт, не изменяются и не удаляются. Имена файлов и величина N задаются в командной строке: fres f1  f2 …, где fres - имя файла-результата, f1, f2, … - файлы, содержимое которых должно быть проанализировано.

int main(int argc,char **argv){
  int n_r,fd,fir,i=3,count=0,seek;
  char buf[SIZE];
  int m=1000;
  char Counting[m];
  if(0>(fir=open(argv[1],O_CREAT|O_RDWR|O_TRUNC,0644))){perror("Error create file\n");exit(-1);}
  int N=*argv[2]-'0';//N<10

  while(argv[i]!=NULL){
    if(0>(fd=open(argv[i],O_RDWR))) {perror("error open file\n");exit(-1);}
    do{
      if(0>(n_r=read(fd,Counting,1))) {perror("error read file\n");exit(-1);}
      count++;
      }while(n_r);
    lseek(fd,0L,0);
    if(count<N){             
      do{
        if(0>(n_r=read(fd,buf,SIZE))) {perror("error read file\n");exit(-1);}
        if(0>(n_r!=write(fir,buf,n_r))) {perror("error write file\n");exit(-1);}
        }while(n_r);
      count=0;
      i++;
      //delete(fd);
      close(fd);
    }
    else{
      count=0;
      i++;
      close(fd);
    }
  }
  close(fir);
  return 0;
}
//finish

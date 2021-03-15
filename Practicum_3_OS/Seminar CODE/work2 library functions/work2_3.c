#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#define SIZE 1000
//Программа. Распечатать все строки данного файла, содержащие заданную строку в качестве подстроки. Имя файла и строка задаются в командной строке.

int main(int argc,char **argv){
  FILE *f1;
  char buf[SIZE],str[SIZE];
  int l2=strlen(argv[2]);//argv[2]-given subline
  int i,j;
  if(argc!=3) {perror("Error input instructions\n");exit(-1);}
  if((f1=fopen(argv[1],"r"))==NULL) exit(-1);//argv[1]-file
  while(fgets(str,SIZE,f1)!=NULL){//stop when meet '\n'
    int l=strlen(str);//length of a line in file
    for(i=0;i<l-l2+1;i++)
      if(str[i]==argv[2][0]){//if the first symbol equal
        int sign=1;
        for(j=1;j<l2;j++) if(str[i+j]!=argv[2][j]){sign=0;break;}
        if(sign){printf("%s",str);break;}
      }
  }
  fclose(f1);
  return 0;
}
//finish



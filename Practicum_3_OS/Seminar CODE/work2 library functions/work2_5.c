#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#define SIZE 100
//Программа. Определить, какая строка является самой длинной в заданном файле. Если таких строк несколько, то в качестве результата выдать первую из них. Имя файла задается в командной строке.

int main(int argc,char **argv){
  FILE *f1;
  char str[SIZE],big[SIZE];
  int i,k,l,lmax;
  if(argc!=2) {perror("Error input instructions\n");exit(-1);}
  if((f1=fopen(argv[1],"r"))==NULL) exit(-1);//argv[1]-file
  //the first line
  fgets(str,SIZE,f1);
  lmax=strlen(str);
  for(k=0;k<lmax;k++) big[k]=str[k];

  while(fgets(str,SIZE,f1)!=NULL){
    l=strlen(str);
    if(l>lmax){
      lmax=l;
      for(k=0;k<lmax;k++) big[k]=str[k];
    }
  }
  printf("%s",big);
  fclose(f1);
  return 0;
}
//finish


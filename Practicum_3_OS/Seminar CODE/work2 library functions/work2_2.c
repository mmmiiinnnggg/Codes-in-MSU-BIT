#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#define SIZE 1000
//Программа. Определить, сколько раз в данном файле g встречается строка UNIX.
int main(){
  FILE *f1;
  int count=0,i;
  char str[1000];
  char a;
  if((f1=fopen("unix.txt","r"))==NULL) exit(-1); 
  while((fgets(str,SIZE,f1))!=NULL){
    int l=strlen(str);
    for(i=0;i<l;i++)
      if(str[i]=='U'&&str[i+1]=='N'&&str[i+2]=='I'&&str[i+3]=='X') count++;
  }
  printf("'UNIX' has shown in file for %d times",count);
  fclose(f1);
  return 0;
}
//finish


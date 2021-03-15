#include<stdio.h>
#include<stdlib.h>

//Программа. Определить, сколько раз в данном файле f встречается символ ‘A’.
int main(){
  FILE *f1;
  char a;
  int i=0,count=0;
  if((f1=fopen("f.txt","r"))==NULL) exit(1); 
  while((a=fgetc(f1))!=EOF){ 
   if(a=='A') count++;
  }
  fclose(f1);
  printf("%d",count);
  return 0;
}
//finish


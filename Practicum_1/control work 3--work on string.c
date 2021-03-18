#include <stdio.h>
#include <stdlib.h>
#define N 100
#include <string.h> 

int check(char *str)
{
    int i=0;
    while(str[i])
    {
      if((str[i]==' ')&&(str[i+1]==' '))
        {
          printf("String Error");
          return 0;
        }
      if((str[i]<'a')||(str[i+1]>'z'))
        {
          printf("String Error");
          return 0;
        }
      i++;      
    }
    
    printf("String is OK");
    return 1;
}


int select(char *str,char *words[])
{
    int i=1;
    if(*str==' ')
      words[0]=++str;
    else words[0]=str;

      }
    while(*str)
    {
      if(*str==' ')
      {
        *str='\0';
        words[i]=++str;
        i++;
      }
      str++;
    }
    return i;
}


int compare(char *w1,char *w2)
{
    while(*w1&&*w2&&(*w1==*w2)&&(*w1!=' ')&&(*w2!=' ')) w1++,w2++;
    return *w1-*w2;
}

int count(char *words[],int nw,int wnum[])
{
    int i,j;
    for(i=0;i<nw;i++)
      for(j=0;j<nw;j++)
        if(compare(words[i]),words[j])==0)
          wnum[i]++;
    return 0;
}

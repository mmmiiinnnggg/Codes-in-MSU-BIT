
#include <stdio.h>
#include <stdlib.h>
#define N 1000



int compare(char*s,char*a)
{
   while( *s && *a!=' '&& *a && *s==*a )
   {
       s++,a++;
   }
   if(*a==' '&&*s=='\0')
       return 0;
   return *s-*a;
}

int find_words(char*s,char*a)
{
   int count=0,count1=1;
   char*beg=a;
   if(*a!='\0'&&*a!=' ')
   {
       if(compare(s,beg)==0)
           count++;


       if(count==1)
           printf("%d\n",count1);
   }

   while(*a!='\0')
   {

       if(*a==' ')
       {

           count1++;
           beg=a+1;
           if(compare(s,beg)==0)
           {
               count++;


               if(count==1)
                   printf("%d\n",count1);
           }

       }

       a++;
   }
   return count;
}

int main()
{
   char a[N];
   char s[]="abc";
   int m;
   printf("input the article:\n");
   gets(a);
   m=find_words(s,a);
   printf("%d",m);
   return 0;
}


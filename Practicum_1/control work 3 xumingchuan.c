#include <stdio.h>
#include <stdlib.h>
#define N 100
#include <string.h> 

int check(char *str)
{
    int judge1=0;
    int judge2=0;
    int i=0,j=0;
    char c1='a';
    char c2='z';
    char c3='\0';
    char c4=' ';
    while( (c1<=str[i]) && (str[i]<=c2) && (str[i]!=c3) )
    {
        i++;
        judge1=str[i];
    }
    while( (str[j]==c4) || (str[j+1]==c4) || (str[j]!=c3) )
    {
        j++;
        judge2=str[j];
    }
    if((judge1==0) && (judge2==0))
    {
        printf("StringisOK!");
        return 1;
    }
    else
    {
        printf("StringError!");
        return 0;
    }
}

int select(char *str,char *words[])
{
	int i=0,len=0,j=0;
	char tmp[100];
    while(str[i]!='\0')
    {
    	if(str[i]!=' ')
    	{
    		tmp[len]=str[i];
    		len++;
    	}
		    
    	else
    	{
    		*(tmp+len)='\0';
    		words[j]=(char*)malloc(len*sizeof(char));
    		strcpy(words[j],tmp);
    		len=0;
    		j++;
    	}
        i++;
    }
    
    if(len>0)
    {
    	*(tmp+len)='\0';
    	words[j]=(char*)malloc(len*sizeof(char));
    	strcpy(words[j],tmp);
    	len=0;
    	j++;
    }
    
    return j;
}


int compare(char *w1,char *w2)
{
    while(*w1&&*w2&&(*w1==*w2)) w1++,w2++;
    return *w1-*w2;
}

int count(char *words[],int nw,int wnum[])
{
    int i,j,k;
    for(i=0;i<nw;i++)
    {
    	for(j=0;j<nw;j++)
        if(compare(words[i],words[j])==0) 
		    wnum[i]++;
		printf("%s",words[i]);
		printf(":%d",wnum[i]);
		printf("\n");
    }
    return 0;
}

int main()
{
    
	printf("Please type in a string:\n");
    char str[N];
    scanf("%s",str);
    //test function 1
    check(str);
    
    //test function 2
    int j;
    char *words[N];
    j=select(str,words[N]);
    
    //test function 3 
    char *w1;
    char *w2;
    printf("Please type in two strings to compare:\n");
    scanf("%s",w1);
    scanf("%s",w2);
    if((compare(w1,w2)>0)) printf("w1 is bigger than w2");
    if((compare(w1,w2)<0)) printf("w2 is bigger than w1");
    if((compare(w1,w2)==0)) printf("w1 is equal to w2");
    
    //test function 4
    int nw,wnum[N];
    count(words[j],nw,wnum[j]);
    

    return 0;
}

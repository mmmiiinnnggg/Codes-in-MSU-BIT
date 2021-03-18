#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10000


// function of work 27
void changetobig(char str[])
{
	int i=0;
	while(str[i]!='\0')
	{
		if('a'<=str[i] && str[i]<='z')
		{
			str[i]-=('a'-'A');
		}
		i++;
	} 
} 

//function of work 32

void putinwords(char str[],char *words[],int m)
{
	int i,j;
    //for(i=0;i<m;i++)
    //{
    	scanf("%s",str);
		/*
		j=0;
		while((str[j]!=' ')&&str[j]!='\0')
		  j++;
		if(str[j]=='\0') break;  
    	words[i]=(char*)malloc((j)*sizeof(char));
    	strncpy(words[i],str,j);
    	str=str+j+1;
    	*/
    while(*str)
    {
      if(*str==' ')
      {
        *str='\0';
        words[i]=++str;
        i++;
      }
      str++;
   // }
}

void sortstring(char **words,int m)//32
{
	int i,j;
    char c[N];
	for(i=1;i<m;i++)
	for(j=m-1;j>=i;j--)
	      {
	      	 	if(strcmp(words[j-1],words[j])>0)
	      	 	{
	      	  		strcpy(c,words[j-1]);
                    strcpy(words[j-1],words[j]);
                    strcpy(words[j],c);
					//tmp=words[j-1];
	    	  		//words[j-1]=words[j];
	    	  		//words[j]=tmp;
	   			}
	      }   
}

int main()
{
	int i,m;
	char str[N];
	
	
	printf("Please type in a string:\n");
	gets(str);
	printf("Please in the number of text:\n");
	scanf("%d",&m);
	char *words[m];
	
	//changetobig(str);
	//puts(str);
	
	putinwords(str,words,m);
	sortstring(*words[m],m);
	for(i=0;i<m;i++)
	  printf("%s",words[i]);
	  
	//for(i=0;i<m;i++)
	  //free(words[i]);
	  
	return 0;	
}

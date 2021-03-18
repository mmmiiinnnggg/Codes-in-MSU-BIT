//xumingchuan 2 1120170019 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NM 15
#define LM 10

struct Tlink
{
	int value;
	struct Tlink *pnext;
};

struct TLink *AddFirst (struct TLink *pHead, int Val) 
{ 
    struct Tlink* pt;
    if(pt=(struct Tlink*)malloc(sizeof(struct Tlink)))
    {
        pt->pnext=pHead;
        pt->value=Val;
        pHead=pt;
        return pHead;
    }
    printf("error\n");
    exit(-1);
} 

int main()
{
	//work 1
	int n,i,j,k;
	printf("Numbers of words:");
	scanf("%d",&n);
	char words[NM][LM];
	for(i=0;i<n;i++)
	{
		printf("Word %d:",i);
		scanf("%s",words[i]);
	}
	printf("\n");
	
	//work 2
	printf("Word length - ");
	int length[n];
	for(i=0;i<n;i++)
	{
		j=0,k=0;
		while(words[i][j]!=0)
		  j++;
		length[i]=j;
		while(k<j)
		{
			printf("%c",words[i][k]);
			k++;
		}
		
		printf(":%d ",j);
	}
	printf("\n");
	
	//work 3
	printf("The longest word: ");
	int lengthmax=length[0];
	int ilengthmax;
	for(i=1;i<n;i++)
	{
	  if(length[i]>lengthmax)
	  {
	  	lengthmax=length[i];
	    ilengthmax=i;
	  }  
	} 
	k=0;
	while(k<length[ilengthmax])
	{
		printf("%c",words[ilengthmax][k]);
		k++;
	}
	printf("\n");
		
	//work 4
	printf("Total number of symbols: ");
	int sumnumber=0;
	for(i=0;i<n;i++)
        sumnumber+=length[i];
    printf("%d\n",sumnumber);
    
    //work 5
    printf("Selected words - ");
    int lengtha[n];
    int x=0;
    int judge;
    for(i=0;i<n;i++)
    {
    	judge=0;
		for(j=0;j<length[i];j++)
		{
			while(words[i][j]=='a')
		    {
		    	lengtha[x++]=i;
				printf("%d:",i);
				k=0;
		    	while(k<length[i])
	            {
					printf("%c",words[i][k]);
		            k++;
		        }
			    printf(" ");
			    judge=1;
				break;
		    }
			if(judge==1) break;
		}
    }

	printf("\n");
	
	//work 6
	printf("List of word lengths: ");
    struct Tlink *p=NULL,*pl;
    int m;
 
    for(i=0; i<x; i++)
    {
        m=length[lengtha[i]];
        p=AddFirst(p,m);
    }
    pl=p;
    while(pl)
    {
        printf("%d ",pl->value);
        pl=pl->pnext;
    }
    
    printf("\n");

	//work 7
	printf("Total length: ");
	struct Tlink *pm;
	pm=p;
	int suma=0;
	while(pm)
	{
		suma+=pm->value;
		pm=pm->pnext;
	}
	printf("%d",suma);
	
	return 0;
} 

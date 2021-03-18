#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10000
#define M 100


// function of work 27
void changetobig(char str[][N],int n)
{
    int i=0;
    int j=0;
    char str2[M][N];
    for(i=0; i<n; i++)
    {
        for(j=0; str[i][j]!='\0'; j++)
            str2[i][j]=str[i][j];
    }
    for(i=0; i<n; i++)
    {
        for(j=0; str2[i][j]!='\0'; j++)
        while(str2[i][j]!='\0')
        {
            if('a'<=str2[i][j] && str2[i][j]<='z')
            {
                str2[i][j]-=('a'-'A');
            }
            j++;
        }
    }
    printf("%s",str2[0]);
    for(i=1; i<n; i++)
    {
        printf(" %s",str2[i]);
    }
    printf("\n");
}

void putinwords(char b[][N],int n)
{
    int i,j;
    char c[N];
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(strcmp(b[j],b[i])<0)
            {
                strcpy(c,b[i]);
                strcpy(b[i],b[j]);
                strcpy(b[j],c);
            }
        }
    }
    for( i=0; i<n; i++)
        printf("%s\n",b[i]);
}
int main()
{
    int i=0;
    char words[M][N];
    printf("Please type in a string:\n");
    while(scanf("%s",words[i]))
    {
        i++;
        if(getchar()=='\n')
            break;
    }
    changetobig(words,i);
    putinwords(words,i);
    return 0;
}

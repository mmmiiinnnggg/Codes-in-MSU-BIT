#include<stdio.h>
#include<stdlib.h>
#define maxn 1000
int strcmp(char *w1,char *w2){
	int i=0;
	while (*(w1+i) && *(w2+i) && *(w1+i)==*(w2+i)) i++;
	return *w1-*w2;
} 
int getword(char *str,char *words[]){
	int i=0,j=0,m=0;
	words[j]=(char*)malloc(maxn*sizeof(char));
	while (str[i]!='\0')
	{
		if (str[i]!=' ')
		{
			words[j][m]=str[i];
			m++;i++;
		}
		else if (str[i]==' ')
		{
			words[j][m]='\0';
			j++;
			words[j]=(char*)malloc(maxn*sizeof(char));
			m=0;i++;
		}
	}
	words[j][m]='\0';
	j++;
	return j;
}
void xiaoxie(char *s){
	int i=0;
	while (s[i]!='\0')
	{
		if (s[i]>='A' && s[i]<='Z') s[i]=s[i]-'A'+'a';
		i++;
	}
}
int main(){
	char *key,*str,*words[10];
	int i,n,count=0,local,ind=0; 
	key=(char*)malloc(maxn*sizeof(char));
	str=(char*)malloc(maxn*sizeof(char));
	scanf("%s",key);
	i=0;
	getline
	//getchar();
	//gets(str);
	xiaoxie(key);
	xiaoxie(str);
	printf("%s\n%s\n",key,str);
	n=getword(str,words);
	printf("%d\n",n);
	for (i=0;i<n;i++) printf("%s\n",words[i]);
	for (i=0;i<n;i++) 
	{
		if (strcmp(key,words[i])==0)
		{
			if (ind==0) {ind=1;local=i;}
			count++;
		}
	}
	if (ind==1) printf("%d %d",count,local);
	else printf("-1");
	for (i=0;i<n;i++) free(words[i]);
	free(key);
	free(str);
	return 0;
}


#include<stdio.h>
#define N 100
#include<time.h>
int countop=0;

int cmp2elem(int elem1,int elem2)
{
	countop++;
	if(elem1<elem2) return 1;
	else return 0; 
}

void simple_sort_insert(int X[],int n)
{
	int tmp,i,j;
	for(i=0;i<n;i++)
	{
	  tmp=X[i];
	  for(j=i-1;(j>=0)&&(cmp2elem(tmp,X[j])==1);j--)
	    {
	      X[j+1]=X[j];	
	      countop++;
	    }
	  X[j+1]=tmp;
	}	
}

int main()
{
	int a[4][7],n[4]={10,20,50,100},i;
	int p,q,k;
	srand(time(NULL));

//////////////////////////////////////////////////////////////
/////////// Generate the 5 needed matrixs ////////////////////
	  
for(k=0;k<4;k++)
{
	int ntmp=n[k],j,sum=0;
	int X[ntmp];
	int first[ntmp],second[ntmp],third[ntmp],forth[ntmp],fifth[ntmp];
	for(i=0;i<ntmp;i++)
	  first[i]=i;//1st sequence
	for(i=0;i<ntmp;i++)
	  second[i]=first[ntmp-1-i];//2nd sequence
	for(i=0;2*i<ntmp;i++)
	  third[2*i]=first[2*i];
	for(i=0;2*i+1<ntmp;i++)
	  third[2*i+1]=second[2*i];//3rd sequence
	for(i=0;i<ntmp;i++)
	  forth[i]=rand()%100;//4th sequence
	for(i=0;i<ntmp;i++)
	  fifth[i]=rand()%100;//5th sequence
	  
//////////////////////////////////////////////////////////////
/////////// Print out the 5 matrixs ////////////////////
	  
	printf("The 5 matrixs below when n=%d",n[k]);
	printf("\n");
	for(i=0;i<ntmp;i++)
	  printf("%d ",first[i]);
	printf("\n");
	for(i=0;i<ntmp;i++)
	  printf("%d ",second[i]);
	printf("\n");
	for(i=0;i<ntmp;i++)
	  printf("%d ",third[i]);
	printf("\n");
	for(i=0;i<ntmp;i++)
	  printf("%d ",forth[i]);
	printf("\n");
	for(i=0;i<ntmp;i++)
	  printf("%d ",fifth[i]);
	printf("\n");
	printf("\n");
	
///////////////////////////////////////////////////////////////
/////////// The simple sort //////////////////////////////////
	
	a[k][0]=ntmp;//THE NUMBER OF MATRIX
	
	for(i=0;i<ntmp;i++)
	  X[i]=first[i];
	simple_sort_insert(X,ntmp);
	a[k][1]=countop;
	countop=0;
	
	for(i=0;i<ntmp;i++)
	  X[i]=second[i];
	simple_sort_insert(X,ntmp);
	a[k][2]=countop;
	countop=0;
	
	for(i=0;i<ntmp;i++)
	  X[i]=third[i];
	simple_sort_insert(X,ntmp);
	a[k][3]=countop;
	countop=0;
	
	for(i=0;i<ntmp;i++)
	  X[i]=forth[i];
	simple_sort_insert(X,ntmp);
    a[k][4]=countop;
    countop=0;

    for(i=0;i<ntmp;i++)
	  X[i]=fifth[i];
	simple_sort_insert(X,ntmp);
    a[k][5]=countop;
    countop=0;  
    
    for(j=1;j<6;j++)
      sum=sum+a[k][j];
    a[k][6]=sum/5;//CALCULATE THE AVERAGE NUMBER
}

//////////////////////////////////////////////////////////////
/////////// Print out the Table ////////////////////////////

printf("Table:\n");
printf("n    1     2     3     4    5    average\n");
for(p=0;p<4;p++)
{
	for(q=0;q<7;q++)
      printf("%d   ",a[p][q]);
    printf("\n");
}
  
	return 0;
}


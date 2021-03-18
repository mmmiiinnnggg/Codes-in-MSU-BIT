//Code by Xumingchuan from group 2

//matrix dimensions take from 20 to 4860, with 3 times proportion between dimensions
//Update proportion - 20%


#include <stdio.h>
#include <stdlib.h>

//different dimensions of matrix
#define nDim 20//60、180、540、1620、4860 

int Arr[nDim];

//initialization 
void RndArr(){
  for(int i=0;i<nDim;i++)
    Arr[i]=rand()%1000;
}

//Update 20percent data front
void RndArrFront(){
	int nDimFront=nDim/5;
	for(int i=0;i<nDimFront;i++)
	  Arr[i]=rand()%1000;
}

//Update 20percent data end
void RndArrEnd(){
	int nDimEnd=nDim-nDim/5;
	for(int i=nDimEnd;i<nDim;i++)
	  Arr[i]=rand()%1000;
}

void PrintArr(){
  for(int i=0;i<nDim;i++)
    printf("%d ",Arr[i]);
}

int nCount;

void Exchange(int i,int j){
  int Tmp=Arr[i];
  Arr[i]=Arr[j];
  Arr[j]=Tmp;
  nCount += 3;
}

//move 1 position towards the back
void shift(int i,int j){
  int Tmp=Arr[j];
  if(j>i) for(int k=j;k>=i+1;k--) Arr[k]=Arr[k-1];
  else    for(int k=j;k<=i-1;k++) Arr[k]=Arr[k+1];
  Arr[i]=Tmp;
  nCount+= abs(i-j)+2;
}

//find the first number which bigger than key 
int LinSearch(int key,int iMax){
  for(int i=0;i<=iMax;i++)
    if(Arr[i]>=key)
      return i; 
  return -1;
}

void SortingDirectInclude(){
  for(int i=1;i<nDim;i++){
    int j=LinSearch(Arr[i],i-1);
    if(j>=0) shift(j,i);
  }
}

void UpdateFront(){
  printf("Update 20percent data front:\n");
  RndArrFront();
  PrintArr();
  nCount=0;
  SortingDirectInclude();
  printf("\nAfter Direct Include with 20percent new data front:\n");
  PrintArr();
  printf("\n");
  printf("nCount=%d",nCount);
  printf("\n");
  printf("\n");
}

void UpdateEnd(){
  printf("Update 20percent data end:\n");
  RndArrEnd();
  PrintArr();
  nCount=0;
  SortingDirectInclude();
  printf("\nAfter Direct Include with 10percent new data End:\n");
  PrintArr();
  printf("\n");
  printf("nCount=%d",nCount);
  printf("\n");
}


int main()
{
  printf("nDim=%d\n",nDim);
  RndArr();
  printf("The original sequence:\n");
  PrintArr();
  nCount=0;
  SortingDirectInclude();
  printf("\nAfter Direct Include:\n");
  PrintArr();
  printf("\n");
  printf("nCount=%d",nCount);
  printf("\n");
  printf("\n");
 
  char Judge;
  printf("Type in F for UpdateFront\n");
  printf("Type in E for UpdateEnd\n");
  scanf("%c",&Judge);
  if(Judge=='F')
    UpdateFront();
  else if(Judge=='E')
    UpdateEnd();
  
  return 0;
}


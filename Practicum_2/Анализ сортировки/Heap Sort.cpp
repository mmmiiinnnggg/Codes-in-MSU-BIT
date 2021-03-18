#include<stdio.h>
#include<stdlib.h>

//From Arr[0] start storing numbers
#define nDim 800

int nCount;
int Arr[nDim];

//initialization 
void RndArr(){
  for(int i=0;i<nDim;i++)
    Arr[i]=rand()%1000;
}

//Update 10percent data front
void RndArrFront(){
	int nDimFront=nDim/10;
	for(int i=0;i<nDimFront;i++)
	  Arr[i]=rand()%1000;
}

//Update 10percent data end
void RndArrEnd(){
	int nDimEnd=nDim-nDim/10;
	for(int i=nDimEnd;i<nDim;i++)
	  Arr[i]=rand()%1000;
}

void Exchange(int i,int j){
  int tmp=Arr[i];
  Arr[i]=Arr[j];
  Arr[j]=tmp;
  nCount += 3;
}

void PrintArr(){
    for(int i=0;i<nDim;i++)
        printf("%d ",Arr[i]);
}

int FindBiggerChild(int Child,int Dim){
	//if left and right child exist
	if(Child+1<Dim && Arr[Child+1]>Arr[Child]) Child++;
	return Child;
}

//sink the element to corresponding position 
void Sink(int i,int Dim){
    int LeftChild,BiggerChild;
    //if left child exists 
    while(2*i+1<Dim){
        LeftChild = 2*i+1; 
        //find the biggest child of node
        BiggerChild=FindBiggerChild(LeftChild,Dim);
        //if node bigger than child, then position don't exchange  
        if (Arr[i] > Arr[BiggerChild]) break;
        // if the biggest child bigger than node, then exchange the position
		Exchange(i,BiggerChild);
		//make BiggerChile become new node
		i=BiggerChild;
    }
}

void HeapSort(){ 
    for (int i=nDim/2;i>=0;i--)
	    Sink(i,nDim);    //build heap:start from Arr[1]
	int Dim=nDim;
    while(Dim>1){
        //exchange the head and last element 
		Exchange(0,Dim-1);
		//decrease size of Arr and leave sorted element behind
		Dim-=1;
        Sink(0,Dim-1);
    }
}

void UpdateFront(){
  printf("Update 10percent data front:\n");
  RndArrFront();
  PrintArr();
  nCount=0;
  HeapSort();
  printf("\nAfter Heap Sort with 10percent new data front:\n");
  PrintArr();
  printf("\n");
  printf("nCount=%d",nCount);
  printf("\n");
  printf("\n");
}

void UpdateEnd(){
  printf("Update 10percent data end:\n");
  RndArrEnd();
  PrintArr();
  nCount=0;
  HeapSort();
  printf("\nAfter Heap Sort with 10percent new data End:\n");
  PrintArr();
  printf("\n");
  printf("nCount=%d",nCount);
  printf("\n");
}


int main(){
	printf("nDim=%d\n",nDim);
    RndArr();
    printf("The original sequense:\n");
	PrintArr();
    printf("\n");
    HeapSort();
    printf("After Heap sort:\n");
    PrintArr();
    printf("\n");
    printf("nCount=%d",nCount);
    printf("\n");
    printf("\n");
    
    char Judge;
    printf("Type in F for UpdateFront\n");
    printf("Type in E for UpdateEnd\n");
    scanf("%c",&Judge);
    printf("\n");
    
    if(Judge=='F')
      UpdateFront();
    else if(Judge=='E')
      UpdateEnd();
    
    return 0;
}

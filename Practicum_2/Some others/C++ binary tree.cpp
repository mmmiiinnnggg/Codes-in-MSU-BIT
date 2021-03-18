#include <iostream>

using namespace std;

class BTree{
public:
bool Empty;
int A;
BTree* Left;
BTree* Right;

BTree(){Empty=true;}//methods
bool Add(int AAA);
int Depth();

void Print(int,int);//parameter version
bool YesSearch(int,int);

//void Print(int Space,int SpaceR);//parameter version
//bool YesSearch(int Min,int Max);

void Infix();//interface
void Prefix();
void Postfix();
};

bool BTree::Add(int AAA){
if(Empty){
  Empty=false;
  A=AAA;
  Left=new BTree;
  Right=new BTree;
  return true;
}

if(AAA=A) return false;
if(AAA<A) return Left->Add(AAA);
return Right->Add(AAA);
}

int BTree::Depth(){
if(Empty) return -1;
return 1+max(Left->Depth(),Right->Depth());
}

void BTree::Print(int Space,int SpaceR){
if(Empty) return;
for(int i=0;i<Space;i++) cout<<" ";
cout<<A<<" ";
Left->Print(0,SpaceR+3);
if(Left->Empty) cout<<endl;
Right->Print(SpaceR,SpaceR+3);
}

bool BTree::YesSearch(int Min,int Max){
if(Empty) return true;
if(A<Min||A>Max) return false;
return Left->YesSearch(Min,A-1)&&Right->YesSearch(A+1,Max);
}

void BTree::Infix(){
if(Empty) return;
cout<<A<<" ";
Left->Infix();
Right->Infix();
}

void BTree::Prefix(){
if(Empty) return;
Left->Prefix();
cout<<A<<" ";
Right->Prefix();
}

void BTree::Postfix(){
if(Empty) return;
Left->Postfix();
Right->Postfix();
cout<<A<<" ";
}


int main()
{
    cout<<"Hello World!"<<endl;
    BTree* BT=new BTree;
    cout<<"depth: "<<BT->Depth()<<endl;

    BT->Add(69);
    BT->Add(49);
    BT->Add(97);
    BT->Add(47);
    BT->Add(58);
    BT->Add(82);
    BT->Add(99);
    BT->Add(35);
    BT->Add(52);
    BT->Add(67);
    BT->Add(76);
    BT->Add(19);
    BT->Add(45);
    BT->Add(62);

    cout<<"depth: "<<BT->Depth()<<endl;
    BT->Print(0,3);
    if(BT->YesSearch(10,99)) cout<<"search tree ok"<<endl;
    cout<<"infix: ";BT->Infix();cout<<endl;
    cout<<"prefix: ";BT->Prefix();cout<<endl;
    cout<<"Postfix: ";BT->Postfix();cout<<endl;
    return 0;
}


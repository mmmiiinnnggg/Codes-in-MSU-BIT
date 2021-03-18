#include <iostream>

using namespace std;

class List{
public:
  bool Empty;
  int A;
  List* Next;

  List(){Empty=true;}
  void AddTail (int El);
  int Length();
  void Print();
  };

  void List::AddTail (int El){
  if(!Empty) Next->AddTail(El);
  else{
     Empty=false;
     A=El;
     Next= new List;
     Next->Empty =true;
     }
  }

  int List::Length(){
  if(Empty) return 0;
  return 1+Next->Length();
  }

  void List::Print(){
  if(Empty){
     cout<<"***";
     return;
     }
     cout << A << " ";
     Next->Print();
  }

  void Var01 (List*L, List* L1, List* L2){
  if(L->Empty) return;
  int A=L->A;
  if(A>0) L1->AddTail(A);
    else L2->AddTail(A);
  Var01(L->Next,L1,L2);
  }

  void Var02 (List* L,int E, int El){
  if(E==El) return;
  if(L->Empty) return;
  if(L->A==E){
    List* Ltmp=L->Next;
    L->Next=new List;
    L->Next->Empty=false;
    L->Next->A =El;
    L->Next->Next =Ltmp;
    }
    Var02(L->Next,E,El);
    }

    void Var03(List* L,int E,int El){
    	if(E==El) return;
    	
    	if(L->Empty) return;
    	if(L->A==E){
    		List* Lnew=new List;
    		Lnew->Empty=false;
    		Lnew->Next=L->Next;
    		Lnew->A=E;
    		L->Next=Lnew;
    		L->A=El;
    		L=L->Next;
    	}
    	Val03(L->Next,E,El);
    	
    }

int main()
{
    List* LLL=new List;
    LLL->AddTail(2);
    LLL->AddTail(3);
    LLL->AddTail(-3);
    LLL->AddTail(4);
    LLL->AddTail(5);
    LLL->AddTail(-5);
    LLL->AddTail(6);
    LLL->AddTail(7);
    LLL->AddTail(-7);
    List* LLL1= new List;
    List* LLL2= new List;

    Var01(LLL,LLL1,LLL2);
    LLL->Print(); cout << endl;
    LLL1->Print(); cout<<endl;
    LLL2->Print(); cout<<endl;
    return 0;
}


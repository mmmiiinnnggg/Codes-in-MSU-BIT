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




int main()
{
    List* LL=new List;
    cout<<"List's length in the beginning: "<<LL->Length() <<endl;
    LL->AddTail(2);
    LL->AddTail(3);
    cout<<"List's length adding 2 elements: "<<LL->Length() <<endl;
    return 0;
}


#include <iostream>

using namespace std;

class Error{
    string str;
public:
    Error(string l="Unknown Error"){
        str=l;
    }
    void Watch(){
        cout<<str;
    }
};

template<class T,int max_size>
class Stack: public Error{
    T s[max_size];
    int top;
public:
    Stack(){top=0;}//constructor
    void reset(){top=0;}//reset the stack
    void push(T i);
    T pop();
    int Size(){return top;}//return size of current stack
    T peek(){return s[top];}//return the top element
    bool Empty(){return top==0;}
    bool Full(){return top==max_size;}
    void Print();
};

template<class T,int max_size>
void Stack<T,max_size>::push(T i){
    if(!Full()){
        s[top]=i;
        top++;
    }
    else throw "stack_is_full";
}

template<class T,int max_size>
T Stack<T,max_size>::pop(){
    if(!Empty()){
        top--;
        //cout<<top<<endl;
        return s[top];
    }
    else throw "stack_is_empty";
}

template<class T,int max_size>
void Stack<T,max_size>::Print(){
    for(int i=0;i<top;i++)
        cout<<s[i]<<" ";
    cout<<endl;
}

int main(){
    Stack<int,10> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    s1.push(6);
    s1.push(7);
    s1.push(8);
    s1.push(9);
    s1.push(10);
    s1.Print();
    cout<<s1.pop()<<endl;
    cout<<s1.pop()<<endl;
    cout<<s1.pop()<<endl;
    s1.Print();
    return 0;
}

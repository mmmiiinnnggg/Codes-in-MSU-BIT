#include <iostream>
#include <cstdlib>
using namespace std;

class T{
public:
    int a;
    T(){ a = 0;}
};

class sp{
    T *p;
    int *pc;
public:
    sp(){
        p = new T;
        pc = new int(1);
    }

    ~sp(){
        if (*pc > 1)(*pc)--;
        else{
            delete p;
            delete pc;
        }
    }

    sp(const sp& x){//copy
        this -> p = x.p;
        (*x.pc)++;
        this -> pc = x.pc;
    }

    sp & operator = (const sp& y){//give value
        if (this == &y) return *this;
        (*pc)--;
        if (*pc == 0) delete p;
        p = y.p;
        pc = y.pc;
        (*pc)++;
        return *this;
    }

    T* operator -> (){ return p;}

};

int main()
{
    sp pp1, pp2, pp3(pp2);
    pp1 -> a = 2;
    cout << pp1 -> a << endl;
    cout << pp2 -> a << endl;
    cout << pp3 -> a << endl;

    pp2 = pp1;
    pp1 = pp3;
    pp2 = pp1;
    cout << pp2 -> a << endl;

    return 0;
}


#include <iostream>
#include <string>
using namespace std;

class Computer
{
    string brand;
    string model;
    int price;

protected:
    void print_info()const
    {
        cout << "Brand: " << brand << endl << "model: " << model << endl<< "Price: " << price <<endl;
    }
public:
    static int Count;
    Computer (string brand, string model, int price)
    {
        this->brand=brand;
        this->model=model;
        this->price=price;
        Count++;
    }

    virtual ~Computer() {Count--;}
    virtual void print()const =0;
};

class Apple : public virtual Computer
{
public:
    Apple(string brand="Apple", string model="Macbook", int price=9999): Computer(brand,model,price) {};

    ~Apple() {}

    void print()const {
    print_info();
    cout<<"Latest version of macOS: Catalina 10.15.1"<<endl;
    cout<<"Designed by Apple in California"<<endl;
    cout<<"Assembled in China"<<endl;
    }
};


class Dell : public virtual Computer
{
public:
    Dell(string brand="Dell", string model="Latitude", int price=7999): Computer(brand,model,price) {};
    virtual void print()const {
    print_info();
    cout<<"Latest version of Windows: Windows 10"<<endl;
    cout<<"Microsoft Office: Activated"<<endl;
    }
};

class Low_Apple: public Apple
{
public:
    Low_Apple(string brand="Apple", string model="Macbook Air", int price=7999):
        Apple(brand,model,price),Computer(brand,model,price) {};
    virtual void print()const {
        Apple::print();
        cout<<"CPU: Intel Core i5"<<endl;
        cout<<"RAM : 4GB LPDDR4 2133MHz"<<endl;
        cout<<"Memory: 256GB PCle"<<endl;
    }
};

class High_Apple: public Apple
{
public:
    High_Apple(string brand="Apple", string model="Macbook Pro", int price=18999):
        Apple(brand,model,price),Computer(brand,model,price){};
    virtual void print()const {
        Apple::print();
        cout<<"CPU: Intel Core i9"<<endl;
        cout<<"RAM : 16GB LPDDR4 2133MHz"<<endl;
        cout<<"Memory: 1TB PCle"<<endl;
    }
};

class Low_Dell: public Dell
{
public:
    Low_Dell(string brand="Dell", string model="Inspiron", int price=6999):
        Dell(brand,model,price),Computer(brand,model,price){};
    virtual void print()const {
        Dell::print();
        cout<<"CPU: Intel Core i5-5200U"<<endl;
        cout<<"RAM : 4GB LPDDR3 2133MHz"<<endl;
        cout<<"Memory: 256GB SDDR"<<endl;
    }
};

class High_Dell: public Dell
{
public:
    High_Dell(string brand="Dell", string model="XPS 13", int price=10999):
        Dell(brand,model,price),Computer(brand,model,price){};
    virtual void print()const {
        Dell::print();
        cout<<"CPU: Intel Core i7-10710U"<<endl;
        cout<<"RAM : 16GB LPDDR3 2133MHz"<<endl;
        cout<<"Memory: 1TB PCle"<<endl;
    }
};

class Company : public Apple ,public Dell
{
public:
    Company(string brand="Apple/Dell",string model="Latitude/Macbook",int price=10000,
            string brand1="Dell", string model1="Latitude", int price1=7999,
            string brand2="Apple", string model2="Macbook Pro", int price2=18999):
                Dell(brand1,model1,price1),Apple(brand2,model2,price2),Computer(brand,model,price){};
    virtual void print()const {
    cout<<"The Company is using two kinds of Computer"<<endl;
    cout<<endl<<endl;
    Apple::print();
    cout<<endl<<endl;
    Dell::print();
    }
};

void Computers(Computer *p[], int n)
    {
        for (int i=0; i<n; i++)
            {
                cout<<"Computer #" <<i+1<<":"<<endl;
                p[i]->print();
                cout<<endl;
            }
    }
int Computer::Count=0;
int main ()
{
    Apple a1;
    Low_Apple a2;
    High_Apple a3;
    Dell d1;
    Low_Dell d2;
    High_Dell d3;
    Computer * arr[] = {(Computer *)&a1,(Computer *)&a2,(Computer *)&a3,(Computer *)&d1,(Computer *)&d2,(Computer *)&d3};
    Computers(arr,sizeof(arr)/sizeof(Computer*));
    cout<<"Count="<<d2.Count<<endl;

    cout<<endl;
    Company Com;
    Computer *c = & Com;
    c->print();

    return 0;
}

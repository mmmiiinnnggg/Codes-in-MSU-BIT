#include <iostream>

using namespace std;

template<class T>class fr{
    T a,b;
public:
    fr(T m=0,T n=1){//constructor

        a=m;
        b=n;
    }
    // +
    fr operator+(const fr& y);
template<class F>//friend function
    friend fr<F> operator+(const F& r,const fr<F>& y);
    // -
    fr operator-(const fr& y);
template<class F>//friend function
    friend fr<F> operator-(const F& r,const fr<F>& y);
    // *
    fr operator*(const fr& y);
template<class F>//friend function
    friend fr<F> operator*(const F& r,const fr<F>& y);
    // /
    fr operator/(const fr& y);
template<class F>//friend function
    friend fr<F> operator/(const F& r,const fr<F>& y);

    friend ostream& operator<<(ostream& s,fr f){
        cout<<"("<<f.a<<"/"<<f.b<<")";
        return s;
    }
};

template<class T>
fr<T> fr<T>::operator+(const fr& y){//fraction + fraction ,fraction + int
    fr z;
    z.a=a*y.b+b*y.a;
    z.b=y.b*b;
    return z;
}

template<class T>
fr<T> operator+(const T& r,const fr<T>& y){//int + fraction
    fr<T> z;
    z.a=y.b*r+y.a;
    z.b=y.b;
    return z;
}

template<class T>
fr<T> fr<T>::operator-(const fr& y){//fraction - fraction , fraction - int
    fr z;
    z.a=a*y.b-b*y.a;
    z.b=y.b*b;
    return z;
}

template<class T>
fr<T> operator-(const T& r,const fr<T>& y){//int - fraction
    fr<T> z;
    z.a=y.b*r-y.a;
    z.b=y.b;
    return z;
}

template<class T>
fr<T> fr<T>::operator*(const fr& y){//fraction * fraction , fraction * int
    fr z;
    z.a=a*y.a;
    z.b=b*y.b;
    return z;
}

template<class T>
fr<T> operator*(const T& r,const fr<T>& y){//int * fraction
    fr<T> z;
    z.a=r*y.a;
    z.b=y.b;
    return z;
}

template<class T>
fr<T> fr<T>::operator/(const fr& y){//fraction / fraction , fraction / int
    fr z;
    z.a=a*y.b;
    z.b=b*y.a;
    return z;
}

template<class T>
fr<T> operator/(const T& r,const fr<T>& y){//int / fraction
    fr<T> z;
    z.a=r*y.b;
    z.b=y.a;
    return z;
}
int main()
{
    fr<int>a(1,3),b(3,5);
    int i=3;
    cout<<"a="<<a<<endl;
    cout<<"b="<<b<<endl;
    cout<<"i="<<i<<endl<<endl;
    cout<<"a+b,a+i,i+a:"<<endl;
    cout<<(a+b)<<endl;
    cout<<(a+i)<<endl;
    cout<<(i+a)<<endl<<endl;
    cout<<"a-b,a-i,i-a:"<<endl;
    cout<<(a-b)<<endl;
    cout<<(a-i)<<endl;
    cout<<(i-a)<<endl<<endl;
    cout<<"a*b,a*i,i*a:"<<endl;
    cout<<(a*b)<<endl;
    cout<<(a*i)<<endl;
    cout<<(i*a)<<endl<<endl;
    cout<<"a/b,a/i,i/a:"<<endl;
    cout<<(a/b)<<endl;
    cout<<(a/i)<<endl;
    cout<<(i/a)<<endl<<endl;
    return 0;
}

#include <iostream>
#include <cmath>

using namespace std;

class complex{
	double re,im;
public:
	complex(double re=0,double im=0){
		this->re = re;
		this->im = im;
	}
	/*
	complex(double re){
		this->re = re;
		im = 0;
	}
	
	complex(){
		re = 0;
		im = 0;
	}
	*/
	complex operator+(complex t){
		return complex(re+t.re,im+t.im);
    }
    
    complex operator-(complex t){
    	return complex(re-t.re,im-t.im);
    }
	
	complex operator*(complex t){
		return complex(re*t.re-im*t.im,re*t.im+im*t.re);
	}
	
	complex operator/(complex t){
		return complex((re*t.re+im*t.im)/(t.re*t.re+t.im*t.im),(im*t.re-re*t.im)/(t.re*t.re+t.im*t.im));
	}
	
	double mudulo(){
		return sqrt(re*re+im*im);
	}
	
	void print()const{
		cout<<"re="<<re<<" im="<<im<<endl; 
	}
};

int main(){
	complex c1(1,2);
	complex c2(2,3);
	complex c3(3,4);
	c3=c1+c2; c3.print();
	c3=c1-c2; c3.print();
	c3=c1*c2; c3.print();
	c3=c1/c2; c3.print();
	cout<<c1.mudulo();
	return 0;
}

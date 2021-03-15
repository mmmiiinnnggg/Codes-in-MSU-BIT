#include <iostream>

using namespace std;

class elephant{
	int trunk,tail;
public:
	elephant(int i,int j){
		trunk = i;
		tail = j;
	}
	int get_trunk()	{return trunk;}
	int get_tail()	{return tail;}
	void operator++(){
		trunk++;
	}
	void operator++(int k){
		tail++;
	}
};

int main()
{
	elephant E(1,1);//trunk = 1,tail = 1
	++E;
	cout << E.get_trunk() << endl;//2
	E++;
	cout << E.get_tail() << endl;//2
	return 0;
} 

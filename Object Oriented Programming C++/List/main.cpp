#include <iostream>
#include "list.h"
using namespace std;

int main() {
	List l1,l2('a'), l3("abc"), l4(l1), l5(l3);
	cout<<l1<<' '<<l2<<' '<<l3<<' '<<l4<<' '<<l5<<endl;
	cout<<(l1=l4)<<' '<<(l3)<<' '<<(l4=l3)<<endl;
	return 0;

}

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Graph{
	enum vertex {
		start,stop,C,Cplus
	};
	vertex v;
	int c,count=0;
public:
	int cut(){
		v=start;
		count=0;
		while(c=getchar()){
			switch(v){
				case start:
				    if(c=='C') v=C;
					else if(c=='\n') v=stop;
					break;
				case C:
				    if(c=='+') v=Cplus;
					else if(c=='\n') v=stop;
					else if(c!='C') v=start;
					break;
				case Cplus:
				    if(c=='+') {v=start;count++;}
					else if(c=='C') v=C;
					else if(c=='\n') v=stop;
					else v=start;
					break;
				case stop:
					return count;
			}
		}
	}
}; 

int main(){
	Graph G;
	std::cout<<G.cut();
	return 0;
}

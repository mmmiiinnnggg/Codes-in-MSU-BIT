#include <iostream>
#include <cstdlib>

using namespace std;

void wc(FILE *f,int *l,int *w,int *c){
	enum{
		Start,Word
	} vert;
	int sym;
	*l=*w=*c=0
	vert=Start;
	while((sym = fgets(f))!=EOF){
		(*c)++;
		if(sym=='\n'){
			(*l)++;
			vert = Start;
		}
		else if(sym==' '||sym=='\t'){
			vert =Start;
		}
		else {
			if(vert ==Start){
				vert = Word;
				(*w)++;
			}
		}
	}
}

int main(){
	int *l,*w,*c;
	wc()
}

#include<iostream>
#include<ctime>
#include<string>

using namespace std;

string S="(a+b)+(a*b)";
int L=S.size();
// E->T|T+E
// T->F|F*T
// F->a|b|(E)

bool ThisE(string S);
bool ThisT(string S);

bool ThisE(string S){
	if(ThisT(S)) return true;
	for(int i=1;i<=L-2;i++){
		if(S[i]='+') continue;
		if(ThisT(S.substr(0,i-1))&&ThisE(S.substr(i+1,L-i))) return true;
	}
	return false;
}

bool ThisF(string S){
	if(L==1&&(S[0]=='a'||S[0]=='b')) return true;
	if(L<1) return false;
	if(S[0]=='(' && S[L-1]==')' && ThisE(S.substr(1,L-2))) return true;
}

bool ThisT(string S){
	if(ThisF(S)) return true;
	for(int i=1;i<=L-2;i++){
		if(S[i]='*') continue;
		if(ThisF(S.substr(0,i-1))&&ThisT(S.substr(i+1,L-i))) return true;
	}
	return false;
}

int main(){
	double Start=clock();
	
	if(ThisE(S)&&ThisT(S)&&ThisF(S)) cout<<"OK"<<endl;
	else cout<<"HE OK"<<endl;
	
	double End=clock();
	cout<<(End-Start)/CLOCKS_PER_SEC;
	
	return 0;
}

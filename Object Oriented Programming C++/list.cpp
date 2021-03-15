#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class List{
	struct Node{
		char elem;
		Node* next;
		Node(char elem=' ',Node* next=NULL){
			this->elem=elem;
			this->next=next;
		}
	};
	Node *lst;//address of head
public:
	List():lst(NULL){}
	
	List(char c){
		lst=new Node(c); 
	}
	
	List(const char* s){
		if(*s=='\0'){
			lst=NULL;
			return;
		}
		Node *p;
		lst=p=new Node(*s++);
		while(*s!='\0'){
			p=p->next=new Node(*s++);
		}
	}
	
	bool empty()const{
		return (lst==NULL);
	}
	
	List(const List& l){//copy constructor
		if(l.empty()){
			lst=NULL;
			return;
		}
		Node *p,*pl=l.lst;//pl要复制的链表，p需要产生的链表 
		p=lst=new Node(pl->elem);
		pl=pl->next;
		while(pl!=NULL){
			p->next=new Node(pl->elem);
			p=p->next;
			pl=pl->next;
		}
	}
	
	void clear(){//clear the list
		Node* pl;
		while(lst!=NULL){
			pl=lst;
			lst=lst->next;
			delete pl;
		} 
	}
	
	~List(){
		this->clear();
	}
	//两个列表头尾连接 
	List operator+ (const List& l)const{
		Node *p,*pl;
	
        if(this->empty()){
               return l;
        }
           
        List res(*this);
           
        p=res.lst;
        while(p->next!=NULL){
            p=p->next;
        }

        pl=l.lst;
		
        while (pl!=NULL) {
			p=p->next=new Node(pl->elem);
            pl=pl->next;
		}	
		
		return res;
	}	

	friend List operator+(char c,const List& l2){
		if(l2.empty()){
			List ret(c);
			return ret;
		}
		
		Node *p;
		List res(l2);
		p=res.lst;
		res.lst=new Node(c);
		res.lst->next=p;
		return res;
	}

	List operator-(const List& l)const{
		Node *p,*plast;
		if(this->empty()){
			return l;
		}
	
		List res(*this);
		char a=(l.lst)->elem;
		
		p=res.lst;
		plast=res.lst;
		while(p->next!=NULL){//the first few are 'a'
			if(p->elem==a){
				p=p->next;
				plast=plast->next;
			}
			else break;
		}
		while(p->next!=NULL){
			if(p->elem!=a){
				plast=p;
			    p=p->next;
			}
			else{//meet the symbol 'a'
				p=p->next;
				plast->next=p;
			}
			
		}
		//if the last symbol is 'a'
		if(p->elem==a){
			plast->next=NULL;
		}
		return res;
	}
	
	friend List operator-(char a,const List& l2){
		Node *p,*plast;
		if(l2.empty()){
			return l2;
		}
		
		List res(l2);
		p=res.lst;
		plast=res.lst;
		while(p->next!=NULL){//the first few are not 'a'
			if(p->elem!=a){
				p=p->next;
				plast=plast->next;
			}
			else break;
		}
		while(p->next!=NULL){
			if(p->elem==a){
				plast=p;
			    p=p->next;
			}
			else{//meet the symbol except 'a'
				p=p->next;
				plast->next=p;
			}
		}
		//if the last symbol is not 'a'
		if(p->elem!=a){
			plast->next=NULL;
		}
		return res;
	}
	
	friend List operator~(const List& l){
		Node *p1,*p2;
		if(l.empty()){
			return l;
		}
		List res(l);
		p1=res.lst;
		p2=NULL;
		while(p1){
			p1=res.lst->next;//record the next node
			res.lst->next=p2;//current node point to last node
			p2=res.lst;//record current node(prepare for next cycle)
			res.lst=p1;//move to next node;
		}
		res.lst=p2;
		return res;
	}

	friend ostream& operator<<(ostream& s,const List& l){
		if(l.lst==NULL){
			s<<"";
			return s;
		}
		Node *pl=l.lst;
		while(pl!=NULL){
			s<<pl->elem;
			pl=pl->next;
		}
		return s;
	}
	
	List operator=(const List& l){
		Node *p,*pl;
		//the same thing
		if(&l==this){
			return *this;
		}
		
		this->clear();//clear 被赋值的列表 
		if(l.lst==NULL){
			return *this;
		}
		
		p=lst=new Node(l.lst->elem);
		pl=l.lst->next;
		//same as in the operation copy 
		while(pl!=NULL){
			p->next=new Node(pl->elem);
			p=p->next;
			pl=pl->next;
		}
		
		return *this;
	}
}; 

int main(){
	List l1("abcda");
	cout<<l1+l1<<endl;
	cout<<('a'+l1)<<endl;
	cout<<(l1-'a')<<endl;
	cout<<('a'-l1)<<endl;
	cout<<(~l1);
	return 0;
}

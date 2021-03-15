// MetodVetveiYGlanica.cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <time.h>
using namespace std;

const int nDimAll = 30; // dim of task
const int nDimArrSub = 200000; // dim of array, consisted of pointers at subtasks
const int nInfty = 99999;
const int nPereBor = 2; // enumerate when dim = 2

//truncated time
clock_t start_t, end_t;
double RecordTime,Currtime,RecordFirst;
int TimeOpt = 0; int check = 0, checkFirst = 0;
double Time = 0.01*2.21;

double f(double x){ // 3/5*f(x)
	return 1.0/2*(1+x*x*x*x);
}

double Rnd(){ 
	int x;
	x=rand()%100;
	return x/100.0;
}

double GetRnd(){
	double u1,u2;
	while(1){
		u1=Rnd();
		u2=Rnd();
		if(u2<=f(u1))
			return u1;
	}
}

class Array {
protected:
    int nDim;
    int* Arr;
    int MakeIndexSimple(int n) { return n - 1; }
    void InitMemory() { Arr = new int[nDim]; }
public:
    Array(int nDim) { this->nDim = nDim; InitMemory(); }
    ~Array() { delete[] Arr; }
    void Set(int nInd, int N) { Arr[MakeIndexSimple(nInd)] = N; }
    int Get(int nInd) { return Arr[MakeIndexSimple(nInd)]; }
    void InitNull() { for (int i = 1; i <= nDim; i++) Set(i, 0); }
    void InitCopy(Array* arr) { for (int i = 1; i <= nDim; i++) Set(i, arr->Get(i)); }
    friend ostream& operator<<(ostream& os, Array& arr);
};

ostream& operator<<(ostream& os, Array& arr) {
    for (int i = 1; i <= arr.nDim; i++) {
        os.width(3);
        os << arr.Get(i);
    }
    return os;
}

class Path : public Array {
public:
    Path() :Array(nDimAll) {}
    bool OK();
};

bool Path::OK() { //check Prev 
    int N = Get(1);
    for (int K = 1; K < nDimAll; K++) {
        if (N <= 1) return false;
        N = Get(N);
    }
    return N == 1;
}

class Numbers : public Array {
public:
    Numbers(int nDim) : Array(nDim) {}
    int GetByNumber(int nNum);
};

int Numbers::GetByNumber(int nNum) { // get order number of nNum
    for (int i = 1; i <= nDim; i++) if (Get(i) == nNum) return i;
    return 0;
}

class SubTask {
private:
    int nDim; // dim of subtask
    int nGran; // bound of subtask
    Numbers* Lin;
    Numbers* Col;
    int* Matr; // elements
    Path* Next;//(from,to) Next[To]=From
    Path* Prev;//(from,to) Prev[From]=To
private:
    int MakeIndex(int nX, int nY) { return (nX - 1) * nDim + (nY - 1); }
    void InitMemoryMatrix() { Matr = new int[nDim * nDim]; }
public:
    SubTask(int nDim);
    SubTask(int* Matr);//init zadacha
    ~SubTask();
    int GetnDim(){return nDim;}
    int GetLin(int I) { return Lin->Get(I); }
    int GetCol(int J) { return Col->Get(J); }
    void SetGran(int N) { nGran = N; }
    int GetGran() { return nGran; }
    bool GetPrevOK(){return Prev->OK();}
    void Set(int nI, int nJ, int N) { Matr[MakeIndex(nI, nJ)] = N; }
    int Get(int nI, int nJ) { return Matr[MakeIndex(nI, nJ)]; }
    friend ostream& operator <<(ostream& os, SubTask& st);

private:
    int MinLin(int nX);
    int MinLinDva(int nX); // find 2-nd Min element in Line
    int MinCol(int nY);
    int MinColDva(int nY); // find 2-nd Min element in Column
    void SetInftyByNubmers(int III, int JJJ);
public:
    //bool OK();
    void ReductionLin(int nX);
    void ReductionCol(int nY);
    void Reduction(); 
    void BestNull(int& nXdel, int& nYdel); // Find best 0, record coordinates
    SubTask* MakeRight(int nXdel, int nYdel);//Make Right SubTask, modify *this to Left SubTask
    int Solve(Path& Otvet); // Solve when nDim = 2, return pseudo-optimal solution, record this Path 
};

SubTask::SubTask(int nDim) {
    this->nDim = nDim;
    InitMemoryMatrix();
    Lin = new Numbers(nDim);
    Col = new Numbers(nDim);
    Next = new Path; Next->InitNull();
    Prev = new Path; Prev->InitNull();
}

SubTask::SubTask(int* Matr) {//for initilization and original matrix
    this->nDim = nDimAll;
    InitMemoryMatrix();
    nGran = 0;
    Lin = new Numbers(nDimAll);
    Col = new Numbers(nDimAll);
    Next = new Path; Next->InitNull();
    Prev = new Path; Prev->InitNull();
    for (int i = 1; i <= nDimAll; i++) {
        Lin->Set(i, i);
        Col->Set(i, i);
        for (int j = 1; j <= nDim; j++) Set(i, j, Matr[MakeIndex(i, j)]);
    }
    Reduction();
}

SubTask::~SubTask() {
    delete Lin;
    delete Col;
    delete[] Matr;
    delete Next;
    delete Prev;
}

ostream& operator<<(ostream& os, SubTask& st) {
    //cout<<"Subtask"<<endl;
    /*
    cout<<"       ";
    for (int j = 1; j <= st.nDim; j++) {
        os.width(5);
        cout << st.GetCol(j) << "." ;
    }
    cout<<endl;
    for (int i = 1; i <= st.nDim; i++) {
        os.width(6);
        cout << st.GetLin(i) << "." ;
        for (int j = 1; j <= st.nDim; j++) {
            os.width(6);
            os << st.Get(i, j);
        }
        cout << endl;
    }
    */

    cout << "dim=" << st.nDim << " nGran="<<st.nGran<<endl;

    /*
    cout<< "Next: ";
    for(int i=1;i<=nDimAll;i++){
        cout<<st.Next->Get(i)<<" ";
    }
    cout<<"\nPrev: ";
    for(int i=1;i<=nDimAll;i++){
        cout<<st.Prev->Get(i)<<" ";
    }
    //cout<<"\nCurrent pseudo-solution: ";
    //cout<<"\nCurrent pseudo-path: ";
    cout<<endl;
   */
    return os;
}

int SubTask::MinLin(int nX) {
    int Min = nInfty;
    for (int i = 1; i <= nDim; i++)
        if (Get(nX, i) < Min) Min = Get(nX, i) ;
    return Min;
}

int SubTask::MinLinDva(int nX) {
    int sign = 0;
    int Min = nInfty;
    for (int i = 1; i <= nDim; i++) {
        if (sign == 0 && Get(nX, i) == 0) { sign = 1; continue; }
        else if (sign == 1 && Get(nX, i) == 0) return 0;
        else if (Get(nX, i) < Min) Min = Get(nX, i);
    }
    return Min;
}

int SubTask::MinCol(int nY) {
    int Min = nInfty;
    for (int i = 1; i <= nDim; i++)
        if (Get(i, nY) < Min) Min = Get(i, nY);
    return Min;
}

int SubTask::MinColDva(int nY) {
    int sign = 0;
    int Min = nInfty;
    for (int i = 1; i <= nDim; i++) {
        if (sign == 0 && Get(i, nY) == 0) { sign = 1; continue; }
        else if (sign == 1 && Get(i, nY) == 0) return 0;
        else if (Get(i, nY) < Min) Min = Get(i, nY);
    }
    return Min;
}

void SubTask::SetInftyByNubmers(int III, int JJJ) {
    Set(III, JJJ,nInfty);
}

void SubTask::ReductionLin(int nX) {
    int Min = MinLin(nX);
    for (int i = 1; i <= nDim; i++) Set(nX,i,Get(nX,i)-Min);
    SetGran(GetGran()+Min);
}

void SubTask::ReductionCol(int nY) {
    int Min = MinCol(nY);
    for (int i = 1; i <= nDim; i++) Set(i,nY,Get(i,nY)-Min);
    SetGran(GetGran()+Min);
}

void SubTask::Reduction() {
    for (int i = 1; i <= nDim; i++) ReductionLin(i);
    for (int j = 1; j <= nDim; j++) ReductionCol(j);
}

void SubTask::BestNull(int& nXdel, int& nYdel) {
    int BestNum = 0;
    int FirstNum=0;
    int D, Besti = 1, Bestj = 1;
    for(int i=1;i<=nDim;i++)
        for (int j = 1; j <= nDim; j++) {
            if (Get(i,j) != 0) continue;
            else { //==0
            	if(!FirstNum) {
            		D = MinLinDva(i) + MinColDva(j); 
            		Besti = i; Bestj = j; BestNum = D; FirstNum = 1; 
            	}
            	else {
                	D = MinLinDva(i) + MinColDva(j);
                	if (D > BestNum) {
                    	BestNum = D; Besti = i; Bestj = j;
                	}
            	}
            }
        }
    nXdel = Lin->Get(Besti);
    nYdel = Col->Get(Bestj);
}

SubTask* SubTask::MakeRight(int nXdel, int nYdel) {
    SubTask* PtrNewRight = new SubTask(nDim-1);

    //change of number
    int k_1 = 1; int k_2 = 1;
    for (int i = 1; i <= nDim; i++) {
        if (Lin->Get(i) == nXdel) continue;
        PtrNewRight->Lin->Set(k_1,Lin->Get(i));
        k_1++;
    }

    for (int i = 1; i <= nDim; i++) {
        if (Col->Get(i) == nYdel) continue;
        PtrNewRight->Col->Set(k_2,Col->Get(i));
        k_2++;
    }

    //Right nGran
    PtrNewRight->nGran = nGran;
    //change of matirx
    k_1 = 1; k_2 = 1;
    for (int i = 1; i <= nDim; i++) {
        if (Lin->Get(i) == nXdel) continue;
        for (int j = 1; j <= nDim; j++) {
            if (Col->Get(j) == nYdel) continue;
            PtrNewRight->Set(k_1, k_2,Get(i, j));
            k_2++;
        }
        k_2=1;
        k_1++;
    }

    //Set (nYdel,nXdel) to Infty, if it exists
    if(PtrNewRight->Lin->GetByNumber(nYdel) != 0 && PtrNewRight->Col->GetByNumber(nXdel) != 0)
        PtrNewRight->Set(PtrNewRight->Lin->GetByNumber(nYdel),PtrNewRight->Col->GetByNumber(nXdel),nInfty);
    //Reduction of Right
    PtrNewRight->Reduction();

    //change of Path - first copy from last subtask
    for (int i = 1; i <= nDimAll; i++) {
        PtrNewRight->Next->Set(i,Next->Get(i));
        PtrNewRight->Prev->Set(i,Prev->Get(i));
    }
    //then set new way
    PtrNewRight->Next->Set(nYdel, nXdel);
    PtrNewRight->Prev->Set(nXdel, nYdel);

    //change of left task and pointers
    //Set choosed way to Infty in the Left
    Matr[MakeIndex(Lin->GetByNumber(nXdel), Col->GetByNumber(nYdel))] = nInfty;
    //change of left task nGran;
    Reduction();

    return PtrNewRight;
}

int SubTask::Solve(Path& Otvet) { 
    if (nDim != nPereBor) exit(0); 
    int Judge = 1;
    int Fir = Matr[MakeIndex(1, 1)] + Matr[MakeIndex(2, 2)];
    int Sec = Matr[MakeIndex(1, 2)] + Matr[MakeIndex(2, 1)];
    if (Fir < Sec) {
        Next->Set(Col->Get(1), Lin->Get(1));
        Next->Set(Col->Get(2), Lin->Get(2));
        Prev->Set(Lin->Get(1), Col->Get(1));
        Prev->Set(Lin->Get(2), Col->Get(2));
        //get Path "Otvet"
        for(int i=1;i<=nDimAll;i++)
        {
            if(i==1) Otvet.Set(1,1);
            else Otvet.Set(i,Prev->Get(Otvet.Get(i-1)));
        }
        if(Prev->OK()) return nGran + Fir;
        else Judge = 0;
    }

    if(Fir>=Sec || Judge ==0) {
        Next->Set(Col->Get(1), Lin->Get(2));
        Next->Set(Col->Get(2), Lin->Get(1));
        Prev->Set(Lin->Get(1), Col->Get(2));
        Prev->Set(Lin->Get(2), Col->Get(1));
        //get Path "Otvet"
        for(int i=1;i<=nDimAll;i++)
        {
            if(i==1) Otvet.Set(1,1);
            else Otvet.Set(i,Prev->Get(Otvet.Get(i-1)));
        }
        if(Prev->OK()) return nGran + Sec;
        else {
        	Next->Set(Col->Get(1), Lin->Get(1));
        	Next->Set(Col->Get(2), Lin->Get(2));
        	Prev->Set(Lin->Get(1), Col->Get(1));
        	Prev->Set(Lin->Get(2), Col->Get(2));
        	//get Path "Otvet"
        	for(int i=1;i<=nDimAll;i++)
       		{
            	if(i==1) Otvet.Set(1,1);
           		else Otvet.Set(i,Prev->Get(Otvet.Get(i-1)));
        	}
        	return nGran + Fir;
        }
    }
}

class Task {
private:
    int* Matr;//original matrix
    int nKol;//current number of subtasks
    SubTask* Zadachi[nDimArrSub];//matrix of subtask pointers
    int nOpt;//current optimal solution
    Path* pOpt;
public:
    Task();//with init of memory
    ~Task();
    int MakeIndex(int nX, int nY) { return (nX - 1) * nDimAll + (nY - 1); }
    int Get(int i, int j) { return Matr[MakeIndex(i, j)]; }
    int GetnKol(){return nKol;}
    int GetnOpt(){return nOpt;}
    SubTask* GetZadachi(int Position){return Zadachi[Position];}
    void ReadFile();
    void InitRnd();
    void InitFirst();
    friend ostream& operator<<(ostream& os, Task& t);
    SubTask* ExtractFirst();// Convert Task T to SubTask with reduction
    void SolveSubTask(SubTask*& st, int Position);//solve Subtask to the bottom and get pOpt
    int BestNext(); // From rest SubTasks find the Subtask with min nGran (To do next branch)
    void AddSubTask(SubTask* st, int Position);//Add st to Position in Zadachi, if Postion==0 Add to the last
    int DelTail(int gran);//delete from this bound and return current number of SubTask (To verify the end of algorithm)
    void Run();
};

Task::Task() {
    Matr = new int[nDimAll * nDimAll];
    pOpt = new Path;
}

Task::~Task() {
    delete Matr;
    delete pOpt;
}

void Task::InitFirst() {
    nOpt = nInfty;
    nKol = 0;
}

ostream& operator<<(ostream& os, Task& t) {
    cout << "Original task" << endl;
    cout << "dim=" << nDimAll << " nGran=0" << endl;
    
    cout<<"       ";
    for (int j = 1; j <= nDimAll; j++) {
        os.width(5);
        cout << j << ".";
    }
    cout<<endl;
    for (int i = 1; i <= nDimAll; i++) {
        os.width(6);
        cout << i << ".";
        for (int j = 1; j <= nDimAll; j++) {
            os.width(6);
            os << t.Get(i, j);
        }
        cout << endl;
    }
	
    return os;
}

SubTask* Task::ExtractFirst() {
    SubTask* PtrNew = new SubTask(Matr);
    //extractFirstLeft,then use SolveSubTask
    nKol++;
    AddSubTask(PtrNew,1);
    return PtrNew;
}

void Task::SolveSubTask(SubTask*& st, int Position) { //divide into two subtask or solve dim=2, Position - Num in Zadachi
    if(st->GetnDim()!=2){
        int nXdel,nYdel;
        SubTask* Right;
        st->BestNull(nXdel,nYdel);
        Right=st->MakeRight(nXdel,nYdel);//Right - Right SubTask, st - Left SubTask
        //Print two SubTasks
     
        //cout<<"#"<<Position<<"   Left"<<endl;
        //cout<<*st<<endl;
        //cout<<"#"<<nKol+1<<"   Right Chosen ("<<nXdel<<","<<nYdel<<")"<<endl;
        //cout<<*Right<<endl;
        
        AddSubTask(st,Position);
        nKol++;
        AddSubTask(Right,0);
        //cout<<"Current Zadachi ";
        //for(int i=1;i<=nKol;i++) cout<<Zadachi[i]->GetGran()<<" ";
        //cout<<endl<<endl;

        //SolveSubTask(Right,nKol);
    }
    else {
        Path* Curr; Curr = new Path;
        int CurrOpt = st->Solve(*Curr);
        if(CurrOpt < nOpt && st->GetPrevOK()) {
        	nOpt=st->Solve(*pOpt);
        	cout<<"Solving with brute force..."<<endl;
        	cout<<"Current pseudo-path: ";
        	for(int i=1;i<=nDimAll;i++)
            	cout<<Curr->Get(i)<<" ";
        	cout<<endl;
        	if(!checkFirst) {RecordFirst = (double)(clock() - start_t) / CLOCKS_PER_SEC; checkFirst = 1;}
        }
        else { //Failed 
        	delete Zadachi[Position];
        	for(int j=Position;j<nKol;j++)
                Zadachi[j]=Zadachi[j+1];//move
            Zadachi[nKol]=NULL;
            nKol--;
        	cout<<"Solving with brute force..."<<endl;
        	cout<<"CurrOpt = "<<CurrOpt<<endl<<"CurrPath: ";
        	for(int i=1;i<=nDimAll;i++) cout<<Curr->Get(i)<<" ";
        	cout<<"\nSOLVING FAILED! GOT BIGGER SOLUTION OR INVALID PATH!"<<endl;
        }

        delete Curr;
        cout<<"----------------"<<endl;
    	cout<<"nKol= "<<nKol<<" nOpt= "<<nOpt<<endl;
    	cout<<"----------------"<<endl;
    	cout<<"----------------"<<endl;
    }
}

void Task::AddSubTask(SubTask* st, int Position) {//Add SubTask to Position - if Position == 0 then Add to Last;  
    if(Position) Zadachi[Position]=st;
    else Zadachi[nKol]=st;//the nKol's Subtask - st
}

int Task::DelTail(int gran) {
    int i=1;
    while(i<=nKol){
        if(Zadachi[i]->GetGran()>=gran){
            delete Zadachi[i];
            for(int j=i;j<nKol;j++) Zadachi[j]=Zadachi[j+1];//move
            Zadachi[nKol]=NULL; nKol--;
        }
        else i++;
    }

    return nKol;
}

int Task::BestNext(){
    int Min = nInfty;
    int MinNum;
    for(int i=1;i<=nKol;i++) 
        if(Zadachi[i]->GetGran()<Min){
            Min = Zadachi[i]->GetGran();
            MinNum = i;
        }
    return MinNum;
}

void Task::Run() {
    SubTask* First;
    First = ExtractFirst();
    AddSubTask(First,1);
    //cout<<"#0 Original task with reduction"<<endl; cout<<*First<<endl;
    while(nKol!=0){
    	DelTail(nOpt); 
    	if(nKol==0) break; // After delete all subtasks are cancelled - END 
    	SolveSubTask(Zadachi[BestNext()],BestNext());
    	Currtime = (double)(clock() - start_t) / CLOCKS_PER_SEC;
    	if( check == 0 && Currtime >= Time) { TimeOpt = nOpt; RecordTime = Currtime; check = 1;}
    }

    cout<<"\nEND OF ALGORITHM!";
    cout<<"\nOptimal solution: "<<nOpt;
    cout<<"\nOptimal Path: ";
    for(int i=1;i<=nDimAll;i++)
        cout<<pOpt->Get(i)<<" ";
    cout<<endl;
}

void Task::InitRnd(){
	FILE* fp1;
	if ((fp1 = fopen("out1-3.txt", "w+")) == NULL){
    //if ((err= fopen_s(&fp1,"test1.txt", "r")) == 0) {
        printf("Cannot open test file\n");
        exit(0);
    }
    int rnd; char str[6]; srand(time(NULL));
    for(int i=1;i<=nDimAll;i++){
    	for(int j=1;j<=nDimAll;j++){
    		if(i==j){ 
    			itoa(nInfty,str,10);
    			fputs(str,fp1);
    			if(j!=nDimAll) {fputs(" ",fp1);}
    		}
    		else{
    			rnd = GetRnd()*100;
    			itoa(rnd,str,10);
    			fputs(str,fp1);
    			if(j!=nDimAll) fputs(" ",fp1);
    		}
    	}
    	fputs("\n",fp1);
    }

    fclose(fp1);
}

void Task::ReadFile() {
	FILE* fp1;
    //errno_t err;
    if ((fp1 = fopen("out1-3.txt", "r")) == NULL){
    //if ((err= fopen_s(&fp1,"test1.txt", "r")) == 0) {
        printf("Cannot open test file\n");
        exit(0);
    }
	int x;
	for (int i = 1; i <= nDimAll; i++)
		for (int j = 1; j <= nDimAll; j++) {
			fscanf(fp1, "%d", &x);
			if (i == j) Matr[MakeIndex(i,j)] = nInfty;
			else Matr[MakeIndex(i,j)] = x;
		}
}

int main()
{
    //clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    Task T; 
    //T.InitRnd(); 
    T.ReadFile(); T.InitFirst(); cout<<"#0"<<endl;cout << T << endl;
    T.Run();
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    cout<<"Running time: "<<total_t<<" s";
    cout<<"\nTimeOpt = "<<TimeOpt<<" Recordtime = "<<RecordTime<<" Time = "<<Time;
    cout<<"\nFirstOpttime = "<<RecordFirst<<endl;
    return 0;
}
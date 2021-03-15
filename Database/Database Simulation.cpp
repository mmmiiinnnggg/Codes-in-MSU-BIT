
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;

/////////////////////////////////////////////////////////////////
long int RndDouble() {
	return rand() * 32768.0 + rand();
}

char RndCaps() {
	return 'A' + (rand()%26);
}

char RndLitt() {
	return 'a' + (rand()%26);
}

int RndDiap(int nMin, int nMax) {
	return nMin + rand() % (nMax-nMin+1);
}

bool Menshe(string s1, string s2) {
	if (s2.size()==0) return false;
	if (s1.size()==0) return true;
	char c1 = s1[0], c2 = s2[0];
	if (c1==c2) return Menshe(s1.substr(1),s2.substr(1));
	if (c2==' ') return false;
	if (c1==' ') return true;
	return c1<c2;
}

////////////////////////////////////////////////////////////////////////////////////
class Fio {
private:
	string sFio; // ключевое поле ФИО
public:
	Fio() {}
	Fio(const Fio& fio) { this->sFio = fio.sFio; }
	void RndInit(); // "случайная" инициализация
	string GetString() { return sFio; }
	friend ostream& operator<<(ostream& os, const Fio& f);
	friend bool operator==(const Fio& f1, const Fio& f2);
	friend bool operator<(const Fio& f1, const Fio& f2);
};

///////////////////////////////////////////////////
void Fio::RndInit() {
	sFio = "";
	int L = RndDiap(1,10);
	sFio += RndCaps();
	for (int i=0; i<L; i++) sFio += RndLitt();
	L = RndDiap(1,10);
	sFio += ' '; sFio += RndCaps();
	for (int i=0; i<L; i++) sFio += RndLitt();
	L = RndDiap(1,10);
	sFio += ' '; sFio += RndCaps();
	for (int i=0; i<L; i++) sFio += RndLitt();
}

ostream& operator<<(ostream& os, const Fio& f) {
	os << f.sFio;
	int T = 30 - f.sFio.size();
	if (T<=0) return os;
	for (int i=0; i<T; i++) os << " ";
	return os;
}

bool operator== (const Fio& f1, const Fio& f2) {
	return f1.sFio == f2.sFio;
}

bool operator< (const Fio& f1, const Fio& f2) {
	return Menshe(f1.sFio,f2.sFio);
}

////////////////////////////////////////////////////////////////////////////////////
enum Country {Rossia, Germania, Kitay, Pindostan, Antarktida, Gvatemala, Gonduras};

////////////////////////////////////////////////////////////////////////////////////
class Student {
private:
	Fio fio; // ключевое поле ФИО
	long int rRating; // ключевое поле рейтинг
	Country cCountry; // (неключевое) поле страна
	int nGruppe; // (неключевое) поле номер учебной группы
	int DD, MM, GG; // (неключевые) поля дата рождения
public:
	// конструктор йок - nользуемся умалчиваемым
	void RndInit(); // "случайная" инициализация
	Fio& GetFio() { return fio; }
	long int GetRating() { return rRating; }
	Country GetCountry() { return cCountry; }
	friend ostream& operator<<(ostream& os, const Student& s);
	// а операторы сравнения - здесь совершенно ни к месту!
};

///////////////////////////////////////////////////
void Student::RndInit() {
	// ФИО
	fio.RndInit();
	// рейтинг
	rRating = RndDouble();
	// страна
	int T = RndDiap(0,6);
	switch(T) {
		case 0: cCountry = Rossia; break;
		case 1: cCountry = Germania; break;
		case 2: cCountry = Kitay; break;
		case 3: cCountry = Pindostan; break;
		case 4: cCountry = Antarktida; break;
		case 5: cCountry = Gvatemala; break;
		case 6: cCountry = Gonduras; break;
	}
	// номер учебной группы
	nGruppe = RndDiap(101,499);
	// дата рождения
	DD = RndDiap(1,28);
	MM = RndDiap(1,12);
	GG = RndDiap(1990,2012);
}

ostream& operator<<(ostream& os, const Student& s) {
	os << "FIO: " << s.fio << "  ";
	os.width(13); os << "Rating: "  << s.rRating << "  ";
	os << "Country: ";
	switch(s.cCountry) {
		case Rossia: os << "Rossia      "; break;
		case Germania: os << "Germania    "; break;
		case Kitay: os << "Kitay       "; break;
		case Pindostan: os << "Pindostan   "; break;
		case Antarktida: os << "Antarktida  "; break;
		case Gvatemala: os << "Gvatemala   "; break;
		case Gonduras: os << "Gonduras    "; break;
	}
	os << "Gruppa: " <<  s.nGruppe << "  ";
	if (s.DD<10) os << 0; os << s.DD << ".";
	if (s.MM<10) os << 0; os << s.MM << ".";
	os.width(4); os << s.GG;
	os << endl;
	return os;
}

////////////////////////////////////////////////////////////////////////////////////
const int NALL = 32767;

class StudentsAll { // только массив с данными - без каких-либо деревьев
private:
	int nKol; // текущее количество; оно только увеличивается
	Student students[NALL];
public:
	StudentsAll() { nKol = 0; }
	int GetKol() { return nKol; }
	Fio GetFio(int i) { return students[i].GetFio(); }
	long int GetRating(int i) { return students[i].GetRating(); }
	Country GetCountry(int i) { return students[i].GetCountry(); }
	bool Add(Student& st);
	friend ostream& operator<<(ostream& os, const StudentsAll& stall);
} stall; // вот только с этим "массивом" stall и будем работать

///////////////////////////////////////////////////
bool StudentsAll::Add(Student& st) {
	if (nKol>=NALL) return false;
	students[nKol++] = st;
	return true;
}

ostream& operator<<(ostream& os, const StudentsAll& stall) {
	for (int i=0; i<stall.nKol; i++) {
		os.width(4); os << i << ".  "; 
		os << stall.students[i];
	}
	return os;
}

////////////////////////////////////////////////////////////////////////////////////
template <class Key>
class AVLTree {
private:
	int nDepth; // глубина дерева; для пустого -1, для одной вершины 0, и т.д.
	Key* pKey; // по этому ключу дерево поиска и строится; деструктором удаляется!
	int nNom; // номер записи об этом студенте в массиве stall
	AVLTree* pParent; // родитель; деструктором не удаляется
	AVLTree* pLeft; // левое поддерево; деструктором удаляется!
	AVLTree* pRight; // правое поддерево; деструктором удаляется!
public:
	AVLTree() { nDepth = -1; }
	~AVLTree() { if (nDepth<0) return; delete pKey; delete pLeft; delete pRight; }
	int GetDepth() { return nDepth; }
	int GetNom() { return nNom; }
	AVLTree* GetLeft() { return pLeft; }
	AVLTree* GetRight() { return pRight; }
	bool Add(Key* pKey, AVLTree* pParent, int nNom); // работаем с нужной (nNom) записью массива stall
	int Search(Key* pKey); // возвращает найденный nNom (или -1, если не нашли)
};

template <class Key>
bool AVLTree<Key>::Add(Key* pKey, AVLTree* pParent, int nNom) {
	if (nDepth<0) {
		nDepth = 0;
		this->pKey = new Key(*pKey);
		this->nNom = nNom; 
		this->pParent = pParent;
		this->pLeft = new AVLTree<Key>;
		this->pRight = new AVLTree<Key>;
		return true;
	}
	if (*this->pKey == *pKey) return false; // уже такой есть; но в массиве вся строка пусть останется...
	if (*this->pKey < *pKey) { if (!pLeft-> Add(pKey,this,nNom)) return false; } // ключ меньше, добавляем налево
	else                     { if (!pRight->Add(pKey,this,nNom)) return false; } // ключ больше, добавляем направо
	nDepth = max(pLeft->GetDepth(),pRight->GetDepth())+1; 
	return true;
}

template <class Key>
int AVLTree<Key>::Search(Key* pKey) {
	if (nDepth<0) return -1;
	if (*this->pKey == *pKey) return this->nNom;
	return (*this->pKey < *pKey) ? pLeft->Search(pKey) : pRight->Search(pKey);
}

////////////////////////////////////////////////////////////////////////////////////
/// далее - чОрт с ними с деревьями...
/// принцип совсем иной:
/// заводится класс, в котором отмечаем, есть ли реально этот элемент в БД (т.е. не удалили ли мы его уже)
/// при этом употребляем:
/// для select'а - объект (основной, "статический" - но "static" употреблять не будем) этого класса,
/// он первоначально копируется из stdall на основе "AVL по ключам"
/// для reselect'а - объект этого же класса, сделанный на основе предыдущего объекта
/// "короче" - "детский сад"...

////////////////////////////////////////////////////////////////////////////////////
class ArraySelect {
private:
    int nDim;   
    bool* Arr; // сами элементы массива (да/нет); №№ совпадают с №№ в массиве stall
public:
	// конструктор видимо не нужен ("от слова совсем") - пользуемся умалчиваемым
    ~ArraySelect() { DisposeMemory(); }
	void InitMemory(int nDim); // инициализация памяти
	void DisposeMemory();               
    void InitEmpty(); 
    void SetFalse(int i) { if (i<nDim) Arr[i] = false; }
    void SetTrue(int i) { if (i<nDim) Arr[i] = true; }
    void InitByTree(AVLTree<Fio>* pAVL); // (первоначальная) инициализация этого массива по студентам, имеющимся в первом дереве поиска
    // далее связанное с (re)select'ами
    // далее печать - совсем-простая, простая и "сложная"
    void ByFio(string Begin, StudentsAll& stall); // параметр - начало фамилии
    void ByRating(long int liMin, long int liMax, StudentsAll& stall); // параметр - начало фамилии
    void ByCountry(string Begin, StudentsAll& stall); // параметр - начало названия страны
	friend ostream& operator<<(ostream& os, const ArraySelect& as);
};

///////////////////////////////////////////////////
void ArraySelect::InitMemory(int nDim) {
	this->nDim = nDim;
	Arr = new bool[nDim];
}

void ArraySelect::DisposeMemory() {
	delete[] Arr;
}

void ArraySelect::InitEmpty() {
	for (int i=0; i<nDim; i++) SetFalse(i);
}

void ArraySelect::InitByTree(AVLTree<Fio>* pAVL) {
	if (pAVL->GetDepth() < 0) return;
	SetTrue(pAVL->GetNom());
	InitByTree(pAVL->GetLeft());
	InitByTree(pAVL->GetRight());
}

void ArraySelect::ByFio(string Begin, StudentsAll& stall) {
	int L = Begin.size();  if (L <= 0) return;
	string EndPlus(Begin); EndPlus[L-1]++;
	for (int i=0; i<nDim; i++) {
		if (!Arr[i]) continue;
		string sfio = stall.GetFio(i).GetString(); 
		if ((Menshe(Begin,sfio) || Begin==sfio) && (Menshe(sfio,EndPlus))) continue; 
		Arr[i] = false;
	}
}

void ArraySelect::ByRating(long int liMin, long int liMax, StudentsAll& stall) {
	for (int i=0; i<nDim; i++) {
		if (!Arr[i]) continue;
		long int T = stall.GetRating(i); 
		if (liMin<=T && T<=liMax) continue; 
		Arr[i] = false;
	}
}

void ArraySelect::ByCountry(string Begin, StudentsAll& stall) {
	Country country = Rossia;
	if (Begin=="German" || Begin=="Germani" || Begin=="Germania") country = Germania;
	else if (Begin=="Kit" || Begin=="Kita" || Begin=="Kitay") country = Kitay;
	else if (Begin=="Pindost" || Begin=="Pindosta" || Begin=="Pindostan") country = Pindostan;
	else if (Begin=="Antarkti" || Begin=="Antarktid" || Begin=="Antarktida") country = Antarktida;
	else if (Begin=="Gvatema" || Begin=="Gvatemal" || Begin=="Gvatemala") country = Gvatemala;
	else if (Begin=="Gondur" || Begin=="Gondura" || Begin=="Gonduras") country = Gonduras;
	for (int i=0; i<nDim; i++) {
		if (!Arr[i]) continue;
		Country T = stall.GetCountry(i); 
		if (T==country) continue; 
		Arr[i] = false;
	}
}

ostream& operator<<(ostream& os, const ArraySelect& as) {
	os << as.nDim << " ";
	for (int i=0; i<as.nDim; i++) os << (as.Arr[i]==0 ? 0 : 1);
	os << endl;
	return os;
}

////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
	StudentsAll stall;
	AVLTree<Fio> avlFIO; // вот оно - первое AVL-дерево (по ФИО)
	AVLTree<long int> avlRating; // вот оно - второе AVL-дерево (по рейтингу)
	// типа общее число студиозусов
	int nStud = 100;
	// проверка поиска в дереве по ФИО (1-му ключевому полю)
	for (int i=0; i<nStud; i++) {
		Student st; st.RndInit(); 
		stall.Add(st);
		// в следующих строках такая проверку: если уже был хоть один такой ключ - не включаем в AVL-деревья (ни в одно)
		// одновременно включение с проверкой совмещать нежелательно, 
		// поскольку хоть одно нарушение "ключа" приведёт к не-включению ни в одно дерево
		Fio fio(stall.GetFio(i)); if (avlFIO.Search(&fio)>=0) continue;
		long int T = st.GetRating(); if (avlRating.Search(&T)>=0) continue;
		// само включение в оба AVL-дерева
		avlFIO.Add(&fio,NULL,stall.GetKol()-1);
		avlRating.Add(&T,NULL,stall.GetKol()-1);
	}
	cout << stall << endl << endl;
	// проверка поиска в дереве по ФИО (1-му ключевому полю)
	Fio fio = stall.GetFio(79); 
	cout << fio << endl;
	cout << avlFIO.Search(&fio) << endl << endl;
	// проверка поиска в дереве по рейтингу (2-му ключевому полю)
	long int rating = stall.GetRating(24); 
	cout << rating << endl;
	cout << avlRating.Search(&rating) << endl << endl;
	// заведение первоначального "детсадовского" массива (и его печать)
	ArraySelect as;
	as.InitMemory(nStud);
	// проверяем попадание фамилии
	as.InitEmpty(); cout << as;
	as.InitByTree(&avlFIO); cout << as;
	as.ByFio("Jl",stall); cout << as << endl; // находим одного
	// проверяем попадание рейтинга в диапазон
	as.InitEmpty(); cout << as;
	as.InitByTree(&avlFIO); cout << as;
	as.ByRating(777777777,888888888,stall); cout << as << endl; // находим примерно десятую часть всех
	// далее RESELECT! из УЖЕ ИМЕЮЩЕГОСЯ выбираем нужную страну!
	as.ByCountry("German",stall); cout << as << endl; // находим примерно десятую часть всех
	// специальный конец работы с "детсадовским" массивом не нужен: деструктор вызовет освобождение памяти
	//
	cout << "***** KONEC" << endl;
	return 0;
}


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>   // для работы с текстовыми файлами
using namespace std;

/////////////////////////////////////////////////////////
class BTree {
protected:
	bool Empty;
	int A;
	BTree* Left;
	BTree* Right;
public:
	BTree();
	BTree(BTree& BT);
	BTree(BTree* pBT);
	~BTree();
	int Depth();
	void Print() { Print(0,3); }
	bool Add(int Anew);
	bool Del(int AAA);
	BTree* ProtoMin();
private:
	void Print(int Space, int SpaceL);
};

/////////////////////////////////////////////////////////
class BTreeD : public BTree {
public:
	int nDeep;
	void Print() { Print(0,6); }
private:
	void Print(int Space, int SpaceL);
};
	
/////////////////////////////////////////////////////////
BTree::BTree() {
	Empty = true;
}

BTree::BTree(BTree& BT) {
	Empty = true;
	if (BT.Empty) return;
	Empty = false;
	A = BT.A;
	Left = new BTree(*BT.Left);
	Right = new BTree(*BT.Right);
}

BTree::BTree(BTree* pBT) {
	Empty = true;
	if (pBT->Empty) return;
	Empty = false;
	A = pBT->A;
	Left = new BTree(pBT->Left);
	Right = new BTree(pBT->Right);
}

BTree::~BTree() {
	if (Empty) return;
	delete Left;
	delete Right;
}
	
int BTree::Depth() {
	if (Empty) return -1;
	return 1+max(Left->Depth(),Right->Depth());
}

void BTree::Print (int Space, int SpaceL) {
    if (Empty) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A;
    Right->Print(0,SpaceL+3);
    if (Right->Empty) cout << endl;
    Left->Print(SpaceL,SpaceL+3);
}

bool BTree::Add(int Anew) {
	if (Empty) {
		Empty = false;
		A = Anew;
		Left = new BTree;
		Right = new BTree;
		return true;
	}
	if (Anew==A) return false;
	if (Anew<A) return Left->Add(Anew);
	return Right->Add(Anew);
}

BTree* BTree::ProtoMin() {
	if (Left->Left->Empty) return this;
	return Left->ProtoMin();
}

bool BTree::Del(int AAA) {
    if (Empty) return false;    // ничего удалить не смогли
    if (AAA<A) return Left->Del(AAA);   // здесь удобнее читать в таком порядке
    if (AAA>A) return Right->Del(AAA);
    // всюду далее A==AAA
    if (Left->Empty && Right->Empty) {  // мы - лист
        Empty = true;
        delete Left;
        delete Right;
        return true;
    }
    if (Right->Empty) { // согласно предыдущему, условие ->LeftIsEmpty() здесь неверно!
                        // т.е. слева что-то есть! (аналогично тому, как на 2-й картинке)
        A = Left->A;
        delete Right;
        BTree* oldLeft = Left;
        Right = Left->Right;
        Left = Left->Left;
        // далее хотелось бы воспользоваться освобождением памяти без деструктора
        // но (поскольку в Си++ это непросто) лучше его вызвать (после подготовки!)
        oldLeft->Left = NULL;
        oldLeft->Right = NULL;
        delete oldLeft;
        return true;
    }
    // внимание! аналогично предыдущему случаю (да и тем, которые далее) -
    // удаляем 1 элемент, а деструктор (для пустого звена) вызываем дважды!
    if (Left->Empty) {  // согласно предыдущему, условие Right->IsEmpty() здесь неверно!
                        // т.е. справа что-то есть! (такой картинки нет)
        A = Right->A;
        delete Left;
        BTree* oldRight = Right;
        Left = Right->Left;
        Right = Right->Right;
        oldRight->Left = NULL;
        oldRight->Right = NULL;
        delete oldRight;
        return true;
    }
    // далее оба поддерева непусты;
    // ищем (как на 3-й картинке) минимальный элемент в правом поддереве
    // (а можно было бы наоборот: искать максимальный элемент в левом поддереве)
    // (выбор "какое поддерево предпочтительнее" мы здесь не рассматриваем - работаем с правым)
    // но!!!! в отличие от того, что на картинке, этот элемент не обязан быть листом!!
    if (Right->Left->Empty) {  // искать ничего не надо
        A = Right->A;
        BTree* Tmp = Right;
        Right = Right->Right;
        Tmp->Right = NULL;
        delete Tmp;
        return true;
     }
     // далее ищем указатель на "тот самый" минимальный элемент в правом поддереве
     BTree* Tmp1 = Right->ProtoMin();
     A = Tmp1->Left->A;
     BTree* Tmp2 = Tmp1->Left;
     Tmp1->Left = Tmp2->Right;
     Tmp2->Right = NULL;
     delete Tmp2;
     return true;
}

void BTreeD::Print (int Space, int SpaceL) {
    if (Empty) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A << "(" << nDeep << ")";
    /*Right->Print(0,SpaceL+6);
    if (Right->Empty) cout << endl;
    Left->Print(SpaceL,SpaceL+6);*/
}

/////////////////////////////////////////////////////////
class BTreeDD {
private:
	//bool Empty; ЭТО УХОДИТ! хватит поля nDepth!
	int nDepth;
	int A;
	BTreeDD* Left;
	BTreeDD* Right;
public:
	BTreeDD() { nDepth = -1; }
	BTreeDD(BTreeDD& BT);
	BTreeDD(BTreeDD* pBT);
	~BTreeDD();
	int GetDepth() { return nDepth; }
	bool IsEmpty() { return nDepth<0; }
	void Print() { Print(0,6); }
	bool Yes() { return nDepth<0 || Yes(0,99); }
	bool Add(int Anew);
	bool Del(int AAA); // я делать не буду! ВАМ! на 25-26 апреля
	BTreeDD* ProtoMin();
private:
	void Print(int Space, int SpaceL);
	bool Yes(int nMin, int nMax); // "просится" быть виртуальной...
};
	
/////////////////////////////////////////////////////////
BTreeDD::BTreeDD(BTreeDD& BT) {
	nDepth = BT.nDepth;
	if (nDepth<0) return;
	A = BT.A;
	Left = new BTreeDD(*BT.Left);
	Right = new BTreeDD(*BT.Right);
}

BTreeDD::BTreeDD(BTreeDD* pBT) {
	nDepth = pBT->nDepth;
	if (nDepth<0) return;
	A = pBT->A;
	Left = new BTreeDD(pBT->Left);
	Right = new BTreeDD(pBT->Right);
}

BTreeDD::~BTreeDD() {
	if (nDepth<0) return;
	delete Left;
	delete Right;
}

bool BTreeDD::Add(int Anew) {
	if (nDepth<0) {
		nDepth = 0;
		A = Anew;
		Left = new BTreeDD;
		Right = new BTreeDD;
		return true;
	}
	if (Anew==A) return false;
	if (Anew<A) { if (!Left->Add(Anew))  return false; }
	else        { if (!Right->Add(Anew)) return false; }
	nDepth = max(Left->GetDepth(),Right->GetDepth())+1;
	return true;
}

void BTreeDD::Print (int Space, int SpaceL) {
    if (nDepth<0) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A << "(" << nDepth << ")";
    Right->Print(0,SpaceL+6);
    if (Right->nDepth<0) cout << endl;
    Left->Print(SpaceL,SpaceL+6);
}
	
bool BTreeDD::Yes(int nMin, int nMax) {
	if (nDepth<0) return true;
	if (A<nMin || A>nMax) return false;
	if (!Left->Yes(nMin,A-1)) return false;
	if (!Right->Yes(A+1,nMax)) return false;
	return true;
}

/////////////////////////////////////////////////////////
class AVLTree {
private:
	int nDepth;
	int A;
	AVLTree* Left;
	AVLTree* Right;
public:
	AVLTree() { nDepth = -1; }
	AVLTree(AVLTree& BT);
	AVLTree(AVLTree* pBT);
	~AVLTree();
	int GetDepth() { return nDepth; }
	bool IsEmpty() { return nDepth<0; }
	void Print() { Print(0,6); }
	bool Yes() { return nDepth<0 || Yes(0,99); }
	bool Add(int Anew);
	bool Del(int AAA); // снова - делать не будем...
	AVLTree* ProtoMin();
private:
	void Print(int Space, int SpaceL);
	bool Yes(int nMin, int nMax); // "просится" быть виртуальной...
};

/////////////////////////////////////////////////////////
AVLTree::AVLTree(AVLTree& BT) {
	nDepth = BT.nDepth;
	if (nDepth<0) return;
	A = BT.A;
	Left = new AVLTree(*BT.Left);
	Right = new AVLTree(*BT.Right);
}

AVLTree::AVLTree(AVLTree* pBT) {
	nDepth = pBT->nDepth;
	if (nDepth<0) return;
	A = pBT->A;
	Left = new AVLTree(pBT->Left);
	Right = new AVLTree(pBT->Right);
}

AVLTree::~AVLTree() {
	if (nDepth<0) return;
	delete Left;
	delete Right;
}

bool AVLTree::Add(int Anew) {
	if (nDepth<0) {
		nDepth = 0;
		A = Anew;
		Left = new AVLTree;
		Right = new AVLTree;
		return true;
	}
	if (Anew==A) return false;
	if (Anew<A) { if (!Left->Add(Anew))  return false; }
	else        { if (!Right->Add(Anew)) return false; }
	nDepth = max(Left->GetDepth(),Right->GetDepth())+1;
	return true;
}

void AVLTree::Print (int Space, int SpaceL) {
    if (nDepth<0) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A << "(" << nDepth << ")";
    Right->Print(0,SpaceL+6);
    if (Right->nDepth<0) cout << endl;
    Left->Print(SpaceL,SpaceL+6);
}
	
bool AVLTree::Yes(int nMin, int nMax) {
	// проверяем условие дерева поиска и условие АВЛ - одновременно!
	// так (видимо) быстрее - хотя по-отдельноси "более в духе ООП"
	if (nDepth<0) return true;
	if (A<nMin || A>nMax) return false;
	if (fabs((Left->nDepth)-(Right->nDepth))>=2) return false; 
	if (!Left->Yes(nMin,A-1)) return false;
	if (!Right->Yes(A+1,nMax)) return false;
	return true;
}

/////////////////////////////////////////////////////////
class Tree {
private:
	int nDepth;
	int nKol;
	int A;
	Tree** SubTrees;
public:
	Tree() { nDepth = -1; }
	Tree(int A);
	~Tree() { Destroy(); }
	int GetDepth() { return nDepth; }
	bool IsEmpty() { return nDepth<0; }
	void InitSubTrees(string Str); 
		// с удалением всех ранее имеющихся поддеревьев (если были)
		// считаем, что каждый символ строки имеет код от 20h до 7Ah (т.е. от 32 до 7*16+10=122 включ.)
	Tree* Search(char Ch, bool bL); 
		// ищем поиском-в-глубину по правилам из предыдущего коммента;
		// внимание! возвращаем "просто" указатель на дерево! => для изменения "из пред.уровня" не используем!
		// bL - надо ли требовать, чтобы это был лист (true - надо)
	void Print() { Print(0,3); }
private:
	void Destroy(); // удаляем только поддеревья!
	void Print(int Space, int SpaceL);
};

Tree::Tree(int A) {
	nDepth = 0;
	nKol = 0;
	this->A = A;
}

void Tree::InitSubTrees(string Str) {
	// сначала - удалить все ранее имеющиеся поддеревья (если были)
	Destroy();
	// теперь - само добавление
	nDepth = 1;
	nKol = Str.size();
	SubTrees = NULL;
	if (nKol<=0) return; 
	SubTrees = new Tree*[nKol];
	for (int i=0; i<nKol; i++) {
		char Ch = Str[i];
		int AAA = Ch;
		if (AAA<32 || AAA>122) exit(1);
		AAA -= 32;
		SubTrees[i] = new Tree(AAA);
	}
}

void Tree::Destroy() {
	if (nDepth<0) return;
	for (int i=0; i<nKol; i++) delete SubTrees[i];
	nDepth = 0;
	nKol = 0;
}

void Tree::Print(int Space, int SpaceL) {
    if (nDepth<0) return;
    for (int i=0; i<Space; i++) cout << " ";
    cout.width(3); cout << A;
    for (int i=nKol-1; i>=0; i--) {
		SubTrees[i]->Print((i==nKol-1?0:SpaceL),SpaceL+3);
		if (i>0) cout << endl;
	}
}

Tree* Tree::Search(char Ch, bool bL) {
	if (nDepth<0) return NULL;
	int AAA = Ch-32; if ((AAA == A) && (!bL || nDepth==0)) return this;
	for (int i=0; i<nKol; i++) {
		Tree* tmp = SubTrees[i]->Search(Ch,bL);
		if (tmp!=NULL) return tmp;
	}
	return NULL;
}

/////////////////////////////////////////////////////////
int main(int argc, char** argv) {
	BTreeDD BT; BT.Print(); cout << endl << endl << endl;
	BT.Add(8); //BT.Print(); cout << endl << endl << endl;
	BT.Add(3); //BT.Print(); cout << endl << endl << endl;
	BT.Add(10); //BT.Print(); cout << endl << endl << endl;
	BT.Add(14); //BT.Print(); cout << endl << endl << endl;
	BT.Add(6); //BT.Print(); cout << endl << endl << endl;
	BT.Add(4); //BT.Print(); cout << endl << endl << endl;
	BT.Add(7); //BT.Print(); cout << endl << endl << endl;
	BT.Add(13); //BT.Print(); cout << endl << endl << endl;
	BT.Add(1); BT.Print(); cout << endl << endl << endl;
	BTreeDD BT1(BT); BT1.Print(); 
	if (BT1.Yes()) cout << "yes"; else cout << "no"; cout << endl << endl << endl;
	//
	AVLTree AT; AT.Print(); cout << endl << endl << endl;
	AT.Add(8); //AT.Print(); cout << endl << endl << endl;
	AT.Add(3); //AT.Print(); cout << endl << endl << endl;
	AT.Add(10); //AT.Print(); cout << endl << endl << endl;
	AT.Add(14); //AT.Print(); cout << endl << endl << endl;
	AT.Add(6); //AT.Print(); cout << endl << endl << endl;
	AT.Add(4); //AT.Print(); cout << endl << endl << endl;
	AT.Add(7); //AT.Print(); cout << endl << endl << endl;
	AT.Add(13); //AT.Print(); cout << endl << endl << endl;
	AT.Add(1); AT.Print(); cout << endl << endl << endl;
	if (AT.Yes()) cout << "yes"; else cout << "no"; cout << endl << endl << endl;
	AT.Add(9); AT.Print(); cout << endl << endl << endl;
	if (AT.Yes()) cout << "yes"; else cout << "no"; cout << endl << endl << endl;
	//
	Tree TTT(7); TTT.Print(); cout << endl << endl;
	TTT.InitSubTrees("rtyuiop"); TTT.Print(); cout << endl << endl;
	Tree* pTTT = TTT.Search('y',true); pTTT->InitSubTrees("poiuytr"); TTT.Print(); cout << endl << endl;
	return 0;
}


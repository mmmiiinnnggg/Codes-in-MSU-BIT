#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "ADT.h"

using namespace std;

	void matrix::init(){
        mat=new double*[n];
        for(int i=0;i<n;i++){
            mat[i]=new double[m];
        }
	}

	matrix::matrix(){
	    n=1;m=1;
	    init();
	    mat[0][0]=0;
	}

	matrix::~matrix(){
	    for(int i=0;i<n;i++){
            delete[] mat[i];
	    }
	    delete[] mat;
	}
/*
	void matrix::Print(){
	    for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(j==0) cout<<' '<<'|'<<' '<<mat[i][j]<<' ';
				else cout<<mat[i][j]<<' ';
			}
			cout<<'|';
			cout<<endl;
		}
	}
*/
	matrix::matrix(const matrix& m1){
	    n=m1.n;m=m1.m;
	    init();
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                mat[i][j]=m1.mat[i][j];
            }
	}

    matrix& matrix::operator=(const matrix& m1){
        if(&m1==this){return *this;}
        if(n!=m1.n||m!=m1.m){
            for(int k=0;k<n;k++) delete[] mat[k];
            delete[] mat;
        }
        n=m1.n;m=m1.m;
        init();
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                mat[i][j]=m1.mat[i][j];
            }
        return *this;
    }
//-----------------------------------------------------------------
//----------------------------4.1-----------------------------
//-----------------------------------------------------------------
	matrix::matrix(int n,int m){
		this->n=n;
		this->m=m;
		init();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				mat[i][j]=0.0;
	}

	matrix::matrix(double a){
		n=1;m=1;
		init();
		mat[0][0]=a;
	}

	matrix::matrix(double *s,int m){
		n=1;
		this->m=m;
		init();
		for(int i=0;i<m;i++)
			mat[0][i]=(*s++);
	}

	matrix::matrix(int n,double *s){
		m=1;
		this->n=n;
		init();
		for(int i=0;i<n;i++)
			mat[i][0]=(*s++);
	}

	matrix::matrix(char* S){
	    char *s=S;
	    char *sp=S;
	    int countleftbracket=0;
	    int comma=0;
	    while((*s++)!='}'){
            if(*s==',') comma++;
	    }
	    this->m=comma+1;

	    while((*s++)!='\0'){
            if(*s=='{') countleftbracket++;
	    }
	    this->n=countleftbracket+1;
	    init();

	    int i=-1,j=0;
	    sp++;//from the second '{'
	    while(*sp!='\0'){
            double sum=0;
            while(*sp!='}'){
                if((*sp>='0'&&*sp<='9')||(*sp=='.')){//meet number
                    if(*sp>='0'&&*sp<='9') {sum=(sum*10)+(*sp-'0');sp++;}
                    else{//if(*sp=='.')
                        double sumaftpoi=0;
                        int countaft=0;
                        sp++;
                        while(*sp!=','&&*sp!='}'){
                            sumaftpoi=(sumaftpoi*10)+(*sp-'0');
                            sp++;countaft++;
                        }
                        sumaftpoi/=(pow(10,countaft));
                        sum=sum+sumaftpoi;
                        mat[i][j]=sum;
                    }
                    mat[i][j]=sum;//when no bits after point
                }
                else if(*sp=='{') {i++;j=0;sp++;sum=0;}//change row;
                else {j++;sp++;sum=0;}//(*sp==',') the next element
            }
            sp+=2;//jump to next row
        }
    }

	matrix matrix::identity(int n){
	    matrix m1(n,n);
        for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j) m1.mat[i][j]=1;
				else m1.mat[i][j]=0;
			}
		return m1;
	}

	matrix matrix::diagonal(double *vals,int n){
	    matrix m1(n,n);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j) m1.mat[i][j]=(*vals++);
				else m1.mat[i][j]=0;
			}
		return m1;
	}

	int matrix::rows(){
		return n;
	}

	int matrix::columns(){
		return m;
	}

	void matrix::setval(int i,int j,double val){
	    if(i>=n||j>=m) throw Error(4);
		mat[i-1][j-1]=val;
	}

	matrix matrix::operator*(double scalar){
		matrix m1(n,m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				m1.mat[i][j]=mat[i][j]*scalar;
		return m1;
	}

	void matrix::operator*=(double scalar){
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				mat[i][j]*=scalar;
	}

	matrix& matrix::operator[](int i){
	    if(n==1){
            double temp = mat[0][i-1];
            m=1;init();
            mat[0][0]=temp;
            return *this;
	    }
	    else{
            double *p = new double[m];
            for(int j=0;j<m;j++)
                p[j]=mat[i-1][j];
	        n=1;init();
	        for(int j=0;j<m;j++)
                mat[0][j]=p[j];
            delete p;
            return *this;
	    }
	}

	ostream& operator<<(ostream& s,const matrix &m1){
		for(int i=0;i<m1.n;i++){
			for(int j=0;j<m1.m;j++){
				if(j==0) s<<' '<<'|'<<' '<<m1.mat[i][j]<<' ';
				else s<<m1.mat[i][j]<<' ';
			}
			s<<'|';
			s<<endl;
		}
		return s;
	}
//-----------------------------------------------------------------------------------
//----------------4.2---------------------------------------------------------------
//-----------------------------------------------------------------------------------------
	matrix matrix::operator+(const matrix& m1){
	    if(n!=m1.n||m!=m1.m) throw Error(0);
	    matrix M(n,m);
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                M.mat[i][j]=mat[i][j]+m1.mat[i][j];
        return M;
	}

	void matrix::operator+=(const matrix& m1){
	    if(n!=m1.n||m!=m1.m) throw Error(0);
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                mat[i][j]+=m1.mat[i][j];
	}

	matrix matrix::operator-(const matrix& m1){
	    if(n!=m1.n||m!=m1.m) throw Error(0);
	    matrix M(n,m);
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                M.mat[i][j]=mat[i][j]-m1.mat[i][j];
        return M;
	}

	void matrix::operator-=(const matrix& m1){
	    if(n!=m1.n||m!=m1.m) throw Error(0);
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                mat[i][j]-=m1.mat[i][j];
	}

	double matrix::times(const matrix m1,const matrix m2,int i,int j){
	    double sum=0;
	    for(int k=0;k<m1.m;k++){
            sum+=m1.mat[i][k]*m2.mat[k][j];
	    }
	    return sum;
	}

	matrix matrix::operator*(const matrix& m1){
	    if(m!=m1.n) throw Error(0);
	    matrix M(n,m1.m);
	    for(int i=0;i<n;i++)
            for(int j=0;j<m1.m;j++)
                M.mat[i][j]=times(*this,m1,i,j);
        return M;
	}

	void matrix::operator*=(const matrix& m1){
	    if(m!=n) throw Error(0);
	    matrix M(n,m1.m);
	    for(int i=0;i<n;i++)
            for(int j=0;j<m1.m;j++)
                mat[i][j]=times(*this,m1,i,j);
	}

	matrix matrix::operator-(){
	    matrix M(*this);
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                M.mat[i][j]*=-1;
        return M;
	}

	bool matrix::operator==(const matrix& m1){
	    if(n!=m1.n||m!=m1.m) throw Error(0);
	    bool sign=true;
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(fabs(mat[i][j]-m1.mat[i][j])>EPS) sign=false;
        return sign;
	}

	bool matrix::operator!=(const matrix& m1){
	    if(n!=m1.n||m!=m1.m) throw Error(0);
	    bool sign=true;
	    for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(fabs(mat[i][j]-m1.mat[i][j])<=EPS) sign=false;
        return sign;
	}

	matrix matrix::operator|(const matrix& m1){
	    if(n!=m1.n) throw Error(0);
	    int column=m+m1.m;
	    matrix M(n,column);
	    for(int i=0;i<n;i++)
            for(int j=0;j<column;j++){
                if(j<m) M.mat[i][j]=mat[i][j];
                else M.mat[i][j]=m1.mat[i][j-m];
            }
        return M;
	}

	matrix matrix::operator/(const matrix& m1){
	    if(m!=m1.m) throw Error(0);
	    int line=n+m1.n;
	    matrix M(line,m);
	    for(int i=0;i<line;i++)
            for(int j=0;j<m;j++){
                if(i<n) M.mat[i][j]=mat[i][j];
                else M.mat[i][j]=m1.mat[i-n][j];
            }
        return M;
	}
//--------------------------------------------------------------------------
//-------------------4.3----------------------------------------------------
//---------------------------------------------------------------------------
    void matrix::change_and_decline(int i){
        double Max=0;
        int imax=0;
        //find the biggest element of i-column from i-row down to bottom
        for(int k=i;k<n;k++){
            if(fabs(mat[k][i])>(Max+EPS)){
                imax=k;
                Max=mat[k][i];
            }
        }
        //change the rows
        double temp;
        for(int j=i;j<m;j++){
            temp=mat[i][j];
            mat[i][j]=mat[imax][j];
            mat[imax][j]=temp;
        }
        //decline to down triangle matrix
        for(int p=i+1;p<n;p++){
            double R=mat[p][i]/mat[i][i];//ratio
            for(int q=i;q<m;q++){
                mat[p][q]-=R*mat[i][q];
            }
        }
        //eliminate the small value;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(fabs(mat[i][j])<EPS)
                    mat[i][j]=0;
    }

    matrix& matrix::operator~(){//inverse matrix
        if(n!=m) throw Error(1);
        matrix I=identity(n);
        matrix Wide=(*this|I);
        //conversion to down triangle matrix
        for(int i=0;i<n;i++){
            Wide.change_and_decline(i);
        }
        //let diagonal element be 1
        for(int i=0;i<n;i++){
            double div=Wide.mat[i][i];
            for(int j=i;j<Wide.m;j++){
                Wide.mat[i][j]/=div;
            }
        }
        //turn down triangle to identity
        for(int i=m-1;i>=0;i--){//every column from right to left
            for(int p=i-1;p>=0;p--){//calculate R and minus every line from line i
                double R=Wide.mat[p][i]/Wide.mat[i][i];//ratio
                for(int q=Wide.m-1;q>=0;q--){//minus every element from line i
                    Wide.mat[p][q]-=(R*Wide.mat[i][q]);
                }
            }
        }
        //Reduce to reverse matrix itself
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                mat[i][j]=Wide.mat[i][j+m];
            }
        return *this;
    }

	double matrix::determinant(){
	    if(n!=m) throw Error(1);
	    matrix MM(*this);
	    for(int i=0;i<n;i++){
            MM.change_and_decline(i);

        }
        double RES=1;
        for(int j=0;j<n;j++){
            RES*=MM.mat[j][j];
        }
	    return RES;
	}

	matrix matrix::solve(){
	    if((n+1)!=m) throw Error(2);
	    matrix MM(*this);
	    for(int i=0;i<n-1;i++){
            MM.change_and_decline(i);
        }

        double RES=1;
        for(int j=0;j<n;j++){
            RES*=MM.mat[j][j];
        }

        //when determinant equal 0 then there are inf solutions
        if(fabs(RES)<EPS){
            throw Error(3);
        }

        double Solution[n]={0};
        for(int i=n-1;i>=0;i--){
            double temp=0;
            for(int j=n-1;j>i;j--){//calculate temp
                temp+=Solution[j]*MM.mat[i][j];
            }
            Solution[i]=(MM.mat[i][m-1]-temp)/MM.mat[i][i];//xi=(bi-temp)/aii
        }
        //write into row-matrix
        matrix Final(n,Solution);
        return Final;
	}

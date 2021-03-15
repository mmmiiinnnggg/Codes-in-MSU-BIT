#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAX_n 1000

using namespace std;

using namespace std;
class complex{
public:
	double re,im;
	complex(double re=0,double im=0){
		this->re = re;
		this->im = im;
	}

	complex operator+(complex t){
		return complex(re+t.re,im+t.im);
    }

    complex operator-(complex t){
    	return complex(re-t.re,im-t.im);
    }

	complex operator*(complex t){
		return complex(re*t.re-im*t.im,re*t.im+im*t.re);
	}

	complex operator/(complex t){
		return complex((re*t.re+im*t.im)/(t.re*t.re+t.im*t.im),(im*t.re-re*t.im)/(t.re*t.re+t.im*t.im));
	}

	double mudulo(){
		return sqrt(re*re+im*im);
	}

	void print()const{
		cout<<"re="<<re<<" im="<<im<<endl;
	}
};

complex A[MAX_n][MAX_n];
complex LU[MAX_n][MAX_n];
complex b[MAX_n];
complex y[MAX_n];
complex x[MAX_n];
int P[MAX_n];
int n;

int makeIndex(int i, int j){
    return (j*(j-1))/2+i;
}

int pow10(int power){
    int pro=1;
    int i=1;
    while(i<=power){
        pro*=10;
        i++;
    }
    return pro;
}

void make_lu_upgrade_complex(){
    //initialization of P
    for(int i=1; i<=n; i++)
        P[i]=i;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            if(i==j) LU[i][j]=1;
            else LU[i][j]=0;
        }

    for(int j=1; j<=n-1; j++){
        double maxelement=A[j][j].mudulo();
        int maxj=j;
        for(int m=j+1; m<=n; m++){
            if(maxelement<A[m][j].mudulo()){
                maxelement=A[m][j].mudulo();
                maxj=m;
            }
        }
        //interchange of L U and P
        complex tmpline[MAX_n];
        int tmp;
        for(int m=1; m<=n; m++){
            tmpline[m]=A[j][m];
            A[j][m]=A[maxj][m];
            A[maxj][m]=tmpline[m];
        }
        for(int m=1; m<=n; m++){
            tmpline[m]=LU[j][m];
            LU[j][m]=LU[maxj][m];
            LU[maxj][m]=tmpline[m];
        }

        tmp=P[j];
        P[j]=P[maxj];
        P[maxj]=tmp;

        //The main body of algorithm
        for(int i=j+1; i<=n; i++){
            LU[i][j]=A[i][j]/A[j][j];
            for(int k=j; k<=n; k++)
                A[i][k]=A[i][k]-LU[i][j]*A[j][k];
        }
    }

    for(int i=1; i<=n; i++)
        for(int j=i; j<=n; j++)
            LU[i][j]=A[i][j];
}

void recognizeReA(complex A[MAX_n][MAX_n], FILE *fp1){
    //recognize ReA
    char c;
    string str;
    c=fgetc(fp1);
    while(c!='[') c=fgetc(fp1);
    int mat_i=1;
    int countn=0;
    int count_1_line;
    int countline=0;
    while(c!=']'){
        while(c==' '||c=='\n') c=fgetc(fp1);
        if(c==',') break;
        int mat_j=1;
        while(c!=';'){
            int i=0;
            int doti=0;
            int sign=1;
            double num=0;
            double num1=0;
            double num2=0;
            if(mat_i==1||(mat_i!=1&&mat_j!=1)) c=fgetc(fp1);
            while(c!=' '&&c!=';'&&c!=']'){
                if(c=='.') doti=i;
                str[i++]=c;
                c=fgetc(fp1);
            }

            int length=i-1;

            if(doti){
                int index2=doti+1;
                int power2=length-doti-1;
                while(index2!=i){
                num2 = num2 + ((str[index2++]-'0')*pow10(power2));
                power2--;
                }
                num2/=pow10(length-doti);
            }

            int power1;
            int index1;
            int typenum;
            if(str[0]=='-') sign=-1;
            if(doti>0&&sign>0){power1=doti-1;index1=0;typenum=1;}
            if(doti>0&&sign<0){power1=doti-2;index1=1;typenum=1;}
            if(doti==0&&sign>0){power1=i-1;index1=0;typenum=2;}
            if(doti==0&&sign<0){power1=i-2;index1=1;typenum=2;}

            if(typenum==1)
                while(index1!=doti){
                    num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                    power1--;
                }
            else while(index1!=i){
                    num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                    power1--;
                }

            num=(num1+num2)*sign;
            A[mat_i][mat_j++].re=num;

            if(c==';'||c==']'){
                countn++;
                mat_i++;
                c=fgetc(fp1);

                //judge if the lengths of lines are equal
                if(mat_i==2) count_1_line=mat_j-1;
                countline=mat_j-1;

                break;
            }
        }

        if(countline!=count_1_line){
            cout<<"ReA is not a matrix";
            exit(0);
        }
    }

    n=countn;

    if(n!=countline){
        cout<<"Matrix A is not a square matrix";
        exit(0);
    }
}

void recognizeImA(complex A[MAX_n][MAX_n], FILE *fp1){
    //recognize ImA
    char c;
    string str;
    while(c!='[') c=fgetc(fp1);
    int mat_i=1;
    int countn=0;
    int count_1_line;
    int countline=0;
    while(c!=']'){
        while(c==' '||c=='\n') c=fgetc(fp1);
        if(c==')') break;
        int mat_j=1;
        while(c!=';'){
            int i=0;
            int doti=0;
            int sign=1;
            double num=0;
            double num1=0;
            double num2=0;
            if(mat_i==1||(mat_i!=1&&mat_j!=1)) c=fgetc(fp1);
            while(c!=' '&&c!=';'&&c!=']'){
                if(c=='.') doti=i;
                str[i++]=c;
                c=fgetc(fp1);
            }

            int length=i-1;

            if(doti){
                int index2=doti+1;
                int power2=length-doti-1;
                while(index2!=i){
                num2 = num2 + ((str[index2++]-'0')*pow10(power2));
                power2--;
                }
                num2/=pow10(length-doti);
            }

            int power1;
            int index1;
            int typenum;
            if(str[0]=='-') sign=-1;
            if(doti>0&&sign>0){power1=doti-1;index1=0;typenum=1;}
            if(doti>0&&sign<0){power1=doti-2;index1=1;typenum=1;}
            if(doti==0&&sign>0){power1=i-1;index1=0;typenum=2;}
            if(doti==0&&sign<0){power1=i-2;index1=1;typenum=2;}

            if(typenum==1)
                while(index1!=doti){
                    num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                    power1--;
                }
            else while(index1!=i){
                    num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                    power1--;
                }

            num=(num1+num2)*sign;
            A[mat_i][mat_j++].im=num;

            if(c==';'||c==']'){
                countn++;
                mat_i++;
                c=fgetc(fp1);

                //judge if the lengths of lines are equal
                if(mat_i==2) count_1_line=mat_j-1;
                countline=mat_j-1;

                break;
            }
        }

        if(countline!=count_1_line){
            cout<<"ImA is not a matrix";
            exit(0);
        }
    }

    if(n!=countline){
        cout<<"Matrix A is not a square matrix";
        exit(0);
    }
}

void recognizeReb(complex b[MAX_n], FILE *fp2){
    char c;
    string str;
    //input of Reb
    c=fgetc(fp2);
    while(c!='[') c=fgetc(fp2);
    int mat_i=1;
    int b_n;
    c=fgetc(fp2);
    while(c!=']'){
        while(c==' ') c=fgetc(fp2);
        //if(c==';') break;
        int i=0;
        int doti=0;
        int sign=1;
        double num=0;
        double num1=0;
        double num2=0;
        while(c!=';'&&c!=']'){
            if(c=='.') doti=i;
            str[i++]=c;
            c=fgetc(fp2);
        }

        int length=i-1;

        if(doti){
            int index2=doti+1;
            int power2=length-doti-1;
            while(index2!=i){
            num2 = num2 + ((str[index2++]-'0')*pow10(power2));
            power2--;
            }
            num2/=pow10(length-doti);
        }

        int power1;
        int index1;
        int typenum;
        if(str[0]=='-') sign=-1;
        if(doti>0&&sign>0){power1=doti-1;index1=0;typenum=1;}
        if(doti>0&&sign<0){power1=doti-2;index1=1;typenum=1;}
        if(doti==0&&sign>0){power1=i-1;index1=0;typenum=2;}
        if(doti==0&&sign<0){power1=i-2;index1=1;typenum=2;}

        if(typenum==1)
            while(index1!=doti){
                num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                power1--;
            }
        else while(index1!=i){
                num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                power1--;
            }

        num=(num1+num2)*sign;
        b[mat_i++].re=num;

        if(c==';') c=fgetc(fp2);
        if(c==']') break;
    }

    c=fgetc(fp2);
    b_n=mat_i-1;

    if(n!=b_n){
        cout<<"Matrix A and vector b are not corresponded";
        exit(0);
    }
}

void recognizeImb(complex b[MAX_n], FILE *fp2){
    //recognize Imb
    char c;
    string str;
    while(c!='[') c=fgetc(fp2);
    int mat_i=1;
    c=fgetc(fp2);
    while(c!=']'){
        while(c==' ') c=fgetc(fp2);
        //if(c==';') break;
        int i=0;
        int doti=0;
        int sign=1;
        double num=0;
        double num1=0;
        double num2=0;
        while(c!=';'&&c!=']'){
            if(c=='.') doti=i;
            str[i++]=c;
            c=fgetc(fp2);
        }

        int length=i-1;

        if(doti){
            int index2=doti+1;
            int power2=length-doti-1;
            while(index2!=i){
            num2 = num2 + ((str[index2++]-'0')*pow10(power2));
            power2--;
            }
            num2/=pow10(length-doti);
        }

        int power1;
        int index1;
        int typenum;
        if(str[0]=='-') sign=-1;
        if(doti>0&&sign>0){power1=doti-1;index1=0;typenum=1;}
        if(doti>0&&sign<0){power1=doti-2;index1=1;typenum=1;}
        if(doti==0&&sign>0){power1=i-1;index1=0;typenum=2;}
        if(doti==0&&sign<0){power1=i-2;index1=1;typenum=2;}

        if(typenum==1)
            while(index1!=doti){
                num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                power1--;
            }
        else while(index1!=i){
                num1 = num1 + ((str[index1++]-'0')*pow10(power1));
                power1--;
            }

        num=(num1+num2)*sign;
        b[mat_i++].im=num;

        if(c==';') c=fgetc(fp2);
        if(c==']') break;
    }
}

void SolveSystem(){
    for(int i=1; i<=n; i++){
        complex tmp(0,0);
        for(int j=1; j<i; j++)
            tmp=tmp+LU[i][j]*y[j];
        y[i]=b[i]-tmp;
    }

    for(int i=n; i>=1; i--){
        complex tmp(0,0);
        for(int j=i+1; j<=n; j++)
            tmp=tmp+LU[i][j]*x[j];
        x[i]=(y[i]-tmp)/LU[i][i];
    }
}

int main()
{
    FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
    if((fp1=fopen("Amat12.m","r"))==NULL){
        printf("Cannot open AMat3\n");
        exit(0);
    }
    if((fp2=fopen("bvec12.m","r+"))==NULL){
        printf("Cannot open bvec3\n");
        exit(0);
    }
    if((fp3=fopen("xvec12.m","w+"))==NULL){
        printf("Cannot open xvec3\n");
        exit(0);
    }

    recognizeReA(A,fp1);
    recognizeImA(A,fp1);
    recognizeReb(b,fp2);
    recognizeImb(b,fp2);

    if( ((fp4=fopen("Lmat12.m","r"))!=NULL) && ((fp5=fopen("Umat12.m","r"))!=NULL)){
        recognizeReA(LU,fp4);
        recognizeImA(LU,fp4);
        complex L[MAX_n];
        for(int i=1; i<=n; i++)
            for(int j=1; j<i; j++)
                L[makeIndex(i,j)]=LU[i][j];

        recognizeReA(LU,fp5);
        recognizeImA(LU,fp5);
        for(int i=1; i<=n; i++)
            for(int j=1; j<i; j++)
                LU[i][j]=L[makeIndex(i,j)];
    }

    else{
        if((fp4=fopen("Lmat12.m","w+"))==NULL){
            cout<<"Cannot open Lmat12\n";
            exit(0);
        }

        if((fp5=fopen("Umat12.m","w+"))==NULL){
            cout<<"Cannot open Umat12\n";
            exit(0);
        }

        if((fp6=fopen("Pmat12.m","w+"))==NULL){
            cout<<"Cannot open Pmat12\n";
            exit(0);
        }

        make_lu_upgrade_complex();

        fputs("L = complex\n  ",fp4);
        fputs("[(",fp4);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i==j) fprintf(fp4,"%d ",1);
                else if(i<j) fprintf(fp4,"%d ",0);
                else fprintf(fp4,"%f ",LU[i][j].re);
            }
            if(i!=n) fprintf(fp4,"%d;\n  ",0);
            else fprintf(fp4,"%d],[",1);
        }

        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i==j) fprintf(fp4,"%d ",0);
                else if(i<j) fprintf(fp4,"%d ",0);
                else fprintf(fp4,"%f ",LU[i][j].im);
            }
            if(i!=n) fprintf(fp4,"%d;\n  ",0);
            else fprintf(fp4,"%d]);",0);
        }

        fputs("U = complex\n  ",fp5);
        fputs("([",fp5);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i<=j) fprintf(fp5,"%f ",LU[i][j].re);
                else fprintf(fp5,"%d ",0);
            }
            if(i!=n) fprintf(fp5,"%f;\n  ",LU[i][n].re);
            else fprintf(fp5,"%f],[",LU[n][n].re);
        }

        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i<=j) fprintf(fp5,"%f ",LU[i][j].im);
                else fprintf(fp5,"%d ",0);
            }
            if(i!=n) fprintf(fp5,"%f;\n  ",LU[i][n].im);
            else fprintf(fp5,"%f]);",LU[n][n].im);
        }

        fputs("P = ...\n  ",fp6);
        fputs("[",fp6);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(j==P[i]) fprintf(fp6,"%d ",1);
                else fprintf(fp6,"%d ",0);
            }
            if(i!=n&&n==P[i]) fprintf(fp6,"%d;\n  ",1);
            else if(i!=n&&n!=P[i]) fprintf(fp6,"%d;\n  ",0);
            else if(i==n&&n==P[i]) fprintf(fp6,"%d];",1);
            else fprintf(fp6,"%d];",0);
        }
    }

    SolveSystem();

    fputs("x = complex(  ",fp3);
        fputs("[",fp3);
        for(int i=1; i<=n; i++){
            if(i==n) fprintf(fp3,"%f],",x[i].re);
            else fprintf(fp3,"%f; ",x[i].re);
        }

        fputs("[",fp3);
        for(int i=1; i<=n; i++){
            if(i==n) fprintf(fp3,"%f])",x[i].im);
            else fprintf(fp3,"%f; ",x[i].im);
        }

    cout<<"Success! Please check the answer in Amat12.m, bvec12.m and xvec12.m"<<endl;

    return 0;
}

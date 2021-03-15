#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAX_n 100

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

	complex conju(){
	    complex CC(0,0);
	    CC.re=re;
	    CC.im=-im;
	    return CC;
	}

	complex SQRT(){
	    re=sqrt((re+this->mudulo())/2);
	    im=sqrt((this->mudulo()-re)/2);
	    return *this;
	}

	void print()const{
		cout<<"re="<<re<<" im="<<im<<endl;
	}
};

complex A[MAX_n][MAX_n];
complex Q[MAX_n][MAX_n];
complex R[MAX_n];
complex b[MAX_n];
complex y[MAX_n];
complex x[MAX_n];
complex p[MAX_n];
int n;
int M=100;


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

void make_qr_complex(){
    for(int j=1; j<=n; j++){
        //p_j(0)=a_j
        for(int z=1; z<=n; z++) p[z]=A[z][j];

        for(int m=1; m<=M; m++){
            for(int i=1; i<=j-1; i++){
                //p_j(m)=p_j(m-1)-q_i(q_i*p_j(m-1))
                complex val(0,0);
                for(int z=1; z<=n; z++)
                    val=val+(Q[z][i].conju())*p[z];
                for(int z=1; z<=n; z++){
                    p[z]=p[z]-Q[z][i]*val;
                }
            }
        }

        complex nopma(0,0);
        for(int z=1; z<=n; z++)
            nopma.re+=p[z].mudulo()*p[z].mudulo();
        nopma.re=sqrt(nopma.re);

        for(int z=1; z<=n; z++)
            Q[z][j]=p[z]/nopma;

        //find R
        for(int k=1; k<=j; k++){
            complex tmp(0,0);
            for(int z=1; z<=n; z++)
               tmp=tmp+(Q[z][k].conju())*A[z][j];
            R[makeIndex(k,j)]=tmp;
        }
    }
}


void recognizeReA(complex A[MAX_n][MAX_n], FILE *fp1, int isQorQ){
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
            cout<<"A is not a matrix";
            exit(0);
        }
    }

    n=countn;

    if(n!=countline){
        cout<<"Matrix A is not a square matrix";
        exit(0);
    }

    if(!isQorQ){
        for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++)
            if(A[i][j].re!=A[j][i].re){
                cout<<"Matrix ReA is not symmetric matrix";
                exit(0);
            }
    }

}

void recognizeImA(complex A[MAX_n][MAX_n], FILE *fp1, int isQorR){
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

    if(!isQorR){
       for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++)
            if(A[i][j].im!=(-A[j][i].im)){
                cout<<"Matrix ImA is not symmetric matrix";
                exit(0);
            }
    }

}

void recognizeb(FILE *fp2){
    //input of b
    char c;
    string str;
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
        b[mat_i++]=num;

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
    //gauss method

    //transpose Q: Q^-1=Q*
    complex tmpval(0,0);
    for(int i=1; i<=n; i++)
        for(int j=1; j<i; j++){
            tmpval=Q[i][j];
            Q[i][j]=Q[j][i];
            Q[j][i]=tmpval;
            Q[i][j]=Q[i][j].conju();
            Q[j][i]=Q[j][i].conju();
        }

    //y=Q-1*b
    for(int i=1; i<=n; i++){
        complex tmp(0,0);
        for(int j=1; j<=n; j++)
            tmp=tmp+Q[i][j]*b[j];
        y[i]=tmp;
    }

    //Rx=y
    for(int i=n; i>=1; i--){
        complex tmp(0,0);
        for(int j=i+1; j<=n; j++)
            tmp=tmp+R[makeIndex(i,j)]*x[j];
        x[i]=(y[i]-tmp)/R[makeIndex(i,i)];
    }
}


int main()
{
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    if((fp1=fopen("Amat13.m","r"))==NULL){
        printf("Cannot open AMat10\n");
        exit(0);
    }
    if((fp2=fopen("bvec13.m","r+"))==NULL){
        printf("Cannot open bvec10\n");
        exit(0);
    }

    if((fp3=fopen("xvec13.m","r+"))==NULL){
        printf("Cannot open xvec10\n");
        exit(0);
    }

    recognizeReA(A,fp1,0);
    recognizeImA(A,fp1,0);
    recognizeReb(b,fp2);
    recognizeImb(b,fp2);

    if( ((fp4=fopen("Qmat13.m","r"))!=NULL) && ((fp5=fopen("Rmat13.m","r"))!=NULL) ){
        recognizeReA(Q,fp4,1);
        recognizeImA(Q,fp4,1);
        complex RR[MAX_n][MAX_n];
        recognizeReA(RR,fp5,1);
        recognizeImA(RR,fp5,1);
        for(int i=1; i<=n; i++)
            for(int j=i; j<=n; j++){
                R[makeIndex(i,j)]=RR[i][j];
            }
    }

    else{
        if((fp4=fopen("Qmat13.m","w+"))==NULL){
            printf("Cannot open Qmat11\n");
            exit(0);
        }

        if((fp5=fopen("Rmat13.m","w+"))==NULL){
            printf("Cannot open Rmat11\n");
            exit(0);
        }

        make_qr_complex();

        fputs("Q = complex(",fp4);
        fputs("[",fp4);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                fprintf(fp4,"%f ",Q[i][j]);
            }
            if(i!=n) fprintf(fp4,"%f;\n  ",Q[i][n]);
            else fprintf(fp4,"%f],",Q[n][n]);
        }

        fputs("[",fp4);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                fprintf(fp4,"%f ",Q[i][j]);
            }
            if(i!=n) fprintf(fp4,"%f;\n  ",Q[i][n]);
            else fprintf(fp4,"%f]);",Q[n][n]);
        }

        fputs("R = complex(",fp5);
        fputs("[",fp5);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i>j) fprintf(fp5,"%d ",0);
                else fprintf(fp5,"%f ",R[makeIndex(i,j)]);
            }
            if(i!=n) fprintf(fp5,"%f;\n  ",R[makeIndex(i,n)]);
            else fprintf(fp5,"%f],",R[makeIndex(n,n)]);
        }

        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i>j) fprintf(fp5,"%d ",0);
                else fprintf(fp5,"%f ",R[makeIndex(i,j)]);
            }
            if(i!=n) fprintf(fp5,"%f;\n  ",R[makeIndex(i,n)]);
            else fprintf(fp5,"%f]);",R[makeIndex(n,n)]);
        }
    }

    SolveSystem();

    fputs("x = complex(",fp3);
        fputs("[",fp3);
        for(int i=1; i<=n; i++){
            if(i==n) fprintf(fp3,"%f],",x[i].re);
            else fprintf(fp3,"%f; ",x[i].re);
        }

        fputs("[",fp3);
        for(int i=1; i<=n; i++){
            if(i==n) fprintf(fp3,"%f]);",x[i].im);
            else fprintf(fp3,"%f; ",x[i].im);
        }

    cout<<"Success! Please check the answer in Amat13.m, bvec13.m, Qmat13.m, Rmat13.m and xvec13.m"<<endl;

    return 0;
}

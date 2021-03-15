#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAX_n 100

using namespace std;
double A[MAX_n][MAX_n];
double C[MAX_n];
double b[MAX_n];
double y[MAX_n];
double x[MAX_n];
int n;


int makeIndex(int i, int j){
    return (i*(i-1))/2+1+j;
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

void make_chol(){
    for(int k=1; k<=n; k++){
        double tmp1=0;
        for(int j=1; j<=k-1; j++)
            tmp1+=C[makeIndex(k,j)]*C[makeIndex(k,j)];
        double VAL=A[k][k]-tmp1;
        if(!VAL){
            cout<<"The Matrix A is not positive definite";
            exit(0);
        }
        C[makeIndex(k,k)]=sqrt(VAL);

        for(int i=k+1; i<=n; i++){
            double tmp2=0;
            for(int j=1; j<=k-1; j++)
                tmp2+=C[makeIndex(i,j)]*C[makeIndex(k,j)];
            C[makeIndex(i,k)]=(A[i][k]-tmp2)/C[makeIndex(k,k)];
        }
    }
}

void recognizeA(double A[MAX_n][MAX_n], FILE *fp1, int isA){
    //input of A
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
        if(c==';') break;
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
            A[mat_i][mat_j++]=num;

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

    c=fgetc(fp1);
    n=countn;

    if(n!=countline){
        cout<<"Matrix A is not a square matrix";
        exit(0);
    }

    if(isA){
        for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++)
            if(A[i][j]!=A[j][i]){
                cout<<"Matrix A is not symmetric matrix"<<endl;
                exit(0);
            }
    }
}

void recognizeb(double b[MAX_n], FILE *fp2){
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

void SolveSystem(){
    //gauss method
    for(int i=1; i<=n; i++){
        double tmp=0;
        for(int j=1; j<i; j++)
            tmp+=C[makeIndex(i,j)]*y[j];
        y[i]=(b[i]-tmp)/C[makeIndex(i,i)];
    }

    for(int i=n; i>=1; i--){
        double tmp=0;
        for(int j=i+1; j<=n; j++)
            tmp+=C[makeIndex(j,i)]*x[j];
        x[i]=(y[i]-tmp)/C[makeIndex(i,i)];
    }
}

int main()
{
    FILE *fp1, *fp2, *fp3, *fp4;
    if((fp1=fopen("Amat7.m","r"))==NULL){
        printf("Cannot open AMat7\n");
        exit(0);
    }
    if((fp2=fopen("bvec7.m","r+"))==NULL){
        printf("Cannot open bvec7\n");
        exit(0);
    }

    if((fp3=fopen("xvec7.m","r+"))==NULL){
        printf("Cannot open xvec7\n");
        exit(0);
    }

    recognizeA(A,fp1,1);
    recognizeb(b,fp2);

    if((fp4=fopen("Cmat7.m","r+"))!=NULL){
        double CC[MAX_n][MAX_n];
        recognizeA(CC,fp4,0);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=i; j++){
                C[makeIndex(i,j)]=CC[i][j];
            }

    }

    else{
        if((fp4=fopen("Cmat7.m","w+"))==NULL){
            cout<<"Cannot open Cmat6\n";
            exit(0);
        }

        make_chol();

        fputs("C = ...\n  ",fp4);
        fputs("[",fp4);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i<j) fprintf(fp4,"%d ",0);
                else fprintf(fp4,"%f ",C[makeIndex(i,j)]);
            }
            if(i!=n) fprintf(fp4,"%d;\n  ",0);
            else fprintf(fp4,"%f];",C[makeIndex(n,n)]);
        }
    }

    SolveSystem();

    fputs("x = ...\n  ",fp3);
        fputs("[",fp3);
        for(int i=1; i<=n; i++){
            if(i==n) fprintf(fp3,"%f];",x[i]);
            else fprintf(fp3,"%f; ",x[i]);
        }

    cout<<"Success! Please check the answer in Amat7.m, bvec7.m, Cmat7.m and xvec7.m"<<endl;

    return 0;
}

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAX_n 1000

using namespace std;
double A[MAX_n][MAX_n];
double C[MAX_n];
int n;

int makeIndex(int i, int j){
    return (i*(i-1))/2+j;
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

void recognize(FILE *fp1){
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

    for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++)
            if(A[i][j]!=A[j][i]){
                cout<<"Matrix A is not symmetric matrix";
                exit(0);
            }
}

int main()
{
    FILE *fp1, *fp2;
    if((fp1=fopen("Amat6.m","r"))==NULL){
        printf("Cannot open AMat6\n");
        exit(0);
    }
    if((fp2=fopen("Cmat6.m","w+"))==NULL){
        printf("Cannot open CMat6\n");
        exit(0);
    }

    recognize(fp1);
    make_chol();

    fputs("C = ...\n  ",fp2);
    fputs("[",fp2);
    for(int i=1; i<=n; i++){
        for(int j=1; j<n; j++){
            if(i<j) fprintf(fp2,"%d ",0);
            else fprintf(fp2,"%f ",C[makeIndex(i,j)]);
        }
        if(i!=n) fprintf(fp2,"%d;\n  ",0);
        else fprintf(fp2,"%f];",C[makeIndex(n,n)]);
    }

    cout<<"Success! Please check the answer in Amat6.m and Cmat6.m"<<endl;

    return 0;
}

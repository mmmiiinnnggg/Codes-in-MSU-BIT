#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAX_n 10000

using namespace std;
double A[MAX_n][MAX_n];
double LU[MAX_n][MAX_n];
int n;
double epsilon=0.0001;

int pow10(int power){
    int pro=1;
    int i=1;
    while(i<=power){
        pro*=10;
        i++;
    }
    return pro;
}

void make_lu(){
    for(int j=1; j<=n-1; j++){
        for(int i=j+1; i<=n; i++){
            if(fabs(A[j][j])<epsilon){
                cout<<"The matrix is not strict regular"<<endl;
               exit(0);
            }
            LU[i][j]=A[i][j]/A[j][j];
            for(int k=j; k<=n; k++)
                A[i][k]-=LU[i][j]*A[j][k];
        }
    }

    for(int i=1; i<=n; i++)
        for(int j=i; j<=n; j++)
            LU[i][j]=A[i][j];
}

void recoginze(double A[MAX_n][MAX_n],FILE *fp1){
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
}

int main()
{
    FILE *fp1, *fp2, *fp3;
    if((fp1=fopen("Amat1.m","r"))==NULL){
        printf("Cannot open AMat1\n");
        exit(0);
    }
    if((fp2=fopen("Lmat1.m","w+"))==NULL){
        printf("Cannot open LMat1\n");
        exit(0);
    }
    if((fp3=fopen("Umat1.m","w+"))==NULL){
        printf("Cannot open UMat1\n");
        exit(0);
    }

    recoginze(A,fp1);
    make_lu();

    fputs("L = ...\n  ",fp2);
    fputs("[",fp2);
    for(int i=1; i<=n; i++){
        for(int j=1; j<n; j++){
            if(i==j) fprintf(fp2,"%d ",1);
            else if(i<j) fprintf(fp2,"%d ",0);
            else fprintf(fp2,"%f ",LU[i][j]);
        }
        if(i!=n) fprintf(fp2,"%d;\n  ",0);
        else fprintf(fp2,"%d];",1);
    }

    fputs("U = ...\n  ",fp3);
    fputs("[",fp3);
    for(int i=1; i<=n; i++){
        for(int j=1; j<n; j++){
            if(i<=j) fprintf(fp3,"%f ",LU[i][j]);
            else fprintf(fp3,"%d ",0);

        }
        if(i!=n) fprintf(fp3,"%f;\n  ",LU[i][n]);
        else fprintf(fp3,"%f];",LU[n][n]);
    }

    cout<<"Success! Please check the answer in Lmat1.m and Umat1.m"<<endl;

    return 0;
}

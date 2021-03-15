#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAX_n 600000

using namespace std;
float A[1100][1100];
float LU[1100][1100];
float b[1100];
float y[1100];
float x[1100];
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

void make_lu(){
    for(int j=1; j<=n-1; j++){
        cout<<"making lu... "<<endl;
        for(int i=j+1; i<=n; i++){
            LU[i][j]=A[i][j]/A[j][j];
            for(int k=j; k<=n; k++)
                A[i][k]-=LU[i][j]*A[j][k];
        }
    }

    for(int i=1; i<=n; i++)
        for(int j=i; j<=n; j++)
            LU[i][j]=A[i][j];
}

void recognizeA(float A[1100][1100], FILE *fp1){
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
}

void recognizeb(float b[1100], FILE *fp2){
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
    //solve
    for(int i=1; i<=n; i++){
        double tmp=0;
        for(int j=1; j<i; j++)
            tmp+=LU[i][j]*y[j];
        y[i]=b[i]-tmp;
    }

    for(int i=n; i>=1; i--){
        double tmp=0;
        for(int j=i+1; j<=n; j++)
            tmp+=LU[i][j]*x[j];
        x[i]=(y[i]-tmp)/LU[i][i];
    }
}

int main()
{
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;
    if((fp1=fopen("Amat5.m","r"))==NULL){
        printf("Cannot open AMat5\n");
        exit(0);
    }
    if((fp2=fopen("bvec5.m","r+"))==NULL){
        printf("Cannot open bvec5\n");
        exit(0);
    }
    if((fp3=fopen("xvec5.m","w+"))==NULL){
        printf("Cannot open xvec5\n");
        exit(0);
    }

    recognizeA(A,fp1);
    recognizeb(b,fp2);

    /*if( ((fp4=fopen("Lmat5.m","r"))!=NULL) && ((fp5=fopen("Umat5.m","r"))!=NULL)){
        recognizeA(LU,fp4);
        double L[MAX_n];
        for(int i=1; i<=n; i++)
            for(int j=1; j<i; j++)
                L[makeIndex(i,j)]=LU[i][j];
        recognizeA(LU,fp5);
        for(int i=1; i<=n; i++)
            for(int j=1; j<i; j++)
                LU[i][j]=L[makeIndex(i,j)];
    }

    else{ */
        if((fp4=fopen("Lmat5.m","w+"))==NULL){
            cout<<"Cannot open Lmat3\n";
            exit(0);
        }

        if((fp5=fopen("Umat5.m","w+"))==NULL){
            cout<<"Cannot open Umat3\n";
            exit(0);
        }

        make_lu();

        fputs("L = ...\n  ",fp4);
        fputs("[",fp4);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i==j) fprintf(fp4,"%d ",1);
                else if(i<j) fprintf(fp4,"%d ",0);
                else fprintf(fp4,"%f ",LU[i][j]);
            }
            if(i!=n) fprintf(fp4,"%d;\n  ",0);
            else fprintf(fp4,"%d];",1);
        }

        fputs("U = ...\n  ",fp5);
        fputs("[",fp5);
        for(int i=1; i<=n; i++){
            for(int j=1; j<n; j++){
                if(i>j) fprintf(fp5,"%d ",0);
                else fprintf(fp5,"%f ",LU[i][j]);
            }
            if(i!=n) fprintf(fp5,"%f;\n  ",LU[i][n]);
            else fprintf(fp5,"%f];",LU[n][n]);
        }
    /*}*/

    SolveSystem();

    fputs("x = ...\n  ",fp3);
        fputs("[",fp3);
        for(int i=1; i<=n; i++){
            if(i==n) fprintf(fp3,"%f];",x[i]);
            else fprintf(fp3,"%f; ",x[i]);
        }

    cout<<"Success! Please check the answer in Amat5.m, bvec5.m and xvec5.m"<<endl;

    return 0;
}

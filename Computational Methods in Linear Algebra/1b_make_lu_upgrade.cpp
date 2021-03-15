#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define MAX_n 1000

using namespace std;
double A[MAX_n][MAX_n];
double LU[MAX_n][MAX_n];
double P[MAX_n];
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

void make_lu_upgrade(){
    //initialization of P
    for(int i=1; i<=n; i++)
        P[i]=i;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++){
            if(i==j) LU[i][j]=1;
            else LU[i][j]=0;
        }

    for(int j=1; j<=n-1; j++){
        double maxelement=fabs(A[j][j]);
        int maxj=j;
        for(int m=j+1; m<=n; m++){
            if(maxelement<fabs(A[m][j])){
                maxelement=A[m][j];
                maxj=m;
            }
        }
        //interchange of L U and P
        double tmpline[MAX_n];
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

void recoginze(double A[MAX_n][MAX_n], FILE *fp1){
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
    FILE *fp1, *fp2, *fp3, *fp4;
    if((fp1=fopen("Amat2.m","r"))==NULL){
        printf("Cannot open AMat2\n");
        exit(0);
    }
    if((fp2=fopen("Lmat2Up.m","w+"))==NULL){
        printf("Cannot open LMatUp2\n");
        exit(0);
    }
    if((fp3=fopen("Umat2Up.m","w+"))==NULL){
        printf("Cannot open UMatUp2\n");
        exit(0);
    }
    if((fp4=fopen("Pmat2.m","w+"))==NULL){
        printf("Cannot open PMat2\n");
        exit(0);
    }

    recoginze(A,fp1);
    make_lu_upgrade();

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

    fputs("P = ...\n  ",fp4);
    fputs("[",fp4);
    for(int i=1; i<=n; i++){
        for(int j=1; j<n; j++){
            if(j==P[i]) fprintf(fp4,"%d ",1);
            else fprintf(fp4,"%d ",0);
        }
        if(i!=n&&n==P[i]) fprintf(fp4,"%d;\n  ",1);
        else if(i!=n&&n!=P[i]) fprintf(fp4,"%d;\n  ",0);
        else if(i==n&&n==P[i]) fprintf(fp4,"%d];",1);
        else fprintf(fp4,"%d];",0);
    }

    cout<<"Success! Please check the answer in Lmat2Up.m, Umat2Up.m and Pmat2.m"<<endl;

    return 0;
}

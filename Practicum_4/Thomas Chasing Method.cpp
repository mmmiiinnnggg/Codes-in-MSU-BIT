#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#define MAX_n 10000

using namespace std;

int n;
double A[MAX_n], B[MAX_n], C[MAX_n];
double inverseA[MAX_n][MAX_n];
double f[MAX_n], x[MAX_n];

double xtmp[MAX_n];
double xpre[MAX_n];
double xcurr[MAX_n];
double xstart[MAX_n];
int iteration;

void Trisolve(double a[MAX_n],double b[MAX_n],double c[MAX_n],double f[MAX_n],double X[MAX_n],int n){
    //the difference between book and code:
    //in the book the first element of a[] is a[2], but in the code is a[1]
    //so all the index of a[] minus 1

    //direct
    float p[n+1];
    float q[n+1];
    a[0]=0; c[n]=0;
    p[1]=c[1]/(-b[1]);
    q[1]=-f[1]/(-b[1]);
    for(int i=2; i<=n-1; i++){
        double A=(-b[i])-a[i-1]*p[i-1];
        p[i]=c[i]/A;
        q[i]=(a[i-1]*q[i-1]-f[i])/A;
    }
    //back
    X[n]=(a[n-1]*q[n-1]-f[n])/((-b[n])-a[n-1]*p[n-1]);
    for(int i=n-1; i>=1; i--){
        X[i]=p[i]*X[i+1]+q[i];
    }

    for(int i=1; i<=n; i++){
        x[i]=X[i];
    }
}

// x_k=A*x_k-1
void muti(double a[MAX_n],double b[MAX_n],double c[MAX_n]){
    for(int i=0; i<=n; i++){
        xtmp[i] = 0;
    }
    xtmp[1]=b[1]*xcurr[1]+c[1]*xcurr[2];
    xtmp[n]=a[n-1]*xcurr[n-1]+b[n]*xcurr[n];
    for(int i=2; i<n; i++)
        xtmp[i] = a[i-1]*xcurr[i-1]+b[i]*xcurr[i]+c[i]*xcurr[i+1];

    for(int k=1; k<=n; k++)
        xpre[k] = xcurr[k];
    for(int k=1; k<=n; k++)
        xcurr[k] = xtmp[k];
}

void ordinarymuti(double a[MAX_n][MAX_n]){
    for(int i=0; i<=n; i++){
        xtmp[i] = 0;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            xtmp[i] += a[i][j]*xcurr[j];
        }
    }

    for(int k=0; k<=n; k++)
        xpre[k] = xcurr[k];
    for(int k=0; k<=n; k++)
        xcurr[k] = xtmp[k];
}

// define (.)
double dotproduct(double x1[MAX_n], double x2[MAX_n]){
    double tmp = 0;
    for(int i=1; i<=n; i++)
        tmp += x1[i]*x2[i];
    return tmp;
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

void ReadLine(FILE* fp1,double Mat[MAX_n]){
    char c;
    string str;
    c=fgetc(fp1);
    if(c=='('){
        c=fgetc(fp1);
        int mat_i=1;
        while(c!=')'){
            int i=0;
            while(c!=','&&c!=')'){
                str[i++]=c;
                c=fgetc(fp1);
            }
            int sign=1;
            int k=i-1;
            int index=0;
            if(str[0]=='-'){
                sign=-1;
                index=1;
                k=i-2;
            }
            double num=0;
            while(k>=0){
                num = num + ((str[index++]-'0')*pow10(k));
                k--;
            }
            num *= sign;
            Mat[mat_i++]=num;
            if(c!=')') c=fgetc(fp1);
            else break;
        }
        Mat[0]=0;
    }
    //read the "enter"
    c=fgetc(fp1);
}

int main()
{
    FILE *fp1, *fp2;
    if((fp1=fopen("XuMingchuanIn.txt","r"))==NULL){
        printf("Cannot open myIn\n");
        exit(0);
    }
    if((fp2=fopen("XuMingchuanOut.txt","r+"))==NULL){
        printf("Cannot open myOut\n");
        exit(0);
    }

    char c;
    string str;
    c=fgetc(fp1);
        //read "N=10"
    if(c=='N')
        if((c=fgetc(fp1))=='='){
            int i=0;
            c=fgetc(fp1);
            while(c!='\n'){
                str[i++]=c;
                c=fgetc(fp1);
            }
            int k=i-1;
            i=0;
            while(k>=0){
                n += (str[i++]- '0')*pow10(k);
                k--;
            }
        }
    n=n+1;

    ReadLine(fp1,C);
    ReadLine(fp1,B);
    ReadLine(fp1,A);
    ReadLine(fp1,f);
    c=fgetc(fp1);
    if(c=='M')
        if((c=fgetc(fp1))=='='){
            int i=0;
            c=fgetc(fp1);
            while(c!='\n'){
                str[i++]=c;
                c=fgetc(fp1);
            }
            int k=i-1;
            i=0;
            while(k>=0){
                iteration += (str[i++]- '0')*pow10(k);
                k--;
            }
        }

        //start approach
    ReadLine(fp1,xstart);

// 1---Chasing method
    Trisolve(A,B,C,f,x,n);

    fputs("The solution with TDMA is:",fp2);
    fputs("\n",fp2);
    fputs("x=(",fp2);
    for(int i=1; i<=n; i++){
        fprintf(fp2,"%f",x[i]);
        if(i!=n)fputc(',',fp2);
        else fputc(')',fp2);
    }
    fputs("\n",fp2);
    fputs("\n",fp2);

// 2---Power method + simple iteration

    // inverse matrix: Ax_i=e_i
    for(int i=1; i<=n; i++){
        for(int j=0; j<=n; j++){
            // f = e_i
            if(j==i) f[j]=1;
            else f[j]=0;
        }

        Trisolve(A,B,C,f,x,n);

        for(int k=1; k<=n; k++){
            inverseA[k][i]=x[k];
        }
    }

    //find max eigenvalue of A
        //initiation of start approach
    for(int i=0; i<=n; i++){
        xcurr[i] = xstart[i];
        xpre[i] = 1;
    }

    double lambda1;
    int i=1;
    while(i<=iteration){
        muti(A,B,C);
        lambda1 = dotproduct(xcurr,xcurr)/dotproduct(xcurr,xpre);
        cout << "Iteration: " << i <<" lambda_max = " << lambda1;
        cout<<endl;
        i++;
    }
    cout<<endl;

    // find max eigenvalue of A^-1 => min of A
        //initiation of start approach
    for(int i=0; i<=n; i++){
        xcurr[i] = xstart[i];
        xpre[i] = 1;
    }

    double lambda2;
    i=1;
    while(i<=iteration){
        ordinarymuti(inverseA);
        lambda2 = dotproduct(xcurr,xcurr)/dotproduct(xcurr,xpre);
        cout << "Iteration: " << i <<" 1/lambda_min = " << lambda2;
        cout<<endl;
        i++;
    }
    cout<<endl;
    lambda2=1/lambda2;

    // simple iteration
    double tao_0 = 2 / (lambda1 + lambda2);
    double yn[MAX_n];
    double ynext[MAX_n];
    double ytmp[MAX_n];
        //y0 = (1,1,1,...,1)
    for(int i=0; i<=n; i++){
        yn[i]=xstart[i];
    }

    int iter=1;
    while(iter<=iteration){
        //calculate ytmp =A*y_n
    for(int i=1; i<=n; i++) ytmp[i] = 0;
    ytmp[1]=B[1]*yn[1]+C[1]*yn[2];
    ytmp[n]=A[n-1]*yn[n-1]+B[n]*yn[n];
    for(int i=2; i<n; i++)
        ytmp[i] = A[i-1]*yn[i-1]+B[i]*yn[i]+C[i]*yn[i+1];
        //calculate y_n+1
    for(int i=1; i<=n; i++){
        ynext[i] = tao_0*f[i]-tao_0*ytmp[i]+yn[i];
    }

    for(int i=0; i<=n; i++)
        yn[i]=ynext[i];
    printf("iteration = %d ",iter);
    for(int i=1; i<=n; i++){
        printf("%f ",yn[i]);
    }
    printf("\n");

    iter++;
    }

    //The prints
    fputs("The solution with simple iteration is:",fp2);
    fputs("\n",fp2);
    fputs("x=(",fp2);
    for(int i=1; i<=n; i++){
        fprintf(fp2,"%f",yn[i]);
        if(i!=n)fputc(',',fp2);
        else fputc(')',fp2);
    }
    fputs("\n",fp2);
    fputs("\n",fp2);


    fputs("The inverse matrix is:",fp2);
    fputs("\n",fp2);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            fprintf(fp2,"%f ",inverseA[i][j]);
        }
        fputs("\n",fp2);
    }
    fputs("\n",fp2);


    fputs("The max and min eigenvalue are:",fp2);
    fputs("\n",fp2);
    fprintf(fp2,"%f %f",lambda1,lambda2);
    //fputs("\n",fp2);

    return 0;
}


/*
    for(int i=1; i<=n; i++)
        printf("%f ",C[i]);
    printf("\n");
    for(int i=1; i<=n; i++)
        printf("%f ",B[i]);
    printf("\n");
    for(int i=1; i<=n; i++)
        printf("%f ",A[i]);
    printf("\n");
    for(int i=1; i<=n; i++)
        printf("%f ",f[i]);
    printf("\n");
    for(int i=1; i<=n; i++)
        printf("%f ",xcurr[i]);
    printf("\n");

*/

/*
    //print A^-1
    printf("The inverse matrix: \n");
    for(int i=1; i<=n; i++)
        printf("%f ",C1[i]);
    printf("\n");
    for(int i=1; i<=n; i++)
        printf("%f ",B1[i]);
    printf("\n");
    for(int i=1; i<=n; i++)
        printf("%f ",A1[i]);
    printf("\n");
    for(int i=1; i<=n; i++)
        printf("%f ",f[i]);
    printf("\n");
*/

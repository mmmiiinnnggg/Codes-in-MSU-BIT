#include <iostream>

#define Maxn 100

using namespace std;

//const int Maxn = 100;
int n;
int iteration;
double lambda;
double A[Maxn][Maxn];
double xpre[Maxn];
double xcurr[Maxn];

//x_i=Ax_i-1
void muti(){
    double xtmp[Maxn] = {0};
    for(int i=0; i<n; i++){
        xtmp[i] = 0;
        for(int j=0; j<n; j++)
            xtmp[i] += A[i][j]*xcurr[j];
    }
    for(int k=0; k<Maxn; k++)
        xpre[k] = xcurr[k];
    for(int k=0; k<Maxn; k++)
        xcurr[k] = xtmp[k];
}

double dotproduct(double x1[Maxn], double x2[Maxn]){
    double tmp = 0;
    for(int i=0; i<Maxn; i++)
        tmp += x1[i]*x2[i];
    return tmp;
}

int main()
{
    for(int i=0; i<Maxn; i++){
        for(int j=0; j< Maxn; j++)
            A[i][j]=0;
    }
    for(int i=0; i<Maxn; i++){
        xcurr[i] = 1;
        xpre[i] = 1;
    }
    cin >> n;
    cin >> iteration;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> A[i][j];

    int i=1;
    while(i<=iteration){
        muti();
        lambda = dotproduct(xcurr,xcurr)/dotproduct(xcurr,xpre);
        cout << "Iteration: " << i <<" lambda = " << lambda;
        cout<<endl;
        i++;
    }
    return 0;
}

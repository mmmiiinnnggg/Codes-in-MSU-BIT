#include <iostream>
#include<stdio.h>
#include<iomanip>
using namespace std;

int main()
{
    int n,temp,minDis;
    cin>>n;
    int dis[n][n]={0};     //distance matrix

    //initialization of distance matrix
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j!=i){
                cin>>temp;
                dis[i][j]=temp;
            }
            else{
                dis[i][j]=50000;
            }
        }
    }

    int d[n][1<<(n-1)]; //1<<(n-1) - 2^(n-1) Process matrix
    for(int i=1;i<n;i++) // initialize distance from every city to city0
        d[i][0]=dis[i][0];

    for(int j=1;j<1<<(n-1);j++){
        for(int i=0;i<n;i++){ //find the shortest distance from city i by passing cities set j
            if(((1<<(i-1))&j)==0){ //if city i is not in set j
                minDis=50000;
                for(int k=1;k<n;k++){
                    if(((1<<(k-1))&j)!=0) //if city k is in set j
                        //test every possible route from i to the next city k
                        //j-(1<<(k-1)) - kick out from set j
                        minDis = min(minDis,dis[i][k]+d[k][j-(1<<(k-1))]);
                }
                d[i][j] = minDis;
            }
        }
    }

    // print out the process matrix
    for(int i=0;i<n;i++){    //
        for(int j=0;j<1<<(n-1);j++){
            cout<<d[i][j]<<"  ";
        }
        cout << endl;
    }

    cout << "The shortest route is: " << minDis;

    return 0;
}

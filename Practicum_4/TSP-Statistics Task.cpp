#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

int dim = 10;
int Max = 1000;

int Processing(int dim)
{
    int matrix[dim][dim];
    srand(time(NULL));
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            matrix[i][j] = rand()%100;
/*
    cout << "The generative matrix: "<<endl;
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++)
            cout<< matrix[i][j]<< " ";
        cout << endl;
    }
*/
    int tempmin = Max ;
    for(int i=0;i<dim;i++){//by row
        for(int j=0;j<dim;j++)
            if(tempmin > matrix[i][j]) tempmin = matrix[i][j];
        for(int j=0;j<dim;j++)
            matrix[i][j] -= tempmin;
        tempmin = Max;
    }
/*
    cout << "The generative matrix after processing row: "<<endl;
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++)
            cout<< matrix[i][j]<< " ";
        cout << endl;
    }
*/
    for(int j=0;j<dim;j++){//by column
        for(int i=0;i<dim;i++)
            if(tempmin > matrix[i][j]) tempmin = matrix[i][j];
        for(int i=0;i<dim;i++)
            matrix[i][j] -= tempmin;
        tempmin = Max;
    }

    int count_zero = 0; // count_zero
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            if(matrix[i][j] == 0) count_zero++;
/*
    cout<<"The reformed matrix after processing column: "<<endl;
    for(int i=0;i<dim;i++){//print
        for(int j=0;j<dim;j++)
            cout<< matrix[i][j]<< " ";
        cout << endl;
    }
*/
   return count_zero;
}

int main(){
    for(int i=10;i<=15;i++){
        float count_sum = 0;
        int result;
        for(int j=0;j<1000;j++){
            Sleep(1001);
            result = Processing(i);
            cout<<result<<" ";
            count_sum += result;
        }
        cout << endl;
        cout <<"The average number of zero for dimension "<<i<<" is: "<< count_sum / 1000<<endl;
    }

    return 0;
}

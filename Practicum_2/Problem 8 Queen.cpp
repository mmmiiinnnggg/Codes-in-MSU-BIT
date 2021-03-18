#include <stdio.h>
#include <stdlib.h>

int Queenes[8]={0},Counts=0;

int Check(int line,int list)
{
    int index;
    for (index=0; index<line; index++)
	{
        int data=Queenes[index];
        if (list==data) {
            return 0;
        }
        if ((index+data)==(line+list)) {
            return 0;
        }
        if ((index-data)==(line-list)) {
            return 0;
        }
    }
    return 1;
}

void print() 
{
	int line; 
    for (line = 0; line < 8; line++)
    {
        int list;
        for (list = 0; list < Queenes[line]; list++)
            printf("0");
        printf("#");
        for (list = Queenes[line] + 1; list < 8; list++){
            printf("0");
        }
        printf("\n");
    }
    printf("================\n");
}

void eight_queen(int line){
    int list;
	for (list=0; list<8; list++)
	{
        if (Check(line, list)) {
            Queenes[line]=list;//在第line行第list列有皇后 
            if (line==7)//line==7表明找到一组解 ，计数+1，打印这组结果 
			{ 
                Counts++;
                print();
                Queenes[line]=0;
            }
            eight_queen(line+1);
            Queenes[line]=0;//每次判断之后都要归0以便下一组的寻找 
        }
    }
}
int main() {
    //调用回溯函数，参数0表示从棋盘的第一行开始判断
    eight_queen(0);
    printf("摆放的方式有%d种",Counts);
    return 0;
}


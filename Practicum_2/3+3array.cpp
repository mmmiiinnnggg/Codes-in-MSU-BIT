#include <iostream>
#include <stdio.h>
using namespace std;

int main(){
	int count=0;
	int nums[10]={0,1,2,3,4,5,6,7,8,9};
	for(int i=0; i<=27 ; i++){
		int a=0;
		for(int j=0 ; j <= 9; j++){
			if(nums[j] > i) break;
			int l = j;
			int r = 9;
			while(l <= r){
				int sum = nums[j] + nums[l] + nums[r];
				if(sum == i){
					if(j==l && j==r) a+=1;
					else if(j!=l && j!=r && l!=r) a+=6;
					else a+=3;
					l++;
					r--;
				}
				else if (sum < i) l++;
				else if (sum > i) r--;
			}
		}
		count += a*a;
	}
	cout << count << endl;
	return 0;
}
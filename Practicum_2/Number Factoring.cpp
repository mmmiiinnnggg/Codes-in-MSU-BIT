#include <stdio.h>
#include <math.h>
int main(){    
  int n, i;    
  scanf("%d", &n);    
  i = 2;    
  while (i<=(int)sqrt(n))
    if((int)n % (int)i == 0) {                 
        printf("%d*",i);
        n = n/i;        
    } else  i = i+1;    
    printf("%d",n);    
    return 0;
}


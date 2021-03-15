#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char cmd[30];
char buf[10][10];
int command[30]={0};//mark the command line in 2-dim buf

//put command line to a 2-dim matrix
int collect(){ 
  int i=0,j=0,k=0,index=0;
  char a,b;
  fgets(cmd,30,stdin);
  while((a=cmd[index])!='\n')
    switch(a){
      case '>': if((b=cmd[index+1])=='>') {i++;j=0;buf[i][j]=a;j++;buf[i][j]=b;command[i]=1;i++;j=0;index+=2;break;}//>>
                else {i++;j=0;buf[i][j]=a;command[i]=2;i++;j=0;buf[i][j]=b;j++;index+=2;break;}//>
      case '|': if((b=cmd[index+1])=='|') {i++;j=0;buf[i][j]=a;j++;buf[i][j]=b;command[i]=3;i++;j=0;index+=2;break;}//||
                else {i++;j=0;buf[i][j]=a;command[i]=4;i++;j=0;buf[i][j]=b;j++;index+=2;break;}//|
      case '<': {i++;j=0;buf[i][j]=a;command[i]=5;i++;j=0;index++;break;}
      case '&': {i++;j=0;buf[i][j]=a;command[i]=6;i++;j=0;index++;break;}
      case ';': {i++;j=0;buf[i][j]=a;command[i]=7;i++;j=0;index++;break;}
      case '(': if(index==0) {buf[i][j]=a;command[i]=8;index++;break;}
                else {i++;j=0;buf[i][j]=a;command[i]=8;index++;break;}
      case ')': if(index==0) {buf[i][j]=a;command[i]=8;index++;break;}
                else {i++;j=0;buf[i][j]=a;command[i]=9;index++;break;}
      case ' ': if((b=cmd[index+1])=='&') {i++;j=0;buf[i][j]=a;command[i]=10;i++;j=0;buf[i][j]=b;command[i]=6;i++;j=0;index+=2;break;}//||
                else {i++;j=0;buf[i][j]=a;command[i]=10;i++;j=0;buf[i][j]=b;j++;index+=2;break;}//|
      default : if((cmd[index-1]!='(')&&(cmd[index-1]!=')')) {buf[i][j]=a;j++;index++;break;}
                else {i++;j=0;buf[i][j]=a;j++;index++;break;}
    }
    return i;//i-lines
}

//# конвейер pr1 | pr2 | ... | prN для произвольного N>=2; считать, что аргументов у prI  (1 <= I<= N) нет (но возможна реализация с произвольным числом аргументов у каждого процесса)

int connector(int st,int N)//st=start,pr1|pr2|pr3
{
    int pid,wpid;
    int i,j,k,*status,pro_num=1;
    int fd[10][2];
    for(i=0;i<N+1;i++) pipe(fd[i]);
    for( i = 0; i < N; i++ ){
        if((pid = fork()) == 0) break;/*son*/
        else if( pid < 0 ){perror("fork error");exit(1);}
    }
    if( i == 0 ){
        printf("child pid = %d,ppid = %d\n",getpid(),getppid());
        for(k=0;k!=i&&k<N;k++){
          close(fd[k][0]);
          close(fd[k][1]);
        }
        close(fd[0][0]);
        //son1 exec to pipe1
        dup2(fd[0][1],1);
        execlp(buf[st],buf[st],NULL);
        perror("first error");
    }
    for(j=0;j<N-1;j++){
       if( i == pro_num){//the middle pipes
        printf("child pid = %d,ppid = %d\n",getpid(),getppid());
        for(k=0;(k!=i)&&(k!=(i+1))&&(k<N);k++){
          close(fd[k][0]);
          close(fd[k][1]);
        }
        close(fd[i][1]);
        close(fd[i+1][0]);
        //son pro_num read, from pipei and go to pipei+1
        dup2(fd[i][0],0);
        dup2(fd[i+1][1],1);
        st+=2;pro_num++;
        execlp(buf[st],buf[st],NULL);
        perror("i error");
      }
    }
    

    if( i == N ){
        printf("child pid = %d,ppid = %d\n",getpid(),getppid());
        for(k=0;k!=i&&k<N;k++){
          close(fd[k][0]);
          close(fd[k][1]);
        }
        close(fd[i][1]);
        //the last son read from pipeN and print on screen
        dup2(fd[i][0],0);
        st+=2;
        execlp(buf[st],buf[st],NULL);
        perror("last error");
    }

    else{ //close father, and must close after fork()
      for(k=0;k<N;k++){
        close(fd[k][0]);
        close(fd[k][1]);
      }
        // father recycle son
      wait(status);
    }
    return 0;
}

int main(){
  collect();
  for(int i=0;i<10;i++){
    for(int j=0;j<10;j++)
      printf("%c",buf[i][j]);
    printf("\n");
  }
  connector(0,2);
  return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

//Породить сыновний процесс. 
//-Родитель должен напечатать I am the parent my pid is PID.
//-Сын должен напечатать I am the son my pid is PID my father’s pid is PPID

int main(){
  int pid;
  if(0>(pid=fork())){perror("fork");exit(-1);}
  else if(pid)  
    printf("I am the parent my pid is %d\n",getpid());
  else{
    printf("I am the son my pid is %d\n",getpid());
    printf("My father's pid %d\n",getppid());
  }
  return 0;
}
//finish

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

//Породить сыновний процесс, затем в обоих процессах вывести на печать собственный PID и PID родительского процесса.
int main(){
  /*создание нового процесса, с этого момента два процесса функционируют параллельно и независимо*/
  if(fork()==-1){perror("fork");return 1;}
  /*оба процесса печатают PID текущего процесса и PID процесса-предка*/ 
  printf("Maybe it's parent maybe it's son PID=%d,PPID=%d\n",getpid(),getppid());
  return 0;
}
//finish


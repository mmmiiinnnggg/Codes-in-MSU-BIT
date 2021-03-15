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

//run with parameters
void exepara(int st,int N){//N-number of paras.
  char para[10][10];
  int pos=st+2;
  for(int i=0;i<N;i++){
    strcpy(para[i],buf[pos]);
    pos+=2;
  }
  execlp(buf[st],buf[st],para,NULL);
  perror("error run with paras");
  exit(1);
}

//# конвейер pr1 | pr2 | ... | prN для произвольного N>=2; считать, что аргументов у prI  (1 <= I<= N) нет (но возможна реализация с произвольным числом аргументов у каждого процесса)
int connector(int st,int N)//st=start of command,N-number of pipe
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
        exit(0);
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

//#перенаправление ввода-вывода <,  >,  >> (в том числе для pr1 и prN в конвейере)
//Например,	
//pr<data>res           
//pr1|pr2>res.txt

void dir1(int st) // st=start of command dir <
{
    int pid,fd,*status;
    if((pid=fork())==0){//son
      if(0>(fd=open(buf[st+2], O_RDWR, 0664))) {perror("open");exit(1);}
      dup2(fd,0); //dup2(oldfd, newfd);
      close(fd);
      execlp(buf[st],buf[st],NULL);
      perror("run right dir");
      exit(1);
    }
    wait(status);  //wait death of one son and recycle
}

void dir2(int st) // st=start of command dir >
{
    int pid,fd,*status;
    if((pid=fork())==0){//son
      if(0>(fd=open(buf[st+2], O_RDWR, 0664))) {perror("open");exit(1);}
      dup2(fd,1); //dup2(oldfd, newfd);
      close(fd);
      if(command[st-1]==5) {execlp(buf[st-2],buf[st-2],NULL);perror("run right dir");exit(1);}//pr1<data>res
      else {execlp(buf[st],buf[st],NULL);perror("run right dir");exit(1);}
    }
    wait(status);  //wait death of one son and recycle
}

void dir3(int st) // st=start of command dir >>
{
    int pid,fd,*status;
    if((pid=fork())==0){//son
      if(0>(fd=open(buf[st+2], O_RDWR, 0664))) {perror("open");exit(1);}
      lseek(fd,0L,SEEK_END);
      dup2(fd,1); //dup2(oldfd, newfd);
      close(fd);
      execlp(buf[st],buf[st],NULL);
      perror("run right dir");
      exit(1);
    }
    wait(status);  //wait death of one son and recycle
}

//запуск в фоновом режиме  & (в том числе и для конвейеров)
//Например,	pr arg1 arg2 &          pr1 | pr2 | pr3 > res.all &
void backRun(int st){/*position of &*/
  int pid,i,*status;
  if(0>(pid=fork())) {perror("error fork1");exit(1);}
  else if(pid) wait(status);//father
  else{//son
    if(0>(pid=fork())) {perror("error fork2");exit(1);}
    else if(pid) printf("child is going to finish");//son
    else{/*grandchild*/
      sleep(3);//grandchild wait for the finish of child and become background to run
      if(command[st-3]==1||command[st-3]==2||command[st-3]==5) execlp(buf[st-4],buf[st-4],NULL);//check dir
      else execlp(buf[st-2],buf[st-2],NULL);
      perror("error exec");
      exit(1);
    }
  }
}

// 1. pr1 ; pr2 ; ... ; prN
//последовательное выполнение команд prI - как  если  бы  они были переданы интерпретатору по одной  команде в строке
void orderRun(int st,int N){//st-start of command, N-how many ;
  int i,j,num=1,pid,*status;
  int sec=1;
  for(i=0;i<N+1;i++){
    if((pid = fork()) == 0) break;/*son, and jump from cycle to following exec*/
    if( pid < 0 ){perror("fork error");exit(1);}
  }

  if(i==0){
    execlp(buf[st],buf[st],NULL);
    perror("runi error");
    exit(1);
  }

  for(j=0;j<N;j++)
    if(i==num){
    num++;
    st+=2;
    sleep(sec);
    sec++;
    execlp(buf[st],buf[st],NULL);
    perror("runi error");
    exit(1);
    }

  if(i==N+1) wait(status);//father
}

// 3. pr1 || pr2 
//выполнить pr1; в случае неудачи выполнить pr2
void changeRun(int st){/*st-start of command*/
  if(0>(execlp(buf[st],buf[st],NULL))){
    printf("Error run pr1\n");
    st+=2;
    execlp(buf[st],buf[st],NULL);
    printf("Error run pr2\n");
    exit(1);
  }
}

//command: 1>> 2> 3|| 4| 5< 6& 7; 8( 9) 10''
//collect connector dir1< dir2> dir3>> backRun orderRun changeRun
void judge(int l,int r,int line){
	int i,flag1=0;
	for(i=l;i<r;i++) if(command[i]!=0) flag1=1;
    if((line==0)&&(flag1==0)) execlp(buf[0],buf[0],NULL);
    else{
	  for(i=l;i<r;i++){
	  if(command[i]==0) continue;
	  else switch(command[i]){
			    case 1: {dir3(i-1);judge(i+2,30,line);break;}
      			case 2: {dir2(i-1);judge(i+2,30,line);break;}
      			case 3: {changeRun(i-1);judge(i+2,30,line);break;}
      			case 4: {int count =1;
               			 int j=i;
            			while((command[i-1]!=9)&&(command[j]==4)&&(command[i+1]!=8)) {count++;j+=2;}//count-number of pipe
               			connector(i-1,count); 
               			judge(i+2*count,30,line); 
               			break;
              			}
      			case 5: {dir1(i-1);judge(i+2,30,line);break;}
     		 	//case 6: {backRun(i);break;}
      			case 7: {int ord=1;
               			 int j=i;
               			 while(command[j]==7) {ord++;j+=2;}//ord-number of ;
               			 orderRun(i-1,ord); 
               			 judge(i+2*ord,30,line); 
               			 break;
              			}
      			case 8: {if(command[i-1]==4) {connector(i-2,1);judge(i+1,30,line);break;}
               			else{
                 			int bl=i,br; 
                 			while(command[bl]!=9) bl++;
                 			judge(l+1,r-1,line);
                 			break;
               				}
				}
      			case 9: {if(command[i+1]==4) {connector(i,1);judge(i+2,30,line);break;}
               			else {judge(i+1,30,line);break;}
				}
                 
      			case 10:{if(command[i+1]==6) {backRun(i+1);break;}//&
               			else{
                 			int ctspace=1,pos=i+2;
                 			while(command[pos]==10) {ctspace++;pos+=2;}//ctspace - number of paras
                 			exepara(i-1,ctspace);
                 			break;
                			}
              			}
		       }
  		
	   }
   }
}

int main(int argc,char **argv){
  while(1)
{
    int line;
    line=collect();
    judge(0,30,line);
    for(int i=0;i<10;i++) memset(buf[i],0,10);
    memset(cmd,0,30);
    for(int j=0;j<30;j++)
    command[j]=0;
}
  return 0;
}

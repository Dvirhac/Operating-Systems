  

// C program to illustrate 
// pipe system call in C 
// shared by Parent and Child 
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include<cstdio>
#include "md5.h"


  char childbuf[20];
  char parentbuf[20];
  char message[20];
  int pid;

void handler(int mysignal){
 // printf("in handler\n");
  if (strlen(childbuf) != 32 ){
       // printf("the gibuv doesnt succeded!");
        exit(1);
  }
  else {
    printf("%s%d%s","encrypted by process ",pid ," : ");
	printf("%s\n",childbuf);

  //kill(pid, SIGKILL);
  
}
}

int main() 
{ 
	printf("plain text:");
    fgets(message,20,stdin);
    int p1[2],p2[2];
    signal( SIGUSR1, handler );


    if (pipe(p1) < 0) 
        exit(1);
    if (pipe(p2) < 0)
        exit(1);
    
    if ((pid = fork()) < 0) 
        exit(0);

    if (pid > 0){    //parent
		close(p1[0]);
		close(p2[1]);
		
     // printf("in parent!\n");
      write(p1[1],message,32);
      read(p2[0],childbuf, 32);
	  wait(NULL);
      kill(pid, SIGKILL);
    } 

    else{
		close(p1[1]);
		close(p2[0]);
		char buf[32];
        read(p1[0], buf, 32);
        write(p2[1],md5(buf).c_str(), 32);
        kill(getppid(), SIGUSR1 );
    }  
    return 0; 
} 
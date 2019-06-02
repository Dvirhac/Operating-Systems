#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
int cpid[5];        
int j;                    

int sigCatcher() {
    signal(SIGINT, sigCatcher);  
    printf("PID %d caught one\n", getpid());
    if (j > -1) {
        kill(cpid[j], SIGINT);
    }
}
int main() {
    int i;
    int zombie;
    int status;
    int pid;
    signal(SIGINT, sigCatcher);
    for(i=0; i<5; i++){
        if((pid=fork()) ==  0){      		
            printf("PID %d ready\n", getpid());
            j = i-1;
            pause(); 			
            exit(0);  		
        }
        else {                
            cpid[i] = pid;
        }
    }
    sleep(2);     			
    kill(cpid[4], SIGINT);     		
    sleep(2);                 			
    for(i=0; i<5; i++){
        zombie = wait(&status); 		
        printf("Process %d is dead\n", zombie);
    }
    exit(0);
}
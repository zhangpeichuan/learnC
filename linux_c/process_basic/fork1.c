#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid;

    printf("[%d]Begin!\n",getpid());
    fflush(NULL);/*重要!!!!!*/
    pid = fork();
    if (pid < 0)
    {
        perror("fork()");
        exit(1);
    }

    if(pid == 0){
        printf("[%d]Child is Working!\n",getpid());
    }else{
        printf("[%d]Parent is Working!\n",getpid());
    }

    
    //getchar();
    printf("[%d]End!\n",getpid());

    return 0;
}
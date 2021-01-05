#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


#define LEFT    30000000
#define RIGHT   30000200

int main(){
    int i,j,mark;
    pid_t pid;
    for (i = LEFT; i <= RIGHT;i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork()");
            exit(1);
        }
        if (pid == 0){
            mark = 1;
            for (j = 2; j < i / 2; j++){
                if (i % j == 0){
                    mark = 0;
                    break;
                }
            }
            if (mark)
                printf("%d is a primer \n", i);
//            sleep(10);
            exit(0);
        }
    }
//    sleep(100);
    exit(0);
}
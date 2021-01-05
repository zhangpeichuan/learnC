#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
date +%s

*/


int main(){
    puts("Begin!");
    fflush(NULL);/*重要*/
    execlp("date","date","+%s",NULL);
    perror("execlp()");
    exit(1);

    puts("End!");
    return 0;
}

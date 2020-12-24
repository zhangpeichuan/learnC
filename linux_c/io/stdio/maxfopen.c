#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(){
    FILE    *fp=NULL;
    int i=0;
    while(1){
    fp = fopen("tmp","r");
    i++;
    if(fp == NULL){
        perror("fopen()");
        break;
    }
    }
    printf("count = %d\n",i);
    //ulimit -a

}

#include <stdio.h>
#include <stdlib.h>

int main(){

    int * p = NULL;
    
    p = malloc(sizeof(int));

    if(p ==NULL){
        printf("malloc() error!\n");
        exit(1);
    }
   *p = 10;
   printf("%p -->p=  %d \n",p,*p);
    free(p);


    return 0;
}

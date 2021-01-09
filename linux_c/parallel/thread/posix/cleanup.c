#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


static void cleanup_fun(void *p){
    puts(p);
}

static void *func(void *p){
    //push pop成对出现，可以预编译查看为什么
    puts("Thread is working!");
    pthread_cleanup_push(cleanup_fun,"cleanup1");
    pthread_cleanup_push(cleanup_fun,"cleanup2");
    pthread_cleanup_push(cleanup_fun,"cleanup3");
    puts("push over \n");
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(1);

    pthread_exit(NULL);
//    return NULL;
}
int main(){

    pthread_t tid;
    int err;
    puts("Begin!");
    pthread_create(&tid,NULL,func,NULL);
    if(err){
        fprintf(stderr,"pthread_create():%s \n ",strerror(err));
        exit(1);

    }
    pthread_join(tid,NULL);

    puts("End!");

    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

#include "mytbf.h"

typedef struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
}mytbf;
typedef void(*sighandler_t)(int);
static mytbf *job[MYTBF_MAX];
static int inited = 0;
static sighandler_t alrm_handler_save;
static int get_free_pos(void){
    int i;
    for (i = 0; i < MYTBF_MAX; i++)
    {
        if(job[i] == NULL)
            return i;
    }
    return -1;
}
static int min(int a,int b){
    return a>b?b:a;
}
static void sighandler(int s){
    int i;
    alarm(1);
    for (i = 0; i < MYTBF_MAX; i++)
    {
        if(job[i] !=NULL){
            job[i]->token +=job[i]->cps;
            if(job[i]->token > job[i]->burst)
                job[i]->token = job[i]->burst;
        }
    }    
}
static void module_unload(void){
    int i;
    
    signal(SIGALRM,alrm_handler_save);
    alarm(0);
    for (i = 0; i < MYTBF_MAX; i++)
    {
        free(job[i]);
    }
}
static void module_load(void){
    alrm_handler_save = signal(SIGALRM,sighandler);
    alarm(1);
    atexit(module_unload);//钩子函数
}

mytbf_t *mytbf_init(int cps,int burst){
    mytbf *me = NULL;

    if(!inited){
        module_load();
        inited = 1;
    }
    

    int pos = get_free_pos();
    if (pos < 0)
        return NULL;

    me = malloc(sizeof(*me));
    if (me == NULL)
        return NULL;
    me->cps = cps;
    me->burst = burst;
    me->token = 0;
    me->pos = pos;

    job[pos] = me;
    return me;
}
int mytbf_fetchtoken(mytbf_t *ptr,int size){
    mytbf *me = (mytbf *)ptr;

    if(size <= 0)
        return -EINVAL;
    
    while (me->token <=0)
        pause();
    int n =  min(me->token,size);
    me->token -= n;
    return n;
}
int mytbf_returntoken(mytbf_t *ptr,int size){
    mytbf *me = (mytbf *)ptr;

    if(size <= 0)
        return -EINVAL;
    
    int token =me->token;
    token +=size;
    me->token = (token > me->burst)?me->burst:token;
    
    return size;

}
int mytbf_destroy(mytbf_t *ptr){
    mytbf *me = (mytbf *)ptr;
    job[me->pos] = NULL;
    free(ptr);
    return 0;

}
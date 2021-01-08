#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

#include "mytbf.h"

typedef struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
}mytbf;
static mytbf *job[MYTBF_MAX];
static int inited = 0;
static struct sigaction alarm_sa_save;
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
static void alarm_action(int sig,siginfo_t *infop,void *unused){
    int i;
    if(infop->si_code == SI_KENEL)
        return;
    
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

    struct itimerval itv;
    sigaction(SIGALRM,&alarm_sa_save,NULL);
    itv.it_interval.tv_sec=0;
    itv.it_interval.tv_usec=0;
    itv.it_value.tv_sec=0;
    itv.it_value.tv_usec=0;
    setitimer(ITIMER_REAL,&itv,NULL);

    for (i = 0; i < MYTBF_MAX; i++)
    {
        free(job[i]);
    }
}
static void module_load(void){

    struct sigaction sa;
    struct itimerval itv;
    sa.__sigaction_u.__sa_sigaction = alarm_action;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGALRM,&sa,&alarm_sa_save);


    itv.it_interval.tv_sec=1;
    itv.it_interval.tv_usec=0;
    itv.it_value.tv_sec=1;
    itv.it_value.tv_usec=0;
    setitimer(ITIMER_REAL,&itv,NULL);

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
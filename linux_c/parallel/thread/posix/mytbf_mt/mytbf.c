#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "mytbf.h"

typedef struct mytbf_st
{
    int cps;
    int burst;
    int token;
    int pos;
	pthread_mutex_t mut;
	pthread_cond_t	cond;
}mytbf;

static mytbf *job[MYTBF_MAX];
static pthread_mutex_t mut_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_t tid_alarm;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;	

static int get_free_pos_unlocked(void){
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
static void *thr_alarm(void *p){
    int i;
	while(1){
		pthread_mutex_lock(&mut_job);
		for (i = 0; i < MYTBF_MAX; i++)
		{
			if(job[i] !=NULL){
				pthread_mutex_lock(&job[i]->mut);
				job[i]->token +=job[i]->cps;
				if(job[i]->token > job[i]->burst)
					job[i]->token = job[i]->burst;
				pthread_cond_broadcast(&job[i]->cond);
				pthread_mutex_unlock(&job[i]->mut);
			}
		}    
		pthread_mutex_unlock(&mut_job);
		sleep(1);
	}
}
static void module_unload(void){
    int i;
 	pthread_cancel(tid_alarm);
	pthread_join(tid_alarm,NULL);
	   
	for (i = 0; i < MYTBF_MAX; i++)
	{	if(job[i] != NULL){
		  mytbf_destroy(job[i]);
		}
	}
	pthread_mutex_destroy(&mut_job);
}
static void module_load(void){
	int err;
   err = pthread_create(&tid_alarm,NULL,thr_alarm,NULL);
	if(err){
		fprintf(stderr,"pthread_creat()%s\n",strerror(err));
		exit(1);
	}
	atexit(module_unload);//钩子函数
}

mytbf_t *mytbf_init(int cps,int burst){
    mytbf *me = NULL;
	
	pthread_once(&init_once,module_load);
	
	me = malloc(sizeof(*me));
    if (me == NULL)
        return NULL;
    me->cps = cps;
    me->burst = burst;
    me->token = 0;
	pthread_mutex_init(&me->mut,NULL);
	pthread_cond_init(&me->cond,NULL);
	pthread_mutex_lock(&mut_job);
    int pos = get_free_pos_unlocked();
    if (pos < 0){
       pthread_mutex_unlock(&mut_job);
		free(me);
		return NULL;
	}
		me->pos = pos;
    job[pos] = me;
	pthread_mutex_unlock(&mut_job);

    return me;
}
int mytbf_fetchtoken(mytbf_t *ptr,int size){
    mytbf *me = (mytbf *)ptr;

    if(size <= 0)
        return -EINVAL;
    pthread_mutex_lock(&me->mut);
    while (me->token <=0)
	{
		pthread_cond_wait(&me->cond,&me->mut);
		/*
		pthread_mutex_unlock(&me->mut);
		sched_yield();
		pthread_mutex_lock(&me->mut);
		*/
	}
	int n =  min(me->token,size);
    me->token -= n;
	pthread_mutex_unlock(&me->mut);
    return n;
}
int mytbf_returntoken(mytbf_t *ptr,int size){
    mytbf *me = (mytbf *)ptr;

    if(size <= 0)
        return -EINVAL;
    
	pthread_mutex_lock(&me->mut);
    me->token +=size;
    if(me->token > me->burst)
		me->token= me->burst;
	pthread_cond_broadcast(&me->cond);
    pthread_mutex_unlock(&me->mut);
    
	return size;
}
int mytbf_destroy(mytbf_t *ptr){
    mytbf *me = (mytbf *)ptr;
	
	pthread_mutex_lock(&mut_job);
    job[me->pos] = NULL;
    pthread_mutex_unlock(&mut_job);

	pthread_mutex_destroy(&me->mut);
	pthread_cond_destroy(&me->cond);
    free(ptr);
	return 0;

}



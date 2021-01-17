/*
 * @Author: your name
 * @Date: 2021-01-07 06:23:48
 * @LastEditTime: 2021-01-07 11:44:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /learnC/linux_c/parallel/signal/anytimer/anytime.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include "anytimer.h"

typedef void(*anytime_handler)(void *);
typedef enum{
    job_state_runing,
    job_state_canceled,
	job_state_pause,
	job_state_over
}job_state;
typedef struct{
	job_state		state;
    int             sec;
	int				time_remain;
	int				repeat;
    at_jobfunc_t	*handler;
    char            *argv;
    int             pos;
}job_st;
static job_st *job[JOBMAX];
static int	inited = 0;
static struct sigaction	sa_old;
static struct itimerval	itv_old;

static int get_free_pos(){
	int i;
	for(i=0;i<JOBMAX;i++){
		if(job[i] == NULL){
			return i;
		}
	}
	return -1;
}
static void alrm_action(int s,siginfo_t *infop,void *unused){
	int i;
	if(infop->si_code != SI_KERNEL)
		return;
	for(i = 0;i< JOBMAX && job[i] != NULL;i++){
		if(job[i]->state == job_state_runing){
			job[i]->time_remain --;
			if(job[i]->time_remain == 0){
				job[i]->handler(job[i]->argv);
				if(job[i]->repeat == 1){
					job[i]->time_remain = job[i]->sec;
				}else{
					job[i]->state = job_state_over;
				}
			}
		}
	}
}
static void module_unload(void){
	setitimer(ITIMER_REAL,&itv_old,NULL);
	sigaction(SIGALRM,&sa_old,NULL);
}
static void module_load(void){
	struct sigaction	sa;
	struct itimerval	itv;
	sa.sa_sigaction = alrm_action;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	if(sigaction(SIGALRM,&sa,&sa_old) < 0){
		perror("sigaction()");
		exit(1);
	}

	itv.it_interval.tv_sec = 1;
	itv.it_interval.tv_usec = 0;
	itv.it_value.tv_sec = 1;
	itv.it_value.tv_usec = 0;
	if(setitimer(ITIMER_REAL,&itv,&itv_old) < 0){
		perror("setitimer()");
		exit(1);
	}
	atexit(module_unload);
}
static int at_addjob_repeat_by(int timeInterval,int repeat,at_jobfunc_t *jobp,void *argv){
	if(timeInterval < 0){
		return -EINVAL;
	}
	if(!inited){
		module_load();
		inited = 1;
	}

	int pos = get_free_pos();
	job_st *me = NULL;
	if(pos < 0){
		return -ENOSPC;
	}
	me= malloc(sizeof(*me));
	if(me == NULL)
		return -ENOMEM;
	me->state = job_state_runing;
    me->sec = timeInterval;
	me->time_remain = me->sec;
	me->repeat = repeat;
    me->handler = jobp;
    me->argv = argv;
	me->pos = pos;
	job[pos] = me;
    return pos;
}
int at_addjob(int sec,at_jobfunc_t *jobp,void * argv){
	return at_addjob_repeat_by(sec,0,jobp,argv);
}
int	at_addjob_repeat(int sec,at_jobfunc_t *jobp,void *argv){
	return at_addjob_repeat_by(sec,1,jobp,argv);
}
int at_canceljob(int id){
	if(id < 0 || id >=JOBMAX || job[id] == NULL)
		return -EINVAL;
	if(job[id]->state == job_state_canceled)
		return -ECANCELED;
	if(job[id]->state == job_state_over)
		return -EBUSY;
	if(job[id]->state == job_state_pause)
		;
	job[id]->state = job_state_canceled;
	return 0;
}
int at_waitjob(int id){
	if(id < 0 || id >=JOBMAX || job[id] == NULL)
		return -EINVAL;
	if(job[id]->repeat == 1)
		return -EBUSY;
	if(job[id]->state == job_state_pause)
		return -EBUSY;
	while(job[id]->state == job_state_runing)
		pause();
	if(job[id]->state == job_state_canceled || job[id]->state == job_state_over){
		free(job[id]);
		job[id] = NULL;
	}
	return 0;
}
int at_pausejob(int id){
	if(id < 0 || id >=JOBMAX || job[id] == NULL)
		return -EINVAL;
	if(job[id]->repeat == 1)
		return -EBUSY;
	if(job[id]->state == job_state_canceled)
		return -ECANCELED;
	if(job[id]->state == job_state_over)
		return -EBUSY;
	if(job[id]->state == job_state_pause)
		return -EBUSY;
	if(job[id]->state == job_state_runing)
		job[id]->state = job_state_pause;
	return 0;
}
int at_resumejob(int id){
	if(id < 0 || id >=JOBMAX || job[id] == NULL)
		return -EINVAL;
	if(job[id]->repeat == 1)
		return -EBUSY;
	if(job[id]->state == job_state_canceled)
		return -ECANCELED;
	if(job[id]->state == job_state_over)
		return -EBUSY;
	if(job[id]->state == job_state_runing)
		return -EBUSY;
	if(job[id]->state == job_state_pause)
		job[id]->state = job_state_runing;
	return 0;
}






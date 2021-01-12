#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include "relayer.h"

#define	BUFSIZE	 1024 

typedef enum{
	STATE_R = 1,
	STATE_W,
	STATE_Ex,
	STATE_T
}FSM_STATE;

typedef struct relayer_fsm_st{
	int		state;
	int		sfd;
	int		dfd;
	int		len;
	int		pos;
	char	*errstr;
	char	buf[BUFSIZE];
	int64_t	rcount;
	int64_t	wcount;
}RELAYER_FSM;
typedef struct relayer_job_st{
	int		job_state;
	int		fd1,fd2;
	int fd1_save,fd2_save;
	RELAYER_FSM	fsm12,fsm21;
	pthread_mutex_t	mut;
	pthread_cond_t	cond;
}relayer_job;
static relayer_job *rel_job[RELAYER_JOBMAX];
static pthread_mutex_t	mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static pthread_t	tid_relayer;
int relayer_job_destroy(int pos){
	relayer_job *me = rel_job[pos];
	if(me == NULL)
		return -EINVAL;

	pthread_mutex_lock(&mut_rel_job);
	rel_job[pos] = NULL;
	pthread_mutex_unlock(&mut_rel_job);
	
	fcntl(me->fd1,F_SETFL,me->fd1_save);
	fcntl(me->fd2,F_SETFL,me->fd2_save);

	pthread_mutex_destroy(&me->mut);
	pthread_cond_destroy(&me->cond);
	free(rel_job[pos]);

	return 0;
}
static void fsm_driver(RELAYER_FSM *fsm){
	int ret;
	switch (fsm->state)
	{
		case STATE_R:
			fsm->len = read(fsm->sfd,fsm->buf,BUFSIZE);
			fsm->rcount +=1;
			if(fsm->len == 0)
				fsm->state = STATE_T;
			else if(fsm->len < 0){
				if(errno == EAGAIN)
						fsm->state = STATE_R;
				else{
					fsm->errstr = "read()";
					fsm->state = STATE_Ex;
				}
			}else{
				fsm->pos = 0;
				fsm->state = STATE_W;
			}
			break;

		case STATE_W:
			ret = write(fsm->dfd,fsm->buf+fsm->pos,fsm->len);
			fsm->wcount +=1;
			if(ret <0){
				if(errno == EAGAIN){
					fsm->state = STATE_W;
				}else{
					fsm->errstr = "write()";
					fsm->state = STATE_Ex;
				}
			}else{
				fsm->pos +=ret;
				fsm->len -=ret;
				if(fsm->len == 0){
					fsm->state = STATE_R;
				}else{
					fsm->state = STATE_W;
				}
			}
			break;

		case STATE_Ex:
			perror(fsm->errstr);
			fsm->state = STATE_T;
			break;

		case STATE_T:
			/*do sth*/
			break;

		default:
			abort();
			break;
	}
}
static void *thr_relayer(void *p){
	int i;
	while(1){
	pthread_mutex_lock(&mut_rel_job);
	for(i = 0;i<RELAYER_JOBMAX;i++){
			if(rel_job[i] != NULL){
				pthread_mutex_lock(&rel_job[i]->mut);
				if(rel_job[i]->job_state == STATE_RUNNING){
					fsm_driver(&rel_job[i]->fsm12);
					fsm_driver(&rel_job[i]->fsm21);
					if(rel_job[i]->fsm12.state == STATE_T && rel_job[i]->fsm21.state == STATE_T)
					{
						rel_job[i]->job_state = STATE_OVER;
					}
				}else if(rel_job[i]->job_state == STATE_CANCELED){
					
				}else if(rel_job[i]->job_state == STATE_OVER){
				
				}
				pthread_cond_broadcast(&rel_job[i]->cond);
				pthread_mutex_unlock(&rel_job[i]->mut);
			}
	}
	pthread_mutex_unlock(&mut_rel_job);
	}
}
static void module_unload(void){
	int i;
	pthread_cancel(tid_relayer);
	pthread_join(tid_relayer,NULL);

	for(i=0;i<RELAYER_JOBMAX;i++){
		if(rel_job[i] != NULL){
			relayer_job_destroy(i);
		}
	}
	pthread_mutex_destroy(&mut_rel_job);
}
static void module_load(void){
	int err;
	err = pthread_create(&tid_relayer,NULL,&thr_relayer,NULL);
	if(err){
		fprintf(stderr,"pthread_create():%s \n",strerror(err));
		exit(1);
	}
	atexit(module_unload);
}
static int find_free_pos_unlocked(void){
	int i;
	for(i = 0 ;i<RELAYER_JOBMAX;i++){
		if(rel_job[i] == NULL)
			return i;
	}
	return -1;
}
int relayer_addjob(int fd1,int fd2){
	relayer_job *me;
	int pos;
	
	pthread_once(&init_once,module_load);

	me = malloc(sizeof(*me));
	if(me == NULL)
		return -ENOMEM;
	me->fd1 = fd1;
	me->fd2 = fd2;
	me->job_state = STATE_RUNNING;
	me->fd1_save = fcntl(me->fd1,F_GETFL);
	me->fd2_save = fcntl(me->fd2,F_GETFL);	
	fcntl(me->fd1,F_SETFL,me->fd1_save|O_NONBLOCK);
	fcntl(me->fd2,F_SETFL,me->fd2_save|O_NONBLOCK);
	
	me->fsm12.sfd = me->fd1;
	me->fsm12.dfd = me->fd2;
	me->fsm12.state = STATE_R;

	me->fsm21.sfd = me->fd2;
	me->fsm21.dfd = me->fd1;
	me->fsm21.state = STATE_W;
	pthread_mutex_init(&me->mut,NULL);
	pthread_cond_init(&me->cond,NULL);

	pthread_mutex_lock(&mut_rel_job);
	pos = find_free_pos_unlocked();
	if(pos < 0 ){
		pthread_mutex_unlock(&mut_rel_job);
		fcntl(me->fd1,F_SETFL,me->fd1_save);
		fcntl(me->fd2,F_SETFL,me->fd2_save);

		pthread_mutex_destroy(&me->mut);
		pthread_cond_destroy(&me->cond);
		free(me);
		return -ENOSPC;
	}
	rel_job[pos] = me;
	pthread_mutex_unlock(&mut_rel_job);
	return pos;
}
int relayer_canceljob(int id){
	if(id < 0 || id > RELAYER_JOBMAX)
		return -EINVAL;
	relayer_job *me = rel_job[id];
	if(me == NULL)
		return -EINVAL;
	int ret;
	pthread_mutex_lock(&mut_rel_job);
	pthread_mutex_lock(&me->mut);
	if(me->job_state == STATE_RUNNING){
		me->job_state = STATE_CANCELED;
		ret = 0;
	}else if(me->job_state == STATE_CANCELED){
		ret = -ECANCELED;
	}else if(me->job_state == STATE_OVER){
		ret = -EBUSY;
	}
	pthread_mutex_unlock(&me->mut);
	pthread_mutex_unlock(&mut_rel_job);
	return ret;
}
int relayer_statjob(int id,struct relayer_stat_st *ptr){
	if(id < 0 || id > RELAYER_JOBMAX)
		return -EINVAL;
	relayer_job *me = rel_job[id];
	if(me == NULL)
		return -EINVAL;
	ptr->fd1 = me->fd1;
	ptr->fd2 = me->fd2;
	pthread_mutex_lock(&mut_rel_job);
	pthread_mutex_lock(&me->mut);
	ptr->state = me->job_state;
	ptr->count12 = me->fsm12.wcount;
	ptr->count21 = me->fsm21.wcount;
	pthread_mutex_unlock(&me->mut);
	pthread_mutex_unlock(&mut_rel_job);
	return 0;
}
int relayer_waitjob(int id,struct relayer_stat_st *ptr){
	if(id < 0 || id > RELAYER_JOBMAX)
		return -EINVAL;
	relayer_job *me = rel_job[id];
	if(me == NULL)
		return -EINVAL;
	ptr->fd1 = me->fd1;
	ptr->fd2 = me->fd2;
	pthread_mutex_lock(&mut_rel_job);
	while(me->fsm12.state != STATE_OVER && me->fsm21.state != STATE_OVER) 
		pthread_cond_wait(&me->cond,&me->mut);
	ptr->state = me->job_state;
	ptr->count12 = me->fsm12.wcount;
	ptr->count21 = me->fsm21.wcount;
	pthread_mutex_unlock(&mut_rel_job);
	return 0;
}

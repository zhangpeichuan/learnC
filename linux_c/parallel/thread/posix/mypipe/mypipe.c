#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <errno.h>
#include "mypipe.h"

typedef struct mypipe_st{
	int		head;
	int		tail;
	char	data[PIPESIZE];
	int		datasize;
	int		count_r,count_w;
	pthread_mutex_t	mut;
	pthread_cond_t	cond;
}MY_PIPE;

int mypipe_register(mypipe_t *ptr,int opmap){
	MY_PIPE *me = ptr;

	pthread_mutex_lock(&me->mut);
	if(opmap & MYPIPE_READ)
		me->count_r++;
	if(opmap & MYPIPE_WRITE)
		me->count_w++;
	
	pthread_cond_broadcast(&me->cond);
	
	while(me->count_r <=0 || me->count_w <= 0)
		pthread_cond_wait(&me->cond,&me->mut);
	pthread_mutex_unlock(&me->mut);
	return 0;
}
int mypipe_unregister(mypipe_t *ptr,int opmap){
	MY_PIPE *me = ptr;
	pthread_mutex_lock(&me->mut);
	if(opmap & MYPIPE_READ);
		me->count_r--;
	if(opmap & MYPIPE_WRITE)
		me->count_w--;
	pthread_cond_broadcast(&me->cond);
	pthread_mutex_unlock(&me->mut);
}
mypipe_t *mypipe_init(void){
	MY_PIPE *me;
	me = malloc(sizeof(*me));
	if(me == NULL)
		return NULL;
	me->head = 0;
	me->tail = 0;
	me->count_r = 0;
	me->count_w = 0;
	me->datasize = 0;
	pthread_mutex_init(&me->mut,NULL);
	pthread_cond_init(&me->cond,NULL);
	return me;

}
static int next(int head){
	int loophead = head;
	if(loophead >= PIPESIZE)
		loophead = loophead%PIPESIZE;
	return loophead;
}
static int mypipe_writebyte_unlocked(MY_PIPE *me,char *datap){
	if(me->datasize >= PIPESIZE)
		return -1;
	me->data[me->tail] = *datap;
	me->tail = next(me->tail+1);
	me->datasize++;
	return 0;
}
static int mypipe_readbyte_unlocked(MY_PIPE *me,char *datap){
	if(me->datasize <=0)
		return -1;
	*datap = me->data[me->head];
	me->head = next(me->head+1);
	me->datasize--;
	return 0;
}
int mypipe_read(mypipe_t *ptr,void *buf,size_t count){
	MY_PIPE *me = ptr;
	int i,num;
	pthread_mutex_lock(&me->mut);
	//数据为空，有写者，进入等待
	while(me->datasize <=0 && me->count_w >0)
		pthread_cond_wait(&me->cond,&me->mut);
	//数据为空，没有写者，退出
	if(me->datasize<= 0 && me->count_w <=0){
		pthread_mutex_unlock(&me->mut);
		return 0;
	}
	
	for(i = 0;i < count;i++){
		if(mypipe_readbyte_unlocked(me,buf+i) !=0)
			break;
		num +=i;
	}
	pthread_cond_broadcast(&me->cond);
	pthread_mutex_unlock(&me->mut);
	
	return num;
}
int mypipe_write(mypipe_t *ptr,const void *buf,size_t count){
	MY_PIPE *me = ptr;
	char *buffer = (char *)buf;
	int i,num;
	pthread_mutex_lock(&me->mut);
	//数据满，有读者，进入等待
	while(me->datasize >= PIPESIZE && me->count_w>=0)
		pthread_cond_wait(&me->cond,&me->mut);
	//数据满，没有读者，退出
	if(me->datasize >= PIPESIZE && me->count_w < 0){
		pthread_mutex_unlock(&me->mut);
		return 0;
	}
	for(i = 0;i < count;i++){
		if(mypipe_writebyte_unlocked(me,buffer+i) != 0)
			break;
		num +=i;
	}
	pthread_cond_broadcast(&me->cond);
	pthread_mutex_unlock(&me->mut);
	return num;
}
int mypipe_destroy(mypipe_t *ptr){
	MY_PIPE *me = ptr;
	pthread_mutex_destroy(&me->mut);
	pthread_cond_destroy(&me->cond);
}

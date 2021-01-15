#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include "pipeopen.h"
#include "mypipe.h"
struct pipeopen_st{
	mypipe_t	*pipe;
	int		mode;
};
static struct pipeopen_st *pipe_job[PIDMAX];
static int find_free_pos(void){
	int i;
	for(i=0;i<PIDMAX;i++){
		if(pipe_job[i]==NULL)
			return i;
	}
	return -1;
}

int pid_open(mode_t mode){
	int pos;
	pos = find_free_pos();
	if(pos < 0){
		return pos;
	}
	struct pipeopen_st *me;
	me = malloc(sizeof(*me));
	if(me == NULL)
		return -1;
	mypipe_t *pipe = mypipe_init();
	if(pipe == NULL){
		free(me);
		return -1;
	}
	me->pipe=pipe;
	if(mode & O_RDONLY)
		me->mode = MYPIPE_READ;
	if(mode & O_WRONLY)
		me->mode = MYPIPE_WRITE;
	if(mode & O_RDWR)
		me->mode = MYPIPE_RDWR;
	pipe_job[pos] = me;
	return pos;
}

int pid_read(int pid,void *buf,size_t count){
	struct pipeopen_st *me = pipe_job[pid];
	if(me == NULL || me->pipe == NULL)
		return -1;

	if(me->mode & MYPIPE_READ){
		mypipe_read(me,&buf,count);
	}
	return -1;
}	

int pid_write(int pid,const void *buf,size_t count){
	struct pipeopen_st *me = pipe_job[pid];
	if(me == NULL || me->pipe == NULL)
		return -1;
	if(me->mode & MYPIPE_WRITE)
		mypipe_write(me,buf,count);
	return -1; 
}

void pid_close(int pid){
	struct pipeopen_st *me = pipe_job[pid];
	free(me);
}





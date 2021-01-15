#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include "pipeopen.h"

#define	THRNUM	2
static int pid1,pid2;
static pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
static pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
static void *thr_fun(void *p){
	char *buf[6];
	if(pid_read(pid1,buf,6)<=0)
		;
	fprintf(stdout,"read buf %s\n",buf);
	pthread_exit(NULL);
}
static void *thr_fun1(void *p){
	char *buf[6];
	if(pid_write(pid2,"Hello",6)<=0)
		;
	fprintf(stdout,"write buf\n");
	pthread_exit(NULL);
}
int main(){
	pthread_t tid[2];
	pid1 =pid_open(O_RDONLY);
	if(pid1 < 0){
		perror("pid_open()");
		exit(1);
	}
	pid2 =pid_open(O_WRONLY);
	if(pid2 <0){
		pid_close(pid1);
		exit(1);
	}
	pthread_create(&tid[0],NULL,thr_fun,NULL);
	pthread_create(&tid[1],NULL,thr_fun1,NULL);
	sleep(1);
	wait(NULL);
	exit(1);

}

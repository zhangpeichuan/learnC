#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


#define	FNAME	"/tmp/out"
static void daemon_exit(int s){

    fprintf(stdout,"int_handler sig=%d\n",s);
	//signal多种信号调用同个方法 发生信号重入
	//fclose(fp);
	closelog();
	exit(0);
}
static int daemonize(void){
	int fd;
	pid_t pid;
	pid = fork();
	if(pid < 0){
		return -1;
	}
	if(pid>0)//parent
		exit(0);
	fd = open("/dev/null",O_RDWR);
	if(fd < 0){
		return -1;
	}
	dup2(fd,0);
	dup2(fd,1);
	dup2(fd,2);

	if(fd > 2)
		close(fd);
	setsid();
	chdir("/");
//	umask(0);

	return 0;
}
static	FILE *fp;

int main(){
	int i;
	struct sigaction sa;
	
	openlog("mydaemon",LOG_PID,LOG_DAEMON);
	if(daemonize()){
		syslog(LOG_ERR,"daemonize() failed");
		exit(1);
	}else{
		syslog(LOG_INFO,"daemonize() successed!");
	}
	fp = fopen(FNAME,"w");
	if(fp == NULL){
		syslog(LOG_ERR,"fopen() %s",strerror(errno));
		exit(1);
	}
	syslog(LOG_INFO,"%s was opened()",FNAME);
	
	sa.__sigaction_u.__sa_handler = daemon_exit;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask,SIGQUIT);
	sigaddset(&sa.sa_mask,SIGTERM);
	sigaddset(&sa.sa_mask,SIGINT);
	sa.sa_flags = 0;

	sigaction(SIGINT,&sa,NULL);
	sigaction(SIGQUIT,&sa,NULL);
	sigaction(SIGTERM,&sa,NULL);

	/* 
	signal(SIGINT,daemon_exit);//有重入的危险
	signal(SIGQUIT,daemon_exit);
	signal(SIGTERM,daemon_exit);
	*/
	for(i=0;;i++){

		fprintf(fp,"%d\n",i);
		fflush(fp);
		syslog(LOG_DEBUG,"%d is printed.",i);
		sleep(1);
	}

	return 0;
}

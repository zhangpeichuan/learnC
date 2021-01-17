#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "proto.h"

#define	MAXCLIENTS	200

static pthread_t tid[MAXCLIENTS];	
static void *client_job(void *p){
	FILE	*fp;
	struct sockaddr_in raddr;
	long long	stamp;
	int sd;
	char	*argv = (char*)p;
	sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd < 0){
		perror("socket()");
		exit(1);
	}
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(SERVERPORT));
	inet_pton(AF_INET,argv,&raddr.sin_addr);
	if(connect(sd,(void *)&raddr,sizeof(raddr)) < 0){
		
		perror("connect()");
		exit(1);
	}
	fp = fdopen(sd,"r+");
	if(fp == NULL){
		perror("fdopen()");
		exit(1);
	}
	if(fscanf(fp,FMT_STAMP,&stamp) < 1){
		fprintf(stderr,"Bad format!\n");
	}else{
		fprintf(stdout,"stamp = %lld\n",stamp);
	}
	sleep(1);
	fclose(fp);

	pthread_exit(NULL);
}
int main(int argc,char *argv[]){
	if(argc < 2 ){
		fprintf(stderr,"Usage...\n");
		exit(1);
	}
	int i;
	for(i = 0;i< MAXCLIENTS;i++){
		pthread_create(tid+(i),NULL,client_job,(void *)argv[1]);	
	}
	for(i = 0;i< MAXCLIENTS;i++){
		pthread_join(tid[i],NULL);
	}
	

	exit(1);
}

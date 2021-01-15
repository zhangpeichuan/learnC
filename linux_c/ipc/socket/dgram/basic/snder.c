#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <string.h>

#include "proto.h"

int main(int argc,char *argv[]){
	if(argc < 2){
		fprintf(stdout,"Usage: ........");
		exit(0);
	}
	int sd;
	struct msg_st sbuf;
	struct sockaddr_in raddr;
	socklen_t raddr_len;

	sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd < 0){
		perror("socket()");
		exit(1);
	}
	
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET,argv[1],&raddr.sin_addr);
	raddr_len = sizeof(raddr);
	
	sbuf.math = htonl(rand()%100);
	sbuf.chinese = htonl(rand()%100);
	strcpy(sbuf.name,"zhangsan");	
	
	//bind()
	if(sendto(sd,&sbuf,sizeof(sbuf),0,(void *)&raddr,raddr_len) < 0){
		perror("sendto()");
		exit(1);
	}
	puts("OK");
	close(sd);


}




#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <time.h>
#include <wait.h>
#include "proto.h"
#define	IPSTRSIZE	40
#define	BUFSIZE		1024
#define	PROCNUM		3
static void server_loop(int sd);
static void server_job(int sd){
	char	buf[BUFSIZE];
	int		len;
	len = sprintf(buf,FMT_STAMP,(long long)time(NULL));
	if(send(sd,buf,len,0)< 0){
		perror("send()");
		exit(1);
	}
}
int main(){
	int	 sd,i,pid;
	//1、创建socket
	sd = socket(AF_INET,SOCK_STREAM,0);/*IPPROTO_TCP,IPPROTO_SCTP*/	
	if(sd < 0){
		perror("socket()");
		exit(1);
	}
	//避免意外杀死进程后，资源未释放，导致无法绑定端口成功
	int val = 1;
	if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val)) < 0){
		perror("setsockopt()");
		exit(1);
	}
	struct		sockaddr_in laddr;
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(SERVERPORT));
	inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr);
	///2、地址端口BIND
	if(bind(sd,(void *)&laddr,sizeof(laddr))<0){
		perror("bind()");
		exit(1);
	}
	//3、监听
	if(listen(sd,200)<0){
		perror("listen()");
		exit(1);
	}
	for(i = 0;i < PROCNUM ;i++){
		pid = fork();
		if(pid < 0){
			perror("fork()");
			exit(1);
		}
		if(pid == 0){
			server_loop(sd);
			exit(0);
		}
	}
	for(i = 0;i<PROCNUM;i++){
		wait(NULL);
	}
	close(sd);
	exit(0);
}
static void server_loop(int sd){
	char		ipstr[IPSTRSIZE];
	int			newsd;
	struct		sockaddr_in raddr;
	socklen_t	raddr_len;
	//4、接收连接
	raddr_len = sizeof(raddr);
	while(1){
		newsd = accept(sd,(void *)&raddr,&raddr_len);
		if(newsd < 0){
			perror("accept()");
			exit(1);
		}
		inet_ntop(AF_INET,&raddr.sin_addr,ipstr,IPSTRSIZE);
		printf("proc[%d] Clent:%s:%d\n",getpid(),ipstr,ntohs(raddr.sin_port));
		
		//发送消息
		server_job(newsd);	
		//关闭连接
		close(newsd);
	}
}

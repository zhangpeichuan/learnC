#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/mman.h>
#include <time.h>
#include <errno.h>
#include "proto.h"

#define	MINSPARESERVER	5
#define	MAXSPARESERVER	10
#define	MAXCLIENTS		20

#define	MAXREUSE		1000

#define	SIG_NOTIFY		SIGUSR2
#define	BUFSIZE			1024
enum {
	STATE_IDEL = 0,
	STATE_BUSY	
};

struct server_st{
	pid_t	pid;
	int		state;
	int		reuse;
};
static struct server_st *serverpool;
static int idle_count = 0,busy_count = 0,sd;

//信号回调
static void usr2_handler(int s){
	
	return ;
}
static void server_job(int pos){
	int ppid,client_sd,err,len;
	struct sockaddr_in raddr;
	char	buf[BUFSIZE];
	socklen_t	raddr_len;
	ppid = getppid();
	while(1)
	{
		//创建完成后给父进程发送通知信号，
		serverpool[pos].state = STATE_IDEL;
		kill(ppid,SIG_NOTIFY);
		//接收连接
		client_sd = accept(sd,(void *)&raddr,&raddr_len);
		if(client_sd < 0){
			if(errno != EINTR || errno != EAGAIN){
				perror("accept()");
				exit(1);
			}
		}
		//接收到客户端的连接后，通知父进程，更改自身状态
		serverpool[pos].state = STATE_BUSY;
		kill(ppid,SIG_NOTIFY);
		//打印客户端信息
		inet_ntop(AF_INET,&raddr.sin_addr,buf,BUFSIZE);
		//printf("[%d] Client%s:%d\n",getpid(),buf,ntohs(raddr.sin_port));

		long long stamp = time(NULL);
		len = snprintf(buf,BUFSIZE,FMT_STAMP,stamp);
		err = send(client_sd,buf,len,0);
		if(err < 0){
			fprintf(stdout,"client_sd[%d] send() failed %d\n",serverpool[pos].pid,err);	
		}else {
			printf("ServerClient_sd[%d] send() success\n",serverpool[pos].pid);
		}
		sleep(2);
		close(client_sd);
	}	

}
//新增一个Server进程
static int add_1_server(void){
	if(idle_count + busy_count >= MAXCLIENTS)
		return -1;
	int pid,slot;
	for(slot = 0;slot < MAXCLIENTS;slot++){
		if(serverpool[slot].pid == -1)
			break;
	}
	serverpool[slot].state = STATE_IDEL;
	pid = fork();
	if(pid < 0){
		perror("fork()");
		exit(1);
	}
	if(pid == 0){//child
		server_job(slot);
		exit(0);
	}else{//parent
		serverpool[slot].pid = pid;
		idle_count++;
	}
	return 0;
}	
//删除一个Server线程
static int del_1_server(void){
	int i;
	if(idle_count == 0)
		return -1;
	for(i = 0;i<MAXCLIENTS;i++){
		if(serverpool[i].pid != -1 && serverpool[i].state == STATE_IDEL){
			kill(serverpool[i].pid,SIGTERM);
			serverpool[i].pid = -1;
			idle_count--;
			break;
		}
	}
	return 0;
}
//遍历池
static int scan_pool(void){
	int idle,busy,i;
	for(i = 0;i<MAXCLIENTS;i++){
		if(serverpool[i].pid == -1)
			continue;
		if(kill(serverpool[i].pid,0)){
			serverpool[i].pid = -1;
			continue;
		}
		if(serverpool[i].state == STATE_IDEL){
			idle++;
		}else if(serverpool[i].state == STATE_BUSY){
			busy++;
		}else{
			//异常状态退出
			abort();
		}
	}
	idle_count = idle;
	busy_count = busy;
	return 0;
}
int main(){
	int val = 1,i;
	struct sigaction sa,osa;
	struct sockaddr_in laddr;
	sigset_t set,oset;	
	
	
	//创建子进程，不需要父进程收尸
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD,&sa,&osa);
	
	sa.sa_handler = usr2_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIG_NOTIFY,&sa,&osa);
	
	sigemptyset(&set);
	sigaddset(&set,SIG_NOTIFY);
	sigprocmask(SIG_BLOCK,&set,&oset);

	//动态申请内存
	serverpool = mmap(NULL,sizeof(struct server_st) *MAXCLIENTS,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if(serverpool == MAP_FAILED){
		perror("mmap()");
		exit(1);
	}
	for(i = 0;i < MAXCLIENTS;i++){
		serverpool[i].pid = -1;
	}
	//创建流式套接字
	sd = socket(AF_INET,SOCK_STREAM,0);
	if(sd < 0){
		perror("socket()");
		exit(1);
	}
	//setSockOpt，重用资源，避免异常退出后地址和端口不能正常访问
	val = 1;
	if(setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val)) < 0){
		perror("setsockopt()");
		exit(1);
	}
	//绑定地址端口和协议
	laddr.sin_family=AF_INET;
	laddr.sin_port = htons(atoi(SERVERPORT));
	inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr);
	if(bind(sd,(void *)&laddr,sizeof(laddr)) < 0){
		perror("bind()");
		exit(1);
	}
	//启动监听
	if(listen(sd,100)< 0){
		perror("listen()");
		exit(1);
	}
	//创建线程池	
	for(i =0;i<MINSPARESERVER;i++){
		add_1_server();
	}
	//等待监听信号
	while(1){
		//信号唤醒当前操作
		sigsuspend(&oset);
		//查看进程池
		scan_pool();
		
		//contrl the pool
		if(idle_count > MAXSPARESERVER){
			for(i = 0;i < (idle_count - MAXSPARESERVER);i++)
				del_1_server();
		}else if(idle_count < MINSPARESERVER){
			for(i = 0;i< (idle_count - MINSPARESERVER);i++)
				add_1_server();
		}
		
		//print pool
		for(i =0;i<MAXCLIENTS;i++){
			if(serverpool[i].pid == -1)
				putchar(' ');
			else if(serverpool[i].state == STATE_IDEL){
				putchar('.');
			}else{
				putchar('x');
			}
		}
		putchar('\n');
	}
	sigprocmask(SIG_SETMASK,&oset,NULL);



	exit(0);
}

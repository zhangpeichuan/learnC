#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <errno.h>


#include "client.h"
void my_getopt_long(int argc,char **argv);
void client_socket(void);
static void printUsage(void);
//客户端可以进行修改地址
struct client_conf_st client_conf = {\
	.rcvport = DEFAULT_PORT,\
	.mgroup = DEFAULT_MGROUP,\
	.player_cmd = DEFAULT_PLAYCMD};
static int	sd = -1;
static int choseid = 0;
static int writen(int fd,const char *buf,size_t len){
	int pos,ret;
	pos = 0;
	while(ret < 0)
	{
		ret = write(fd,buf+pos,len);
		if(ret < 0){
			if(errno == EINTR){
				continue;
			}
			perror("write()");
			return -1;
		}
		len -=ret;
		pos +=ret;
	}
	return pos;
}
int main(int argc,char **argv){
	int pid,ret;
	int pd[2];
	/*
	 *	初始化
	 *	级别:默认值、配置文件、环境变量、命令行参数
	 *
	 *
	 * */
	int option_index = 0;
	int c;
	struct option long_options[] = {{"port",1,NULL,'P'},{"mgroup",1,NULL,'M'},
		{"player",1,NULL,'P'},{"help",0,NULL,'H'},{NULL,0,NULL,0},{0,0,0,0}};
	while(1){
		c = getopt_long(argc,argv,"P:M:p:H",long_options,&option_index);
		if(c < 0){
			break;
		}
		switch (c){
			case 0:
				printf("option %s", long_options[option_index].name);
				if (optarg)
					printf(" with arg %s", optarg);
				printf("\n");
				break;
			case 'P':
				client_conf.rcvport = optarg;
				break;
			case 'M':
				client_conf.mgroup = optarg;
				break;
			case 'p':
				client_conf.mgroup = optarg;
				break;
			case 'H':
				printUsage();
				exit(0);
				break;
			default:
				abort();
				break;
		}
	}
	//创建客户端Socket连接
	client_socket();
	//创建管道
	if(pipe(pd) < 0){
		perror("pipe()");
		exit(1);
	}
	pid = fork();
	if(pid < 0){
		perror("fork()");
		exit(1);
	}
	if(pid == 0){//子进程:调用解码器
		close(sd);
		close(pd[1]);
		dup2(pd[0],0);
		if(pd[0] >0)
			close(pd[0]);

		execl("/bin/sh","sh","-c",client_conf.player_cmd,NULL);
		perror("execl()");
		exit(1);

	}
	//父进程:网络收取数据包，发送给子进程
	//收节目单
	struct msg_list_st *msg_list;
	msg_list = malloc(MSG_LIST_MAX);
	if(msg_list == NULL){
		perror("malloc()");
		exit(1);
	}
	struct sockaddr_in	serveraddr,raddr;
	socklen_t serveraddr_len=sizeof(serveraddr),raddr_len=sizeof(raddr);
	int len;
	while(1){
		len = recvfrom(sd,msg_list,MSG_LIST_MAX,0,(void *)&serveraddr,&serveraddr_len);
		if(len < MSG_LIST_MAX){
			fprintf(stderr,"message is too small.\n");
			continue;
		}
		if(msg_list->chnid != LISTCHNID){
			fprintf(stderr,"chnid is not match");
			continue;
		}
		break;
	}
	struct msg_listentry_st *pos;
	for(pos = msg_list->entry;(char *)pos < ((char *)msg_list+len);pos = (void *)((char*)pos+ntohs(pos->len)))
		printf("channel %d:%s\n",pos->chnid,pos->desc);
	free(msg_list);
	while(ret < 1){
		ret =scanf("%d",&choseid);
		if(ret != 1){
			exit(1);
		}
	}
		
	//选择频道
	fprintf(stdout,"chooseid = %d\n",ret);
	//收频道包，发送给子进程
	struct msg_channel_st *msg_channel;
	msg_channel = malloc(MSG_CHANNEL_MAX);
	if(msg_channel == NULL){
		perror("malloc()");
		exit(1);
	}

	while(1){
		len = recvfrom(sd,msg_channel,MSG_CHANNEL_MAX,0,(void *)&raddr,&raddr_len);
		if(raddr.sin_addr.s_addr != serveraddr.sin_addr.s_addr || serveraddr.sin_port != raddr.sin_port){
			fprintf(stderr,"Ignor:address not match. \n");
			continue;
		}
		if(len < sizeof(struct msg_channel_st)){
			fprintf(stderr,"Ignor:message too small.\n");
			exit(1);
		}
		//临时缓冲区，保证从SERVER获取的数据到达一定的量后再进行写入
		if(msg_channel->chnid == choseid){
			fprintf(stdout,"accepted msg:%d recieved",msg_channel->chnid);
			if(writen(pd[1],msg_channel->data,len-sizeof(chnid_t)) < 0){
				exit(1);
			}
		}
	}
	free(msg_channel);
	close(sd);
	exit(0);
}

/*
 *	-M	--mgroup	指定多播组
 *	-P	--port		指定接收端口
 *	-p	--player	指定播放解码器
 *	-H	--help		显示帮助
 *
 *命令+选项+非选项
 *cmd -opt --option	
 *
 * */
#define	optstring	"P:M:p:H"
static void printUsage(void){
	printf("参数错误	使用方法\n");
	printf("	-M --mgroup 指定多播组\n");
	printf("	-P --port	指定接收端口\n");
	printf("	-p --player 指定播放器\n");
	printf("	-H --help	显示帮助\n ");
}
void client_socket(void){
	int val = 0;
	struct ip_mreqn mreq; 
	struct sockaddr_in	laddr;
	sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd < 0){
		perror("socket()");
		exit(1);
	}
	if(inet_pton(AF_INET,client_conf.mgroup,&mreq.imr_multiaddr) != 1){
		perror("inet_pton");
		exit(1);
	}
	inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
	//指定网卡设备号
	mreq.imr_ifindex= if_nametoindex("enp0s3");
	if(setsockopt(sd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0){
		perror("setsockopt()");
		exit(1);
	}
	/*
	val = 1;
	if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_LOOP,&val,sizeof(val) < 0)){
		perror("setsockopt()");
		exit(1);
	}*/
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(client_conf.rcvport));
	inet_pton(AF_INET,"0.0.0.0",&laddr.sin_addr.s_addr);
	if(bind(sd,(void *)&laddr,sizeof(laddr)) < 0){
		perror("bind()");
		exit(1);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>


#define	BUFSIZE	100

int main(int argc,char **argv){


	if(argc < 3){
		fprintf(stderr,"Usage ..........");
		exit(1);
	}
	char buf[BUFSIZE];
	int sfd,dfd;
	int len,ret,pos;
	len = -1;
	sfd = open(argv[1],O_RDONLY);
	if(-1 == sfd){
		perror("open()");
		exit(1);
	}
	dfd = open(argv[2],O_WRONLY|O_CREAT,0600);
	if(-1 ==  dfd){
		close(sfd);
		perror("open()");
		exit(1);
	}
	while(len){
		len = read(sfd,&buf,BUFSIZE);
		printf("len %d \n",len);
		if(-1 == len){
			perror("read()");
			break;
		}else if(0 == len){
			perror("len=0");
			break;
		}else {
			pos = 0;
			int tmp = len;
			while(tmp >0)
			{
			ret = write(dfd,buf+pos,tmp);
			if(-1 == ret ){
				perror("write()");
				exit(1);
			}else if( 0 ==ret){
				printf("write ret = 0");
			}else{
				perror("write()");
			}
			printf("write ret =%d\n",ret);
			pos +=ret;
			tmp -=ret;

			}
		}
	}
	getchar();

	close(dfd);
	close(sfd);
	printf("close dfd sfd");
	exit(0);
}


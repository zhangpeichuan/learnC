#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	BUFSIZE	1024
int main(){
	int pd[2];
	pid_t pid;
	int len;
	char	buf[BUFSIZE];;
	if(pipe(pd)<0){
		perror("pipe()");
		exit(0);
	}

	pid =fork();
	if(pid <0){
		perror("fork()");
		exit(0);
	}
	if(pid == 0){//child read
		close(pd[1]);//关闭写端
		dup2(pd[0],0);
		close(pd[0]);
		fd = open("/dev/null",O_RDWR);
		dup2(fd,1);
		dup2(fd,2);
		exec("/usr/bin/mpg123","mpg123","-",NULL);
		perror("execl()");
		exit(0);
	}else{//parent write
		close(pd[0]);//关闭读端
		//父进程从网上收数据，往管道中写
		
		close(pd[1]);
		exit(1);
	
	}
	exit(0);
}

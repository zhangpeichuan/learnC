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
		close(pd[1]);
		len = read(pd[0],buf,BUFSIZE);
		write(1,buf,len);
		close(pd[0]);
		exit(1);
	}else{//parent write
		close(pd[0]);
		write(pd[1],"Hello World!\n",13);
		close(pd[1]);
		exit(1);
	
	}
	exit(0);
}

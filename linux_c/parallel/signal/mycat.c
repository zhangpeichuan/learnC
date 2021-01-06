#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <signal.h>
#include <sys/errno.h>

#define	BUFSIZE	100
int main(int argc,char **argv){

    if(argc < 2){
        fprintf(stderr,"Usage ..........");
        exit(1);
    }
    char buf[BUFSIZE];
    int sfd,dfd=1;
    int len,ret,pos;
    len = -1;
    do 
    {
        sfd = open(argv[1],O_RDONLY);
        if(sfd <0 ){
            if (errno != EINTR)
            {
                perror("open()");
                exit(1);		
            }


        }
    }while(sfd <0);
    while(len){
        len = read(sfd,&buf,BUFSIZE);
        if(-1 == len){
            if(errno == EINTR)
              continue;
            perror("read()");
            break;
        }
		if (len == 0)
			break;
		
        pos = 0;
        int tmp = len;
        while(tmp >0)
        {
            ret = write(dfd,buf+pos,tmp);
            if(-1 == ret ){
                if(errno == EINTR)
                  continue;
                perror("write()");
                exit(1);
            }
            pos +=ret;
            tmp -=ret;

        }

    }

    close(sfd);
    exit(0);
}


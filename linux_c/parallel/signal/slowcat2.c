#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <signal.h>
#include <sys/errno.h>

#define CPS     10
#define	BUFSIZE	CPS

#define BURST   100
static volatile int token = 0;
static void alrm_handler(int s){
    alarm(1);
    if(token < BURST)
        token ++;
    
    
}
int main(int argc,char **argv){
    char buf[BUFSIZE];
    int sfd,dfd=1;
    int len,ret,pos;
    len = -1;

    if(argc < 2){
        fprintf(stderr,"Usage ..........");
        exit(1);
    }
    signal(SIGALRM,alrm_handler);
    alarm(1);
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
        while (token <=0)
            pause();//去掉忙等
        token--;
        //令牌桶设计 buffer cache
        while ((len = read(sfd,&buf,BUFSIZE)) < 0)
        {
            if(errno == EINTR)
              continue;
            perror("read()");
            break;
        }
  
        if(len == 0)
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


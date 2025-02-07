#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <signal.h>
#include <sys/errno.h>
#include <sys/time.h>

#define CPS     10
#define	BUFSIZE	CPS
static volatile int loop = 0;
static void alrm_handler(int s){
    //alarm(1);
    loop = 1;
}
int main(int argc,char **argv){
    char buf[BUFSIZE];
    int sfd,dfd=1;
    int len,ret,pos;
    len = -1;
    
    struct itimerval itv;
    if(argc < 2){
        fprintf(stderr,"Usage ..........");
        exit(1);
    }
    signal(SIGALRM,alrm_handler);
    //alarm(1);
    itv.it_interval.tv_sec = 1;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 1;
    itv.it_value.tv_usec = 0;
    if(setitimer(ITIMER_REAL,&itv,NULL) <0){
        perror("setitimer()");
        exit(1);
    }
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
        while (!loop)
            pause();//去掉忙等
        loop=0;
        //漏桶设计 buffer cache
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


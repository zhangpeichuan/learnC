#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <signal.h>

static void int_handler(int s){
    write(1,"!",1);
    fprintf(stdout,"int_handler sig=%d\n",s);
}
int main(){
    int i,j;
    //signal(SIGINT,SIG_IGN);//ctr+\ quit信号
    sigset_t    set,oset;
    sigset_t    save_set;
    
    signal(SIGINT,int_handler);
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_UNBLOCK,&set,&save_set);//系统之前的saveset需要保存
    for ( j = 0; j < 1000; j++)
    {
        sigprocmask(SIG_BLOCK,&set,&oset);
        for (i = 0; i < 10; i++)
        {
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        sigprocmask(SIG_SETMASK,&oset,NULL);

    }
    sigprocmask(SIG_SETMASK,&save_set,NULL);//过后恢复之前保存的saveset
    

    


    return 0;
}
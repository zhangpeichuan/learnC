/*
 * @Author: your name
 * @Date: 2021-01-07 19:09:45
 * @LastEditTime: 2021-01-07 20:20:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /learnC/linux_c/parallel/signal/susp.c
 */
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
    sigprocmask(SIG_BLOCK,&set,&oset);
    for ( j = 0; j < 100; j++)
    {
        for (i = 0; i < 5; i++)
        {
            write(1,"*",1);
            sleep(1);
        }
        write(1,"\n",1);
        sigsuspend(&oset);
        /*
        sigset_t tmpset;
        sigprocmask(SIG_SETMASK,&oset,&tmpset);
        pause();
        sigprocmask(SIG_SETMASK,&tmpset,NULL);
        */
    }
    sigprocmask(SIG_SETMASK,&save_set,NULL);//过后恢复之前保存的saveset
    

    


    return 0;
}
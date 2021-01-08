/*
 * @Author: your name
 * @Date: 2021-01-07 06:23:48
 * @LastEditTime: 2021-01-07 11:44:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /learnC/linux_c/parallel/signal/anytimer/anytime.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#include "anytime.h"

typedef void(*anytime_handler)(void *);
typedef enum{
    job_flag_runing,
    job_flag_stop
}job_flag;
typedef struct{
    int             second;
    anytime_handler *handler;
    char            *argv;
    int             pos;

}job_st;


int at_addjob(int sec,at_jobfunc_t *jobp,void * argv){
    job_st *me = malloc(sizeof(*me));

    me->second = sec;
    me->handler = jobp;
    strcpy(me->argv,argv);


    return me;
}

#include <stdio.h>
#include <stdlib.h>
//gcc -E 观察预处理结果
enum day
{
    MON = 1,
    TUS,
    THR,
    WES,
    FRI = 1,
    SAT,
    SUN
};
enum
{
    STATE_RUNNING = 1,
    STATE_CANCELED,
    STATE_OVER
};
struct job_st
{
    int     id;
    int     state;
    time_t  start,end;
};
int main(){
    struct job_st job1;
/* 获取任务状态*/
    job1.state = STATE_OVER;
    switch(job1.state)
    {
        case STATE_RUNNING:
            break;
        case STATE_CANCELED:
            break;
        case STATE_OVER:
            break;
        default:
            abort();
            break;
    }


#if 0
    enum day a =MON;
    printf("%d \n",a);
    a = FRI;
    printf("%d \n",a);
    a = SUN;
    printf("%d \n",a);
#endif



    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
//资源竞争和冲突
#define THRNUM 4

static int num = 0;
//忙等num值得变化，这个是通过查询法进行分配任务，优化点改为通知法
static pthread_mutex_t mut_num = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_num = PTHREAD_COND_INITIALIZER;

static void *thr_prime(void *p);
int main()
{
    int i, err;

    pthread_t tid[THRNUM];
    for (i = 0; i < THRNUM; i++)
    {

        err = pthread_create(tid + (i), NULL, thr_prime, (void *)i);
        if (err)
        {
            fprintf(stderr, "pthread_create(): %s \n", strerror(err));
            exit(1);
        }
    }
    for (i = LEFT; i <= RIGHT; i++)
    {
        pthread_mutex_lock(&mut_num);
        while (num != 0)
        {
			pthread_cond_wait(&cond_num,&mut_num);
        }
        num = i;
		pthread_cond_signal(&cond_num);
        pthread_mutex_unlock(&mut_num);
    }
    pthread_mutex_lock(&mut_num);
    while (num != 0)
    {
		pthread_cond_wait(&cond_num,&mut_num);
    }
    num = -1;
	pthread_cond_broadcast(&cond_num);
    pthread_mutex_unlock(&mut_num);

    for (i = 0; i < THRNUM; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&mut_num);
    pthread_cond_destroy(&cond_num);
	exit(0);
}
static void *thr_prime(void *p)
{
    int i, j, mark;
    while (1)
    {
        pthread_mutex_lock(&mut_num);
        while (num == 0)
        {
			pthread_cond_wait(&cond_num,&mut_num);
        }
        if (num == -1)//解锁后再跳转
        {
            pthread_mutex_unlock(&mut_num);
            break;
        }
        i = num;
        num = 0;
		pthread_cond_broadcast(&cond_num);
        pthread_mutex_unlock(&mut_num);

        mark = 1;
        for (j = 2; j < i / 2; j++)
        {
            if (i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if (mark)
        {
            printf("[%d]%d is a primer \n",(int)p, i);
        }
    }

    //sleep(1000);
    pthread_exit(NULL);
}

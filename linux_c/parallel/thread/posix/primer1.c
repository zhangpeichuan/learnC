#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>

#define LEFT 30000000
#define RIGHT 30000200
//分块法
#define THRNUM 3

struct thr_arg_st
{
    int num_left;
    int num_right;
    int index;
};

static void *thr_prime(void *p);
int main()
{
    int i, err;
    pthread_t tid[THRNUM];
    struct thr_arg_st *p;
    void *ptr;
    for (i = 0; i < THRNUM; i++)
    {
        p = malloc(sizeof(*p));
        if (p == NULL)
        {
            perror("malloc()");
            exit(1);
        }
        p->index = i;
        p->num_left = LEFT+i * (RIGHT - LEFT) / 3;
        p->num_right = LEFT+(i + 1) * (RIGHT - LEFT) / 3;
        err = pthread_create(tid + i, NULL, thr_prime, p);
        if (err)
        {
            fprintf(stderr, "pthread_create(): %s \n", strerror(err));
            exit(1);
        }
    }
    for (i = 0; i < THRNUM; i++)
    {
        pthread_join(tid[i], &ptr);
        free(ptr);
    }
    exit(0);
}
static void *thr_prime(void *p)
{
    int i, j, mark;
    struct thr_arg_st *q = (struct thr_arg_st *)p;
    printf(" %d\n",q->num_right);
    for (i = q->num_left; i < q->num_right; i++)
    {
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
            printf("%d is a primer \n", i);
        }
    }

    //sleep(1000);
    pthread_exit(p);
}
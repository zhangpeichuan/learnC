#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#define NAMESIZE    32
struct score_st{
    int id;
    char    name[NAMESIZE];
    int     math;
    int     chinese;
};

static void printscore(void *record){
    struct score_st *s = (struct score_st *)record;
    printf("%d %s %d %d\n",s->id,s->name,s->math,s->chinese);
}

int main(void){
    struct score_st   tmp;
    int     i,ret;

    printf("%s %d",__FUNCTION__,__LINE__);
    STACK *st = stack_create(sizeof(struct score_st));
    if(st == NULL)
        exit(1);

    printf("%s %d",__FUNCTION__,__LINE__);
    for(i=0;i<7;i++){
        tmp.id = i;
        snprintf(tmp.name,NAMESIZE,"stu%d",i);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        if(stack_push(st,&tmp))
          exit(1);
    }
    while(ret >= 0){

        ret = stack_pop(st,&tmp);
        printf("%d",ret);
        if(ret == LLIST_ERROR_FLASE){
            break;
        }
        printscore(&tmp);
    }
    stack_destory(st);

    exit(0);
}

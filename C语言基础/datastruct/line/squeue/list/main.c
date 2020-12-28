#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#define NAMESIZE    32 

typedef struct score_st{
        int     id;
        char    name[NAMESIZE];
        int     math;
        int     chinese;
}datatype;
static void printscore(void *record){
    struct score_st *s = (struct score_st *)record;
    printf("%d %s %d %d\n",s->id,s->name,s->math,s->chinese);
}
int main(){
    QUEUE *sq = NULL;
    datatype data;
    int i,ret=0;
    sq = queue_create(sizeof(datatype));
    if(sq == NULL)
        exit(1);
    for(i=0;i<6;i++){
        data.id = i;
        snprintf(data.name,NAMESIZE,"stu%d",i);
        data.math = rand()%100;
        data.chinese = rand()%80;
        ret = queue_en(sq,&data);
        if(ret == -1){
            printf("enqueue failed\n");
        }else{
            printf("enqueue success \n");
        }
    }
    while(1){
        ret = queue_de(sq,&data);
        if(ret == -1){
            printf("dequeue failed\n");
            break;
        }else{
            printf("dequeue success ");
            printscore(&data);
        }
    }

    queue_destory(sq);
    exit(0);
}

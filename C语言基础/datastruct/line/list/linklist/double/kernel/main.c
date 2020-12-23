#include <stdio.h>
#include <stdlib.h>


#include "list.h"
#define NAMESIZE    32

typedef struct score_st{
    int     id;
    char    name[NAMESIZE];
    int     math;
    int     chinese;
    struct  list_head node;
}score;
static void printfs(score *s){
    printf("%d %s %d %d\n",s->id,s->name,s->math,s->chinese);
}
int main(){
    score   *data;
    int i=0;
    struct list_head *cur;
    LIST_HEAD(head);
    for(i = 0;i<7;i++){
        data = malloc(sizeof(*data));
        if(data == NULL)
            exit(1);

        data->id = i;
        snprintf(data->name,NAMESIZE,"stu%d",i);
        data->math = rand()%100;
        data->chinese = rand()%100;
        list_add(&data->node,&head);        
    }
     __list_for_each(cur,&head){
       data = list_entry(cur,struct score_st,node);
       printfs(data);
    }
    __list_for_each(cur,&head){
       data = list_entry(cur,struct score_st,node);
       if(data->id == 100)
            break;
    }
    if(cur == &head)
        printf("can not find!\n");
    else
        printfs(data);
    return 0;
}

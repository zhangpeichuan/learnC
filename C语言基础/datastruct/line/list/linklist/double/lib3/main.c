#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

#define NAMESIZE    32
typedef struct  score_st{
    int     id;
    char    name[NAMESIZE];
    int     math;
    int     chinese;
}score;
static void print_s(const void *r){
    score *p = (score *)r;
    if(p == NULL)
        printf("空数据\n");
    else
        printf("%s %d %s %d %d \n",__FUNCTION__,p->id,p->name,p->math,p->chinese);
}
static int id_cmp(const void *key,const void *record){
    const int *k = key;
    const score *r = record;
    return (*k - r->id);
}
static int name_cmp(const void *key,const void *record){
    const char *k = key;
    const score *r = record;
    return strcmp(k,r->name);

}
int main(){
    LLIST   *handler;
    int     i,ret;
    score data;
    
    llist_create(&handler,sizeof(score));

    for(i=0;i<7;i++){
        data.id = i;
        snprintf(data.name,NAMESIZE,"stu%d",i);
        data.math = rand()%100;
        data.chinese = rand()%100;
		handler->insert(handler,&data,LLIST_MODE_BACKWORD);
    }
        llist_travel(handler,&print_s);
//	handler->travel(handler,&print_s);
    printf("\n\n");
    int id = 6; 
    print_s(llist_find(handler,&id,&id_cmp));
    printf("\n\n");
    ret =llist_delete(handler,&id,&id_cmp);
    if(ret)
        printf("llist_delete failed");
    else{
        llist_travel(handler,&print_s);
    }
    printf("\n\n");
    score *sdata = NULL;
    char name[5] = "stu1";
    ret = llist_fetch(handler,name,&name_cmp,sdata);
    if(ret !=LLIST_ERROR_OK){
        printf("fetch为空");
    }else{
        print_s(sdata);
        printf("找到数据了\n\n");

        llist_travel(handler,&print_s);
    }
	llist_destory(handler);
    return 0;
}

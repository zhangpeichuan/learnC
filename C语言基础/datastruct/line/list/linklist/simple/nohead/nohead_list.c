#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nohead_list.h"

//二级指针直接扩展支持错误返回多种
int list_insert(nohead_list **p,datatype *data){
    
    nohead_list *new;
    new = malloc(sizeof(*new));
    if(new == NULL){
        return -1;
    } 

    new->data = *data;
    new->next = *p;
    *p = new;
    
    return 0;
}
//无头单链表删除，临时保存头节点
int list_delete(nohead_list **p){
    if(*p == NULL)
      return -1;
    nohead_list *cur = *p;
   *p = (*p)->next;
   free(cur);
   return 0;
}
datatype * list_findById(nohead_list *p,int id){
    nohead_list *cur;
     for(cur = p;cur != NULL;cur = cur->next){
         if(cur->data.id == id){
             return &cur->data;
         }
     }
   return NULL;
}


int list_find(nohead_list *p,datatype *data){
    nohead_list *cur;
     for(cur = p;cur != NULL;cur = cur->next){
         if(cur->data.id == data->id && cur->data.math == data->math && cur->data.chinese == data->chinese && (strcmp(cur->data.name,data->name) == 0)){
        printf("list_find id=%d name=%s math=%d chinese=%d\n",cur->data.id,cur->data.name,cur->data.math,cur->data.chinese);
             return 0;
         }
     }
   return -1;
}

int list_display(nohead_list *p){
    nohead_list *cur;
    for(cur = p;cur != NULL;cur = cur->next){
        printf("id=%d name=%s math=%d chinese=%d\n",cur->data.id,cur->data.name,cur->data.math,cur->data.chinese);
    }
    printf("\n");

    return 0;
}
int list_destory(nohead_list *p){
    if(p == NULL)
        return -1;
    nohead_list *q;
    for(q = p;q != NULL; q = p){
        p = q->next;
        free(q);
    }
   return 0;
}





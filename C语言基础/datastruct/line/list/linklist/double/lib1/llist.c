#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"
LL_ERROR llist_create(LLIST **L,int init_size){
    if(*L == NULL)
      return LLIST_ERROR_CREATE;
    LLIST *me = malloc(init_size);
    if(me == NULL)
      return LLIST_ERROR_CREATE;
    me->size = init_size;
    me->head.data = NULL;
    me->head.prev= &me->head;
    me->head.next= &me->head;
    *L = me;
    return LLIST_ERROR_OK;
}
LL_ERROR llist_insert(LLIST *L,const void *data,LL_MODE mode){
    if(L == NULL)
      return LLIST_ERROR_INSERT;

    LNode *newNode = NULL;
    newNode = malloc(sizeof(*newNode));
    if(newNode == NULL)
        return LLIST_ERROR_INSERT;
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->data = malloc(sizeof(L->size));
    memcpy(newNode->data,data,L->size);

    if(mode == LLIST_MODE_FORWARD){
    newNode->prev = &L->head;
    newNode->next = L->head.next;
   }else if(mode == LLIST_MODE_BACKWORD){
    newNode->prev = L->head.prev;
    newNode->next = &L->head;
   }else{
    return LLIST_ERROR_INSERT;
   }
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
    return LLIST_ERROR_OK;
}
static LNode *find_(LLIST *L,const void *key,llist_cmp *cmp){
    LNode *cur = NULL;
    for(cur = L->head.next;cur !=&L->head ;cur = cur->next){
       if(cmp(key,cur->data)==0)
         break;
    }
    return cur;
}
LL_ERROR llist_delete(LLIST *L,const void *key,llist_cmp *cmp){
    LNode *node = find_(L,key,cmp);
    if(node == &L->head){
        return LLIST_ERROR_DELETE;
    }else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node->data);
        free(node);
        return LLIST_ERROR_OK;
    }
}
LL_ERROR llist_fetch(LLIST *L,const void *key,llist_cmp *cmp,void *data){
    LNode *node = find_(L,key,cmp);
    if(node == &L->head){
        return LLIST_ERROR_FETCH;
    }else{
        node->next->prev = node->prev;
        node->prev->next = node->next;
        if(data !=NULL)
            memcpy(data,node->data,L->size);
        free(node->data);
        free(node);
        return LLIST_ERROR_OK;
    }
}

void *llist_find(LLIST *L,const void *key,llist_cmp *cmp){
    LNode *node = find_(L,key,cmp);
    return node->data;
}
LL_ERROR llist_travel(LLIST *L,llist_op *op){
    if(L == NULL)
        return LLIST_ERROR_NULL;
    LNode *cur = NULL;
    for(cur=L->head.next;cur !=&L->head;cur=cur->next){
        op(cur->data);
    }
    return LLIST_ERROR_OK;
}

void llist_destory(LLIST *L){
    if(L == NULL)
      return;
    int i=0;
    LNode *cur = NULL,*next = NULL;
    for(cur = L->head.next;cur != &L->head;cur = next){
        next = cur->next;
         free(cur->data);
         free(cur);
    } 
    free(L);
}








#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"
LLIST *llist_createbysize(int init_size){
    LLIST *me = malloc(init_size);
    if(me == NULL)
      return NULL;
    me->size = init_size;
    me->head.prev= &me->head;
    me->head.next= &me->head;
    return me;
}
LL_ERROR llist_create(LLIST **L,int init_size){
    if(*L == NULL)
      return LLIST_ERROR_FLASE;
    LLIST *me = malloc(init_size);
    if(me == NULL)
      return LLIST_ERROR_FLASE;
    me->size = init_size;
    me->head.prev= &me->head;
    me->head.next= &me->head;
    *L = me;
    return LLIST_ERROR_TRUE;
}

LL_ERROR llist_insert(LLIST *L,const void *data,LL_MODE mode){
    if(L == NULL)
      return LLIST_ERROR_FLASE;

    LNode *newNode = NULL;
    newNode = malloc(sizeof(*newNode)+L->size);
    if(newNode == NULL)
        return LLIST_ERROR_FLASE;
    newNode->next = NULL;
    newNode->prev = NULL;
    memcpy(newNode->data,data,L->size);

    if(mode == LLIST_MODE_FORWARD){
    newNode->prev = &L->head;
    newNode->next = L->head.next;
   }else if(mode == LLIST_MODE_BACKWORD){
    newNode->prev = L->head.prev;
    newNode->next = &L->head;
   }else{
    return LLIST_ERROR_FLASE;
   }
    newNode->prev->next = newNode;
    newNode->next->prev = newNode;
    return LLIST_ERROR_TRUE;
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
        return LLIST_ERROR_FLASE;
    }else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node);
        return LLIST_ERROR_TRUE;
    }
}
LL_ERROR llist_fetch(LLIST *L,const void *key,llist_cmp *cmp,void *data){
    LNode *node = find_(L,key,cmp);
    if(node == &L->head){
        return LLIST_ERROR_FLASE;
    }else{
        node->next->prev = node->prev;
        node->prev->next = node->next;
        if(data !=NULL)
            memcpy(data,node->data,L->size);
        free(node);
        return LLIST_ERROR_TRUE;
    }
}

void *llist_find(LLIST *L,const void *key,llist_cmp *cmp){
    LNode *node = find_(L,key,cmp);
	if(node == &L->head)
		return NULL;
	return node->data;
	
}
LL_ERROR llist_travel(LLIST *L,llist_op *op){
    if(L == NULL)
        return LLIST_ERROR_FLASE;
    LNode *cur = NULL;
    for(cur=L->head.next;cur !=&L->head;cur=cur->next){
        op(cur->data);
    }
    return LLIST_ERROR_TRUE;
}

void llist_destory(LLIST *L){
    if(L == NULL)
      return;
    int i=0;
    LNode *cur = NULL,*next = NULL;
    for(cur = L->head.next;cur != &L->head;cur = next){
        next = cur->next;
         free(cur);
    } 
    free(L);
}








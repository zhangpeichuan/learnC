#include <stdio.h>
#include <stdlib.h>

#include "list.h"




list * list_create(){
    list *p = malloc(sizeof(*p));
    if(p == NULL)
        return NULL;
    p->next = NULL;
    return p;
}

int list_insert_at(list *p,int i,datatype *data){
    if(i < 0 || p == NULL) 
      return -1;
    int j = 0;
    list *q=p,*node;
    while(j<i && q->next !=NULL){
        q = q->next;
        j++;
    }
    if(i!=j){
        printf("当前链表只能插入%d位置 想要插入位置是%d\n",j,i);
    }
    node = list_create();
    node->data = *data;
    node->next = q->next;
    q->next = node;
    return 0;
}
int list_order_insert(list *p,datatype *data){
    if(p == NULL) 
        return -1;
    list *q = p;
    int j = 0;
    while(q->next != NULL && q->next->data < *data){
        q = q->next;
        j++;
    }
    printf("当前链表插入%d位置\n",j);
    list *node = list_create();
    if(node ==NULL) return -1;
    node->data = *data;
    node->next = q->next;
    q->next = node;

    return 0;
} 

int list_delete_at(list *p,int i,datatype *data){
    if(i < 0 || p == NULL)
      return -1;

    int j = 0;
    list *q = p;
    while(j<i && q->next && p->next!= NULL){
        if(q->next->data == *data){
            list *node = q->next;
            q->next = node->next;
            free(node);
            return 0;
        }else{
            q = q->next ;
            j++;
        }
    }
    return -1;
} 
int list_delete(list *p,datatype *data){
    if(p == NULL) 
      return -1;
    list *q = p;
    int j=0;
    while(q->next && q->next !=NULL){
        if(q->next->data == *data){
            list *node = q->next;
            q->next = node->next;
            free(node);
            return 0;
        }else{
            q = q->next;
            j++;
        }
    }  
    return -1;
}

int list_isempty(list *p){
    int result = (p->next == NULL) ? 0:-1;
    return result;
}
int list_setempty(list *p){
     if(p == NULL) 
        return -1;
    list *head = p->next;
    list *node;
    while(head->next != NULL){
        node = head->next;
        head->next = node->next;
        list_destory(node);
    }
    return 0;
}

int list_display(list *p){
     if(list_isempty(p) ==0) 
        return -1;
 
    list *head = p->next;
    while(head !=NULL){
        printf("%d ",head->data);
        head = head->next;
    }
    printf("\n");
    return 0;
} 

void list_destory(list *p){
    list *node;
    list *next;
    for(node = p->next;node != NULL;node = node->next){
        free(node);
    }
    free(p);
} 



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define JOSE_NR    8 

typedef struct node_st {
    int         data;
    struct node_st   *next;
}LNode;

LNode *jose_create(int n){
    int i = 1;
    LNode   *me = NULL,*node = NULL,*cur = NULL;
    me = malloc(sizeof(*me));
    if(me == NULL)
      return NULL;
    me->data = i;
    me->next = me;
    cur = me;
    i++;
    for(;i<=n;i++){
       node = malloc(sizeof(*node));
        if(node == NULL)
            return NULL;
        node->data=i;
        node->next=me;              
        
        
        cur->next = node;
        cur = node;
    }
    return me;
}
void jose_show(LNode *L){
    if(L == NULL)
      return;
    LNode *p = L;
    while(L != p->next){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("%d \n",p->data);
}
void jose_kill(LNode **list ,int n){
    int i=1;
    LNode *cur = *list,*node;
    while(cur != cur->next){
        while(i<n && cur !=cur->next){
            node = cur;
            cur = cur->next;
            i++;
        }
         printf("kill %d \n",cur->data);
        node->next = cur->next;
        free(cur);
        cur = node->next;
        i=1;
    }
    printf("剩余 %d\n",cur->data);
    *list = cur;
}
int main(){

    LNode *list= NULL;
    int  n=3;
    list = jose_create(JOSE_NR);
    if(list == NULL)
        exit(1);
    jose_show(list);
    
    jose_kill(&list,n);
    jose_show(list);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

struct node_st{
    int     coef;
    int     exp;
    struct  node_st *next;
};
struct node_st *poly_create(int a[][2],int n)
{
    struct node_st *me;
    struct node_st *newnode,*cur;
    me = malloc(sizeof(*me));
    if(me == NULL)
        return NULL;
    me->next = NULL;
    int i;
    cur = me;
    for(i=0;i<n;i++){
       newnode = malloc(sizeof(*newnode));
       if(newnode == NULL)
            return NULL;
       newnode->next = NULL;
       newnode->coef = a[i][0];
       newnode->exp = a[i][1];
        
       cur->next = newnode;
       cur = newnode;
    }
    return me;
}
void poly_show(struct node_st *me){
    struct node_st *cur;
    for(cur = me->next;cur !=NULL;cur = cur->next){
        printf("%dx^%d ",cur->coef,cur->exp);
    }
    printf("\n");
    
}
void poly_union(struct node_st *p1,struct node_st *p2){
    struct node_st *q1,*q2;
    q1 = p1->next;
    q2 = p2->next;
    
    struct node_st *node;
    node = p1;

    while(q1 && q2){
        if(q1->exp < q2->exp){
            node->next = q1;
            node = q1;
            q1 = q1->next;
        }else if (q1->exp > q2->exp){
            node->next = q2;
            node = q2;
            q2 = q2->next;
        }else{
            q1->coef +=q2->coef;
            if(q1->coef){
                node->next = q1;
                node = q1;
            }
            q1 = q1->next;
            q2 = q2->next;
        }
    }

    if(q1 == NULL)
        node->next = q2;
    else
        node->next = q1;


}
int main(){
    int a[][2]={{5,0},{2,1},{8,8},{3,16}};
    int b[][2]={{6,1},{16,6},{-8,8}};

    struct node_st *p1,*p2;

    p1 = poly_create(a,4);
    if(p1 == NULL)
        exit(1);
    p2 = poly_create(b,3);
    if(p2 == NULL)
        exit(1);
    poly_show(p1);
    poly_show(p2);

    poly_union(p1,p2);
    poly_show(p1);

    return 0;
}

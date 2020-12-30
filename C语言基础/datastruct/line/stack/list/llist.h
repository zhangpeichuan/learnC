#ifndef LLIST_H__
#define LLIST_H__

typedef void llist_op(const void *);
typedef int llist_cmp(const void *,const void *);

typedef enum LLIST_MODE{
    LLIST_MODE_FORWARD      =1,
    LLIST_MODE_BACKWORD     =2
}LL_MODE;
typedef enum LLIST_ERROR{
    LLIST_ERROR_FLASE       = -1,
    LLIST_ERROR_TRUE,
}LL_ERROR;
typedef struct llist_node_st{
    struct llist_node_st *prev;
    struct llist_node_st *next;
    char	data[0];//0和1的区别
}LNode;
typedef struct llist_st {
    int     size;
    struct  llist_node_st head;
}LLIST;

LLIST *llist_create(int init_size);

LL_ERROR llist_insert(LLIST *L,const void *data,LL_MODE mode);

LL_ERROR llist_delete(LLIST *L,const void *key,llist_cmp *cmp);

void *llist_find(LLIST *L,const void *key,llist_cmp *cmp);

LL_ERROR llist_fetch(LLIST *L,const void *key,llist_cmp *cmp,void *data);

LL_ERROR llist_travel(LLIST *L,llist_op *op);

void llist_destory(LLIST *L);

#endif

#ifndef LLIST_H__
#define LLIST_H__

typedef void llist_op(const void *);
typedef int llist_cmp(const void *,const void *);

typedef enum LLIST_MODE{
    LLIST_MODE_FORWARD      =1,
    LLIST_MODE_BACKWORD     =2
}LL_MODE;
typedef enum LLIST_ERROR{
    LLIST_ERROR_OK,         
    LLIST_ERROR_NULL,
    LLIST_ERROR_CREATE,
    LLIST_ERROR_DELETE,
    LLIST_ERROR_INSERT,
    LLIST_ERROR_FIND,
    LLIST_ERROR_TRAVEL,
    LLIST_ERROR_FETCH,
    LLIST_ERROR_DESTORY

}LL_ERROR;
typedef struct llist_node_st{
    void *data;
    struct llist_node_st *prev;
    struct llist_node_st *next;
}LNode;
typedef struct llist_st {
    int     size;
    struct  llist_node_st head;
}LLIST;

LL_ERROR llist_create(LLIST **L,int init_size);

LL_ERROR llist_insert(LLIST *L,const void *data,LL_MODE mode);

LL_ERROR llist_delete(LLIST *L,const void *key,llist_cmp *cmp);

void *llist_find(LLIST *L,const void *key,llist_cmp *cmp);

LL_ERROR llist_fetch(LLIST *L,const void *key,llist_cmp *cmp,void *data);

LL_ERROR llist_travel(LLIST *L,llist_op *op);

void llist_destory(LLIST *L);

#endif

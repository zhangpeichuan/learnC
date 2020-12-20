#ifndef NOHEAD_LIST_H__
#define NOHEAD_LIST_H__


#define NAMESIZE    32
typedef struct score_st{
        int     id;
        char    name[NAMESIZE];
        int     math;
        int     chinese;
}datatype;
typedef struct node_st {
    datatype    data;
    struct node_st *next;
}nohead_list;


int list_insert(nohead_list **p,datatype *data);

int list_delete(nohead_list **p);

int list_find(nohead_list *p,datatype *data);
datatype * list_findById(nohead_list *p,int id);

int list_display(nohead_list *p);

int list_destory(nohead_list *p);

#endif

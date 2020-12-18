#ifndef SQLIST_H__
#define SQLIST_H__

#define DATASIZE    20
typedef int datatype;
typedef struct node_st{
    datatype data[DATASIZE];
    int last;
}sqlist;

sqlist *sqlist_create();
void sqlist_create1(sqlist **ptr);

int sqlist_insert(sqlist *sq,int index,datatype *data);

int sqlist_delete(sqlist *sq,int index);

int sqlist_find(sqlist *sq,datatype *data);

int sqlist_isempty(sqlist *sq);

int sqlist_getnum(sqlist *sq);

int sqlist_setempty(sqlist *sq);

int sqlist_display(sqlist *sq);

int sqlist_destory(sqlist *sq);

int sqlist_union(sqlist *sq1,sqlist *sq2);
#endif

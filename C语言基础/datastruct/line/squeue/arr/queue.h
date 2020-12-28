#ifndef QUEUE_H__
#define QUEUE_H__ 

#define MAXSIZE  5
typedef int  datatype;

typedef struct node_st {
    datatype    data[MAXSIZE];
    int         head,tail;

}queue;
queue *qu_create(void);

int qu_isempty(queue *qu);

int qu_enqueue(queue *qu,datatype *data);

void qu_travel(queue *qu);

int qu_dequeue(queue *qu,datatype *data);

void qu_clear(queue *qu);

void qu_destory(queue *qu);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
queue *qu_create(void){
    queue *me = malloc(sizeof(*me));
    if(me == NULL)
        return NULL;
    me->head = 0;
    me->tail = 0;
    return me;
}

int qu_isempty(queue *sq){
    int ret = -1;
    if(sq == NULL)
        return ret;
    if(sq->head == sq->tail)
        ret = 0;
    return ret;
}

int qu_enqueue(queue *sq,datatype *data){
    if(sq == NULL )
      return -1;
    if((sq->tail +1)%MAXSIZE == sq->head)
        return -1;
    sq->tail = (sq->tail+1)% MAXSIZE;
    sq->data[sq->tail] = *data;
        return 0;
}
void qu_travel(queue *sq){
    if(sq == NULL || qu_isempty(sq) == 0)
      return;
    if(sq->head == sq->tail)
        return;
    int i = (sq->head +1)%MAXSIZE;
    while(i !=sq->tail){
        printf("%d ",sq->data[i]);
        i = (i+1)%MAXSIZE;
    }
    printf("%d \n",sq->data[i]);
}
int qu_dequeue(queue *sq,datatype *data){
    if(sq == NULL || qu_isempty(sq) == 0)
      return -1;
    int i = (sq->head+1)%MAXSIZE;
    *data = sq->data[i];
    sq->head = i;
    return 0;
}
void qu_clear(queue *sq){
    sq->head = sq->tail;
}
void qu_destory(queue *sq){
    free(sq);
}

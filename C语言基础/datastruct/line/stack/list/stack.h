#ifndef STACK_H__
#define STACK_H__

#include <llist.h>
typedef LLIST   STACK;

STACK *stack_create(int size);

int stack_push(STACK *st,const void *data);

int stack_pop(STACK *st,void *data);

void stack_destory(STACK *st);




#endif

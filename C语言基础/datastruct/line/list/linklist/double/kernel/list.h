#ifndef LINUX_LIST_H__
#define LINUX_LIST_H__

struct list_head {
    struct list_head *next,*prev;
};
#define LIST_HEAD_INIT(name)    {&(name),&(name)}
#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)
static inline void INIT_LIST_HEAD(struct list_head *list){
    list->next = list;
    list->prev = list;
}

/*
ptr->cur
type->struct score_st
member->node
*/
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER) 
/**
  * container_of - cast a member of a structure out to the               containing structure                                                
  * @ptr:    the pointer to the member.
  * @type:   the type of the container struct this is embedded in.
  * @member: the name of the member within the struct.
  *
  */
 #define container_of(ptr, type, member) ({          \
     const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
     (type *)( (char *)__mptr - offsetof(type,member) );})

static inline void __list_add(struct list_head *new,struct list_head *prev,struct list_head *next){
    new->next = next;
    new->prev = prev;
    next->prev = new;
    prev->next = new;
}


#define __list_for_each(pos,head)\
    for(pos =(head)->next;pos != (head);pos = pos->next)
#define list_entry(ptr,type,member)\
    container_of(ptr,type,member);
static inline void list_add(struct list_head *new,struct list_head *head){
    __list_add(new,head,head->next);    
}
static inline void list_add_tail(struct list_head *new,struct list_head *head){
    __list_add(new,head,head->prev);
}
#endif

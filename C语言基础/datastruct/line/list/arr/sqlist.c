#include <stdio.h>
#include <stdlib.h>


#include "sqlist.h"

sqlist *sqlist_create(){
    sqlist *sq =NULL;
    sq = malloc(sizeof(sq));
    if(sq ==NULL) 
            exit(1);
    sq->last = -1;
    printf("[%s] %p %p %d\n",__FUNCTION__,sq,&sq,sq->last);
    return sq;
}
void sqlist_create1(sqlist **ptr){
    *ptr = malloc(sizeof(**ptr));
    if(*ptr ==NULL) return;

    (*ptr)->last = -1;
    printf("[%s] %p\n",__FUNCTION__,*ptr);

}

int sqlist_insert(sqlist *sq,int index,datatype *data){
    if(sq->last == DATASIZE-1) 
      return -1;

    if(index <0 || index > sq->last+1)
      return -2;
    
    int j= sq->last;
    for(;j>=index;j--){
        sq->data[j+1] = sq->data[j];
    }
   sq->data[index] = *data;
   sq->last++;
    return 0;
}

int sqlist_delete(sqlist *sq,int index){
    if(index<0 || index>sq->last)
      return -1;
    int j = index+1;
    for(;j<=sq->last;j++){
    sq->data[j-1]=sq->data[j];
    }
    sq->last--;
    return 0;
}

int sqlist_find(sqlist *sq,datatype *data){
    
    if(sqlist_isempty(sq)==0)
        return -1;


    int index = -1;
    for(int i=0;i<sq->last;i++){
        if(sq->data[i]==*data)
            index = i;
    }
    return index;
} 

int sqlist_isempty(sqlist *sq){
    if(sq->last == -1)
      return 0;
    return -1;
}

int sqlist_getnum(sqlist *sq){
    return sq->last+1;
}

int sqlist_setempty(sqlist *sq){
    sq->last = -1;
    return 0;
}

int sqlist_display(sqlist *sq){
    if(sq->last <0) return -1;
    int i;
    for(i=0;i<=sq->last;i++){
        printf("%d ",sq->data[i]);
    }
    printf("\n");
    return 0;
}

int sqlist_destory(sqlist *sq){
    sq->last = -1;
    free(sq);
    return 0;
}

int sqlist_union(sqlist *sq1,sqlist *sq2){
    
    int i,result=-1;

    for(i=0;i<sq2->last;i++){
        if(sqlist_find(sq1,&sq2->data[i])>=0){
            sqlist_insert(sq1,0,&sq2->data[i]);
            result=0;
        }
    }
    return result;

}

#include <stdio.h>
#include <stdlib.h>
#include "sqlist.h"
int main(){
    int arr[5]={12,23,34,45,56},i;
    int arr2[5]={80,90,21,45,56};
    sqlist *sq2;
    sqlist_create1(&sq2);
   sqlist *sq = sqlist_create();
    if(sq == NULL){
        fprintf(stderr,"sqlist_create() failed!\n");
        exit(1);
    }
    for(i = 0;i<sizeof(arr)/sizeof(*arr);i++){
        sqlist_insert(sq,0,&arr[i]);
        sqlist_insert(sq2,0,&arr2[i]);
        sqlist_display(sq);
    }
    
    printf("%d数据在%d位置\n",arr[2],sqlist_find(sq,&arr[2]));
    printf("%d数据在%d位置\n",arr[1],sqlist_find(sq,&arr[1]));
#if 0    
     for(i = 0;i<sizeof(arr)/sizeof(*arr);i++){
         sqlist_delete(sq,0);
        sqlist_display(sq);
    }
    printf("%d个数据\n",sqlist_getnum(sq));
    sqlist_setempty(sq);
#endif    
 
    int empty = sqlist_isempty(sq);
     if(empty ==0){
        printf("空线性表\n");
     }

     sqlist_display(sq);
     sqlist_display(sq2);
     sqlist_union(sq,sq2);
     sqlist_display(sq);

     sqlist_destory(sq);
     sqlist_destory(sq2);

    return 0;
}

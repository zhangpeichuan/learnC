#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(){

    datatype arr[] ={12,9,23,2,34,6,45}; 
    int i;
    list *link1 =NULL;
    link1 = list_create();
    if(link1 == NULL){
        exit(1);
    } 
    for(i = 0;i<sizeof(arr)/sizeof(*arr);i++){

        list_order_insert(link1,&arr[i]);
#if 0
        list_insert_at(link1,sizeof(arr)/sizeof(*arr)-i,&arr[i]);
        list_insert_at(link1,i,&arr[i]);
        list_insert_at(link1,0,&arr[i]);
#endif
        list_display(link1);
    }
    for(i = 0;i<sizeof(arr)/sizeof(*arr);i++){
        list_delete_at(link1,sizeof(arr)/sizeof(*arr)-i,&arr[i]);
#if 0
        list_delete_at(link1,0,&arr[i]);
        list_delete_at(link1,i,&arr[i]);
        list_delete(link1,&arr[i]);
#endif
        list_display(link1);
    }


    list_destory(link1);
    link1 = NULL;

    return 0;
}

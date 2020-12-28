#include <stdio.h>
#include <stdlib.h>

#include "queue.h"


int main(){
    datatype arr[5] = {2,34,89,25,9};
    queue *sq = NULL;
    datatype data;
    int i,ret;
    sq = qu_create();
    if(sq == NULL)
        exit(1);
    for(i=0;i<sizeof(arr)/sizeof(*arr);i++){
        ret = qu_enqueue(sq,&arr[i]);
        if(ret == -1){
            printf("enqueue failed\n");
        }
    }
    qu_travel(sq);
    for(i=0;i<sizeof(arr)/sizeof(*arr);i++){
        ret = qu_dequeue(sq,&data);
        if(ret == -1){
            printf("dequeue failed\n");
        }else{
            printf("dequeue %d \n",data);
            qu_travel(sq);
        }
    }

    qu_destory(sq);
    exit(0);
}

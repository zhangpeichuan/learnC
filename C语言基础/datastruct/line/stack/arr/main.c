#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"


int main(){
    sqstack *st = NULL;
    datatype arr[] = {19,23,9,45,67};
    int i,ret;
    st = st_create();
    if(st == NULL)
      exit(1);
    for(i= 0;i<sizeof(arr)/sizeof(*arr);i++){
        st_push(st,&arr[i]);
    }
    st_travel(st);
    datatype tmp = 1;

    ret = st_push(st,&tmp);
    if(ret == -1)
        printf("push fail()\n");
    st_travel(st);

    datatype *data;
    while(st_pop(st,data) == 0){
        printf("pop: %d \n",*data);
    } 

    st_destory(st);
    exit(0);
}

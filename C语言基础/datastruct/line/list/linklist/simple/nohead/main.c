#include <stdio.h>
#include <stdlib.h>
#include "nohead_list.h"

int main(){

    int i,result;    
    //声明指针需要指向NULL，否则导致程序异常
    nohead_list *link1 = NULL;
    datatype tmp;
    datatype arr[6];
    for(i = 0;i<7;i++){
        tmp.id = i;
        snprintf(tmp.name,NAMESIZE,"stu%d",i);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        arr[i] = tmp;
        result = list_insert(&link1,&tmp);
        if(result ==-1)
            exit(1);
    }
    list_display(link1);
    list_find(link1,&arr[3]);
    datatype *data = list_findById(link1,2);
    if(data != NULL){
        printf("查找到id=%d name=%s math=%d chinese=%d\n",data->id,data->name,data->math,data->chinese);
    }
    list_delete(&link1);
    list_display(link1);

    list_destory(link1);
    list_display(link1);
    link1 = NULL;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void compare(){
    char * name[5] = {"Follow me","Basic","Great","Fortra","Computer"};
    int i,j,k,length = sizeof(name)/sizeof(name[0]); 
    char * tmp;

   

   //选择排序
    for(i=0;i<length-1;i++){
        k = i;
        for(j=i+1;j<length;j++){
            if(strcmp(name[k],name[j])>0){
             k = j;
            }
        }
        if(k != i){
            tmp = name[i];
            name[i] = name[k];
            name[k] = tmp;
        }
    }

    for(i = 0;i< length;i++){
        puts(name[i]);
    }



}
int main (){
   compare(); 

    return 0;
}

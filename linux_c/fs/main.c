#include <stdio.h>
#include <stdlib.h>
#include <glob.h>

int errfunc(const char *epath,int eerrno){

    return 0;
}

int main(int argc,char **argv){
    int i=0;
    printf("%d \n",argc);    
    // for(i = 0;argv[i] != NULL ;argv++){
    //     printf("%s\n",argv[i]);
    // }
    char **tmp = argv;
    for(i=0;i<argc;i++){
        printf("%s \n",*tmp++);
    }

    return 0;
}
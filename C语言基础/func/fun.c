#include <stdio.h>
#include <stdlib.h>

int main (int argc,char *argv[]){
    
     for(int i=0;i<argc;i++){

        printf("参数是%s \n",argv[i]);

    }    
 
    printf("参数个数 %d \n",argc);

  
    printf("Hello World\n");

    return 0;
}

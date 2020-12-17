#include <stdio.h>
#include <stdlib.h>




int main(void){
    int num = 5,i;
    int *p;

    p = malloc(sizeof(int)* num);
    
    if(p ==NULL) exit(0);

    for(i=0;i<num;i++){
        scanf("%d",&p[i]);
    }

    for(i=0;i<num;i++){
        printf("%d ",p[i]);
    }
    printf("\n");
    free(p);
    return 0;
}

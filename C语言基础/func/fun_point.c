#include <stdio.h>
#include <stdlib.h>

int add(int x,int y){
    printf("[%s] %d x = %d y = %d \n",__FUNCTION__,__LINE__,x,y);

    return x + y;
}
int sub(int x,int y){
    printf("[%s] %d x = %d y = %d \n",__FUNCTION__,__LINE__,x,y);

    return x - y;

}

int main(){

    int a = 3,b =5;
    int ret;
#if 0
    int (*p_add)(int ,int ) = add;
    int (*p_sub)(int ,int ) = sub;

    ret = add(a,b);

    printf("%d\n",ret);

//    p_add = add;

    ret = p_add(b,a);

    printf("%d\n",ret);

    ret = p_sub(b,a);

    printf("%d\n",ret);
#endif
    int (*funcp[2])(int,int) = {add,sub};
    for(int i=0;i<2;i++){
        ret = funcp[i](a,b);
        printf("%d\n",ret);
    }


   return 0;
}

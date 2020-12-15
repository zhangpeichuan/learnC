#include <stdio.h>
#include <stdlib.h>


void a(void){
    printf("[%s] begin!\n",__FUNCTION__);
    printf("[%s] call a()!\n",__FUNCTION__);
    b();
    printf("[%s] returned!\n",__FUNCTION__);
    printf("[%s] end!\n",__FUNCTION__);
}
void b(void){
    printf("[%s] begin!\n",__FUNCTION__);
    printf("[%s] call b()!\n",__FUNCTION__);
    c();
    printf("[%s] returned!\n",__FUNCTION__);
    printf("[%s] end!\n",__FUNCTION__);
}
void c(void){
    printf("[%s] begin!\n",__FUNCTION__);
    printf("[%s] call c()!\n",__FUNCTION__);
    printf("[%s] returned!\n",__FUNCTION__);
    printf("[%s] end!\n",__FUNCTION__);
}
int main(){

    printf("[%s] begin!\n",__FUNCTION__);
    printf("[%s] call a()!\n",__FUNCTION__);
    a();
    printf("[%s] returned!\n",__FUNCTION__);
    printf("[%s] end!\n",__FUNCTION__);
    return 0;
}

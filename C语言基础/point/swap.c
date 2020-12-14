#include <stdio.h>
#include <stdlib.h>

static void swap1(int *a ,int *b){
    int tmp = 0;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
static void swap2(int **a ,int **b){
    int tmp = **a;
    **a = **b;
    **b = tmp;
}

int main(){
    int a = 3;
    int b = 4;

    int *p,*q;
    p = &a;
    q = &b;
    printf("%p --> a = %d %p --> b = %d \n",&a,a,&b,b);
    swap1(p,q);
    printf("一级指针%p -->  a = %d %p --> b = %d \n",&a,a,&b,b);
    swap2(&p,&q);
    printf("二级指针 %p-->  a = %d %p --> b = %d \n",&a,a,&b,b);
    return 0;
}

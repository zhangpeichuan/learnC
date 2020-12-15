#include <stdio.h>
#include <stdlib.h>

//值传递
int print_value(int a, int b){
    //形式参数
    printf("%p --> a=%d %p --> b= %d \n",&a,a,&b,b);
    return 0;
}
//地址传递
void swap(int * p,int *q){
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}
int main(){
    //实际参数
    int i = 3,j = 5;

    printf("%p --> i=%d %p --> j= %d \n",&i,i,&j,j);
    print_value(i,j);


    printf("%p --> i=%d %p --> j= %d \n",&i,i,&j,j);
    swap(&i,&j);
    printf("%p --> i=%d %p --> j= %d \n",&i,i,&j,j);





    return 0;
}

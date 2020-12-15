#include <stdio.h>
#include <stdlib.h>



static int factorial(int n){
    if(n < 0) return -1;

    if (n == 0|| n ==1) return 1;

    return factorial(n-1)*n;

}
//最初是使用两个变量for循环，后来用数组下标，现在用递归
static int fibonacci(int n){
    if(n == 0 ) return 0;
    if(n == 1 ) return 1;

    return fibonacci(n-1)+fibonacci(n-2);
}


int main(void){

    int i;

    for(int i=0;i<10;i++){
        int sum1 = factorial(i);
        int sum2 = fibonacci(i);
        printf("[factorial%d] = %d \n",i,sum1);
        printf("[fibonacci[%d] = %d \n",i,sum2);
        

    }

    scanf("%d",&i);
    printf("factorial %d \n",factorial(i));
    printf("fibonacci %d \n",fibonacci(i));


}

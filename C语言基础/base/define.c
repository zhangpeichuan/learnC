#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926
#define ADD (2+3)

//系统层面内核方面使用宏
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MAX1(a,b) ({typeof(a) A=a, B=b; (A > B ? A : B);})
#if 0
//应用层面开发需要函数
int max (int a, int b)
{
    return a > b ? a : b;
}
#endif
int main()
{

    int i=5,j=3;


    printf("i = %d\n j=%d \n",i,j);
    printf("%d\n ",MAX1((i++),(j++)));
    printf("i = %d\n j=%d \n",i,j);

/*
    printf("i = %d\n j=%d \n",i,j);
    printf("%d\n ",MAX((++i),(++j)));
    printf("i = %d\n j=%d \n",i,j);
*/


    return 0;
}

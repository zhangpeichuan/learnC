#include <stdio.h>
#include <stdlib.h>
/*  int a;变量
 *  const int a ;常量 常量不能直接更改，但是可以通过指针间接访问进行修改
 *  int const a ;
 *
 *  const int *p ;常量指针,指针的指向可以发生变化，但是指针指向的值不能改变,即指针指向的目标变量是不能改变的
 *  int const *p ；常量指针
 *
 *  int *const p ;指针常量 ，指针的指向不能发生变化，但是指针指向的目标变量可以发生变化
 *  const int *const p;即是指针常量又是常量指针
 *
 * */ 
/*
保存常量方法：
1、宏
2、const 检查语法
*/
#define PI  3.14
int main(){

#if 0    
    //2 * PI * R·
    const float pi = 3.14;
//F    pi = 3.14159
    float *p = &pi;
    
    printf("&pi = %p  pi = %f\n",&pi,pi);
    *p  = 3.14159;
    printf("&pi = %p  pi = %f\n",&pi,pi);


    printf("*p = %p p = %f\n",&p,*p );
#endif

//常量指针与指针常量
#if 1
    int i = 3,j=100;
    const int *p = &i;

    printf("&i= %p i= %d \n",&i,i);
    printf("&j= %p j= %d \n",&j,j);
    printf("常量指针&p = %p p= %d \n",p,*p);
//T i = 10 ; F *p = 10;    
    i = 10;
    printf("常量指针&p = %p p= %d 常量修改 \n",p,*p);
    p =&j;
    printf("常量指针&p = %p p= %d 指针指向-->j %p\n",p,*p,&j);
    int * const q = &i;
    printf("指针常量&q = %p 指向i = %d 初始化\n",q,*q);
    *q = 8;
    printf("指针常量&q = %p q = %d 指针修改内容\n",q,*q);
    *q = i;
    printf("指针常量&q = %p q = %d %p -->指向i --> %d \n",q,*q,&i,i);
    *q = j;
    printf("指针常量&q = %p q = %d %p --> 指向j %d\n",q,*q,&j,j);

    const int *const P = &i;
    printf("P %p --> %d\n",P,*P);
//F    P = &j;
//F    *p = 10;

#endif
    






    return 0;
}

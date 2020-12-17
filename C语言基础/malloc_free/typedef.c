#include <stdio.h>
#include <stdlib.h>

/*
typedef int INT;
define  INT int

INT i;--> int i;

#deinfe     IP  int *
typedef     int*    IP

IP  p,q; -->    int *p,q;
IP  p,q; -->    int *p,*q;


typedef int ARR[6]; ---> int [6] ->ARR
ARR 6;  --> int a[6]

struct node_st
{
    int i;
    float f;
};
typedef struct node_st NODE
NODE a;--> struct node_st a;
NODE *p;--> struct node_st  *p;

typedef struct node_st *NODE
NODE p; --> struct node_st *p;

结构体和结构体指针
typedef struct {
    int i;
    float f;
}NODE,*NODEP;

函数
typedef int FUNC(int);  int(int)     FUNC;
FUNC    f; -> int f(int);

函数指针
typedef int * FUNCP(int)
FUNCP p;--> int *p(int)

指针变量p 指向返回值是int *参数为int的函数
指向函数的指针 指向的是指针函数的变量
typedef int *(*FUNCP)(int)
FUNCP p； --> int *(*p)(int)



*/


typedef int ARR[6];
typedef int[6] ARR;
typedef int INT;
#define int ARR[6]
typedef int[6] ARR;
#define int ARR[6]
int main(){
    INT i = 100;
    ARR a;
    int a;
    printf("sizeof(INT)%lu %d \n",sizeof(INT),i);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define M   3
#define N   4
/*
 *  int a[M][N] = {.....}
 *  int *q = *a;
 *  int (*q)[N] = a
 *  a[i][j]  *(a+i)+j  a[i]+j  p[i]  *p  q[i][j]   *q     q       p+3   q+2
 *                                  *(q+0)
 * ->int        int*   int*    int  int     int  int* int(*)[N]   int* int(*)[N]       
 * */
static void print_score(int (*p)[N],int num);
static float  average_score(int * p,int n);
int * find_num(int (*p)[N],int num);
 
static void  fun_sum(int (*p)[N],int m,int n);
//N不能省略
static void print_douarr1(int (*p)[N],int m,int n){
    printf("sizeof(p) %lu\n",sizeof(p));
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%4d",*(*(p+i)+j));
        }
        printf("\n");
    }
    printf("\n");
}
//N不能省略
static void print_douarr2(int p[][N],int m,int n){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%4d",p[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
static void print_douarr(int *p,int n){
    int i ;
    for(i=0;i<n;i++){
        printf("%4d",p[i]);
    }
    printf("\n");
}
int main(){
    int a[M][N] = {1,2,3,4,5,6,7,8,9,10,11,12}; 
    print_douarr(&a[0][0],M*N);//*a a[0] *(a+0)
//    printf("sizeof(a) %lu sieof(*a) %lu\n",sizeof(a),sizeof(*a));
//    print_douarr1(*a,M,N);
//    print_douarr2(*a,M,N);
    
    int num = 1;
    int *res;
    float result = average_score(*a,M*N);
    printf("average = %.2f\n",result);
    
    print_score(a,num);    
    res = find_num(a,3);
    if(res !=NULL){
        for(int i = 0;i<N;i++){
        printf("%d ",res[i]);
        }
        printf("\n");
    }



    return 0;
}
//矩阵求和，求平均成绩
static float  average_score(int * p,int n){
    int i;
    float sum=0.0;
    for(i=0;i<n;i++){
        sum +=p[i];
    }
    return sum/n;
}
//指针函数
int * find_num(int (*p)[N],int num){
        if(num>M-1) return NULL;
    return *(p+num);
}
static void print_score(int (*p)[N],int num){
    int i;
    for(i = 0;i<N;i++){
        printf("%d ",*(*(p+num)+i));
    }
    printf("\n");
}



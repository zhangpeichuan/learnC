#include <stdio.h>
#include <stdlib.h>
/*
 *int a[N] = 1 2 3 4 5
 *int *p = a;
 *->a   *a  a[0]    &a[3]   p[i]    p   *p  p+1 
 *      *(a+0)
 * int* int int     int*    int    int* int int*    
 *
 * */
//[] == *

static void reverse_array(char *p,int length);
//打印int类型指针数组
void print_int_point_array(int *ptr[],int length);

//打印是int的数组，通过int类型的指针偏移
static void print_array0(int *p,int length){
    printf("[%s] sizeof *p %lu length= %d\n ",__FUNCTION__,sizeof(p),length);
    int i;
    for(i=0;i<length;i++){
    printf("%d ",*(p+i));
    }
    printf("\n");
}
//打印int类型数组，通过数组下标
static void print_array1(int p[],int length){
    printf("[%s] sizeof *p %lu length= %d\n ",__FUNCTION__,sizeof(*p),length);
    int i;
    for(i=0;i<length;i++){
    printf("%d ",p[i]);
    }
    printf("\n");
}

static void reverse_array1(int arr[],int length){
    printf("[%s] sizeof *p %lu length= %d\n ",__FUNCTION__,sizeof(*arr),length);
    int i,j;
    for(i=0,j=length-1;i<j;i++,j--){
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
    }
}
static void reverse_array2(int *p,int length){
    printf("[%s] sizeof *p %lu length= %d\n ",__FUNCTION__,sizeof(*p),length);
    int *q=p+length-1;
    while(p<q)
    {
        int tmp=*p;
        *p = *q;
        *q = tmp;
        q--;
        p++;
    }

}
int main (){
    int n[5] = {1,2,3,4,5};
    printf("%s sizeof = %lu \n",__FUNCTION__,sizeof(n));
    print_array0(n,sizeof(n)/sizeof(*n));
    reverse_array1(n,sizeof(n)/sizeof(*n));
    print_array1(n,sizeof(n)/sizeof(*n));
    reverse_array2(n,sizeof(n)/sizeof(*n));
    print_array1(n,sizeof(n)/sizeof(*n));

    int *m[10];

    for(int i=0;i<10;i++){
        int *p = (int *)malloc(sizeof(int));
        *p = i;
        m[i] = p;
    }
    print_int_point_array(m,sizeof(m)/sizeof(*m));
    //打印字符数组
    char ch[] = {'a','b','c','d'};
    for(int i=0;i<4;i++){
        printf("%c ",ch[i]);
    }
    printf("\n");
 
    reverse_array(ch,sizeof(ch)/sizeof(*ch));
    for(int i=0;i<4;i++){
        printf("%c ",ch[i]);
    }
    printf("\n");
    return 0;
}

//打印int类型指针数组
void print_int_point_array(int *ptr[],int length){
    printf("int *ptr sizeof(%lu) %d\n",sizeof(*ptr),length);
    int i;

    for(i=0;i<length;i++){
        int *q = *(ptr+i);
        printf("int *ptr[%d] = %d\n",i,*q);
    }
    printf("\n");
} 
static void reverse_array(char *p,int length){
    printf("[%s] %d\n",__FUNCTION__,__LINE__);
    char *q = p+length-1;
    while(p<q){
        char tmp = *p;
        *p = *q;
        *q = tmp;
        p++;
        q--;
    }

}




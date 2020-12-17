#include <stdio.h>
#include <stdlib.h>

//产生内存泄漏
void func(int *p,int n){
    printf("[%s] %p\n",__FUNCTION__,&p);
    
    p = malloc(n);

    if(p==NULL) exit(1);
    
    printf("[%s] %p\n",__FUNCTION__,&p);

}
//两种 函数内部申请内存的方式
void func1(int **p,int n){
    *p = malloc(n);

    if(*p==NULL) exit(1);

}
void * func2(int *p,int n){
    p = malloc(n);

    if(p==NULL) exit(1);

    return p;
}

int main(){

    int num = 100;
    int *p=NULL;
#if 0    
    func(p,num);
    free(p);
#endif
    //%p *p 十六进制打印指针的内容
    p = malloc(num);

    if(p==NULL) exit(1);
    printf("%p--> %d \n",*p);
    *p = 10;
    
    printf("%p --> %d \n",*p,*p);
    free(p);//p = NULL;//释放过后的指针，需要立马指向NULL
    
    //free过后的指针再次被赋值后，地址将会发生变化,这是野指针,退租了不能再访问了
    
    *p = 123;
    printf("%p --> %d \n",*p,*p);

    exit(0);
}

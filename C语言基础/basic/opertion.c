#include <stdio.h>
#include <stdlib.h>

/*
 *
 + - * / % 
 *运算符在前，先进行计算，再取变量值使用
 *变量在前，先取变量值使用，再进行计算
 *
 *
 * */
int main()
{

    int i = 1;

//  i++;//表达式值1，i值为2
//  ++i;//表达式值位2，i值位2
    
    int j=10,value;
/*
    value = i++ + ++j;
    i;
    j=j+1;
    value=i+j;
    i=i+1;
 * */

//    value = i++ + ++i - i-- + --i;

    printf("i = %d\n ",i);
    printf("j = %d\n ",j);
    printf("value = %d\n ",value);


    value = --i + j++;
    /*
     i = i-1;
     value = i+j;
     j=j+1;
     * */
    printf("i = %d\n ",i);
    printf("j = %d\n ",j);
    printf("value = %d\n ",value);



    return 0;
}

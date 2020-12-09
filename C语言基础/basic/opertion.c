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
/*(n&(1<<i))?1:0
int 4字节，所以是32位进制，从bit0到bit31，所以i<<i，就是将1移位31，然后和n位与，用于将n的最高位去除，因为去除后如果是0，那么结果就是0.如果是1，结果就是一个正整数，所以这儿加问号正则表达式，来将结果变为0和1
按位与& 9级，移位6 问号表达式14级，所以 移位>>按位与>>问号表达式
*/
void print_binary(int n)
{
	int bit = sizeof(int)*8;
	int i;
	for(i= bit-1;i>=0;i--)
	{
		int bin =n & 1<< i?1:0;
			printf("%d",bin);
	}
	puts("");
}
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

//关系运算符|赋值运算符
	int a=1,b=2,c=3,d=4;
	int m=1,n=1;
	
//  (m=a>b) && (n=c>d);
	(m=a>b) || (n=c>d);

	printf("m =%d\n n=%d\n",m,n);

	a -= a *= a += 3;
	printf("a =%d \n ",a);

//强制类型转换
	float f = 3.9;

	a = (int)f;
	printf("a = %d\n",a);
	printf("f = %f\n",f);
	
	//位运算 << >>左右移动相当于*2 /2
	int flag1 = 6;
	int flag2 = 5;
	printf("flag1 %d flag2 %d \n",flag1,flag2);
	print_binary(flag1);
	print_binary(flag2);
	printf("flag1|flag2 ");
	print_binary(flag1|flag2);
	printf("flag1&flag2 ");
	print_binary(flag1&flag2);
	printf("flag1^flag2 ");
	print_binary(flag1^flag2);
	printf("flag1 %d\n",flag1);
	printf("flag1 <<%d\n",(flag1 <<1));
	printf("flag1 >>%d\n",(flag1 >>1));



    return 0;
}

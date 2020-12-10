#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
 *printf("修饰符",格式字符)
 */

#define STRSIZE 32
#define SEC_YEAR 60LL*60LL*24LL*365LL
//LL在整数后面标识LongLong类型，避免数据溢出




int main()
{
    printf("hello word!\n");
    int a = 567;
    printf("十进制 %d \n",a);
    printf("十六进制无符号整形%X \n",a);
    printf("八进制无符号整数%o \n",a);
    printf("不带符号十进制整数%u \n",a);
    printf("单一字符%c \n",a);
    printf("字符串%s \n","ABC");
	float b = 567.789;
	printf("指数形式浮点小数 %e \n",b);
	printf("指数形式浮点小数 %f \n",b);
	printf("百分号%%\n");


	//修饰符
	printf("%4d\n",a);
	float c = 123.456789;
	printf("b = %2f \n",b);
	printf("c = %20f \n",c);

	char str[STRSIZE]="helloworld";
    printf("str = %.5s[over]\n","ABC");
    printf("str = %-10.5s[over]\n","ABC");

	printf("十六进制无符号整形%#x \n",a);
    printf("十六进制无符号整形%#x \n",a);
    printf("八进制无符号整数%#o \n",a);
    printf("八进制无符号整数%#o \n",a);
    
	double dou = 123.456;
	long long l = 123456;

	printf("dou = %lf\n",dou);
	printf("ll  = %ld\n",l);
	//多个输出参数出现的问题,变参函数问题
	printf("printf 少参数验证%d %e \n",a);
	printf("printf 多参数验证%d %e \n",a,l,dou);
	printf("printf 参数验证%d %e \n",a,l);
	//缓冲器刷新问题
	printf("[%s:%d] before sleep",__FUNCTION__,__LINE__);
	sleep(3);
	printf("[%s:%d] after sleep",__FUNCTION__,__LINE__);
	printf("\n");
	printf("[%s:%d] before sleep \n",__FUNCTION__,__LINE__);
	sleep(3);
	printf("[%s:%d] after sleep \n",__FUNCTION__,__LINE__);

	printf("[%s:%d] before while \n",__FUNCTION__,__LINE__);
	while(3);
	printf("[%s:%d] after while",__FUNCTION__,__LINE__);


    return 0;
}

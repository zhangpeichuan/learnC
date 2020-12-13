#include <stdio.h>
#include <stdlib.h>
void test_nullpoint(){
	int i = 1;
	int * p = NULL ;
	int * q ;
	printf("i= %d \n",i);
	printf("&i= %p \n",&i);
	
	printf("q= %p \n",q);
	printf("&q= %p\n",&q);
	printf("* q= %d \n",*q);


	printf("p= %p \n",p);
	printf("&p= %p\n",&p);
	printf("* p= %d \n",*p);
}
// TYPE NAME = VALUE
/*
 *void * 百搭的数据类型，不确定数据类型
 * */
static void testvoidpoint(){
	int *p = NULL ;
	void *q = NULL;

//(F)段错误	*p = 1;
	printf(" %p\n",&p);
	printf("%d %p\n",*p,&p);
}
int main(){
	//test_nullpoint();
	testvoidpoint();	
	





	return 0;
}

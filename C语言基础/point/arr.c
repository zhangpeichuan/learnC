#include <stdio.h>
#include <stdlib.h>

// TYPE NAME = VALUE; a和p可以互换，a是常量，p是变量
// a[i] = *(a+i) = *(p+i) = p[i]
// &a[i] = a+i	=	p+i	=	&p[i]
static void test(){
	int a[3] = {1,2,3};
	int i;
	int *p;
//(F) a++ a = a+1
//	p++	p = p+1
//	p++ -> p = p+1
//	p+1
	p =a;
	for(i = 0;i<sizeof(a)/sizeof(a[0]);i++){
		printf("a[] %p  %d \n",a+i,a[i]);
		printf("p %p  %d \n",p+i,*(p+i));
	}
	printf("\n");
	for(i = 0;i<sizeof(a)/sizeof(*a);i++){
		printf("a[] %d a+i  %d p[] %d p+i %d \n",a[i],*(a+i),a[i],*(p+i));
		printf("&a[i] %p a+i  %p p+i %p &p[i] %p \n",&a[i],a+i,&p[i],p+i);
	}
	printf("\n");
}
static void test_operation_test(){
	int a[] = {5,1,7,2,8,3};
	int y;
	int *p =&a[1];
	
	y = (*--p)++;
	printf("%d \n",y);
	printf("a[0] %d \n",a[0]);
	printf("a[1] %d \n",a[1]);
	printf("%p \n",p);
	for(int i=0;i<6;i++){
		printf("%p-->%d\n",&p[i],p[i]);
	}
}
static void test_operation(){
/*
	int *p =(int [3]){1,2,3};
	int i;
	for(i=0;i<3;i++){
		printf("%p-->%d\n",&p[i],p[i]);
	}
*/
	int a[3];
	int *p=a;
	int i;
	for(i = 0;i<sizeof(a)/sizeof(*a);i++){
		printf("%p -->%d \n",&a[i],a[i]);
	}
	for(i = 0;i<sizeof(a)/sizeof(*a);i++){
		scanf("%d",p++);
	}

	p=a;
	for(i = 0;i<sizeof(a)/sizeof(*a);i++,p++){
		//printf("%p  %d \n",&a[i],a[i]);
		printf("%p-->%d \n",p,*p);
	}
	printf("\n");
}
int main(){
	
	test();
//	test_operation();	
//	test_operation_test();





	exit(0);
}

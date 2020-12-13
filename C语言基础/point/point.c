#include <stdio.h>
#include <stdlib.h>


// TYPE NAME = VALUE
//i		*p		**q
//&i	p		*q
static void point_usage(){
	int i = 1;
	int * p = &i;//int *p; p =&i;

	int ** q = &p;

	printf("i= %d \n",i);
	printf("&i= %p \n",&i);

	printf("p= %p \n",p);
	printf("&p= %p\n",&p);
	printf("*p= %d\n",*p);
	
	printf("q= %p\n",q);
	printf("&q= %p\n",&q);
	printf("**q= %d *q = %d\n",**q,*p);



}
static void sizeofPoint(){
	int		*i;
	float	*f;
	char	*c;
	double	*d;

	printf("int *i= %lu \n",sizeof(i));
	printf("float *f= %lu \n",sizeof(f));
	printf("char *c= %lu \n",sizeof(c));
	printf("double *d= %lu \n",sizeof(d));


	int *p;
	p=&i;
	c = &p;
	printf("i= %d \n",*i);
	printf("int *p= %d \n",*p);
	printf("c access p  = %d \n",*c);


}
int main(){
#if 0
	char c[4];
    int *p = NULL;
    p = (int *)(&c[0]);
    *p = 0X01020304;
    printf("%d--%d--%d--%d--",c[0],c[1],c[2],c[3]);
#endif
	point_usage();
	sizeofPoint();	

	



	return 0;
}

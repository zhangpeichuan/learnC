#include <stdio.h>
#include <stdlib.h>

//引入数组指针


int main(){

	int a[2][3] = {1,2,3,4,5,6};
	int i,j;

	int *p;
//(W)	p = a;
	int (*q)[3] = *a;
	p = &a[0][0];//&a[i][j],*(a+0),*a;
	printf("a %p  a+1 %p \n",a,a+1);
	printf("p %p  p+1 %p \n",p,p+1);
	printf("q %p  q+1 %p \n",q,q+1);
	for(i=0;i<2;i++){
		for(j=0;j<3;j++){
			printf("%p -->%d ",&a[i][j],a[i][j]);
			printf("%p -->%d ",*(a+i)+j,*(*(a+i)+j));
			printf("%p -->%d ",(p+i+j),*(p+i+j));
		}
		printf("\n");
	}

	p = &a[0][0];//*(a+0),*a;
	for(i=0;i<6;i++){
	printf("%d ",p[i]);
	}
	printf("\n");









	return 0;
}

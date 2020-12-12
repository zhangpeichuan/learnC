#include <stdio.h>
#include <stdlib.h>

#define M	3

int main(){
	int arr1[M];
	static int arr4[M];
	//arr ={4,5,6};(F)
	printf("sizeof  %d\n",sizeof(arr1));
	for(int i=0;i<M;i++){
		printf("输入int 数组");
		scanf("%d",&arr1[i]);
	}
	for(int i=0;i<M;i++){
		printf("%p %d \n",&arr1[i],arr1[i]);
	}
	arr1[3] = 10;
	printf("%p %d \n",&arr1[3],arr1[3]);
	for(int i=0;i<M;i++){
		printf("%p %d static\n",&arr4[i],arr4[i]);
	}
	return 0;
}

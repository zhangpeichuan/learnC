#include <stdio.h>
#include <stdlib.h>

#define		M		2
#define		N		3


int main(){
	int a[][N]={{1,2},{4}};
	//int a[M][N]={{1,2,3},{4}};
	int i,j;
#if 0
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			scanf("%d",&a[i][j]);
		}
	}
#endif

	//行指针的概念
	printf("%p--> a\n",a);
	printf("%p--> a+1\n",a+1);

	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf("%p--> %d ",&a[i][j],a[i][j]);
		}
		printf("\n");
	}


	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define		M		2
#define		N		3
#define		K		2


static void exchange(){
	int a[M][N]={{1,2,3},{4,5,6}},b[N][M];
	int i,j;
#if 0
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			scanf("%d",&a[i][j]);
		}
	}
#endif

	printf("%p--> a\n",&a);
	printf("%p--> b\n",&b);


	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			printf(" %d ",a[i][j]);
			b[j][i]=a[i][j];
		}
		printf("\n");
	}
	for(i=0;i<N;i++){
		for(j=0;j<M;j++){
			printf("%d ",b[i][j]);
		}
		printf("\n");
	}
}
static void sum(void){
	int a[5][4] = { {1,2,3},{4,5,6},{7,8,9},{10,11,12}};
	int i,j,sum_row,sum_colum;
	for(i=0;i<4;i++){
		for(j=0;j<3;j++){
			a[4][3] +=a[i][j];
			a[4][j] +=a[i][j];
			a[i][3] +=a[i][j];
		}
	}
	for(i=0;i<5;i++){
		for(j=0;j<4;j++){
			printf("%4d ",a[i][j]);

		}
		printf("\n");
	}



}
static void max(void){
	int a[M][N]={43,4,23,89,9,7};
	int i,j;
	int max = a[0][0],row = 0,colum = 0;
	for(i=0;i<M;i++){
		for(j=0;j<N;j++){
			if(max<a[i][j]){
				max = a[i][j];
				row = i;
				colum = j;
			}
		}
	}

	printf("max:a[%d][%d] = %d \n",row,colum,max);

}
static void mul(){
	int a[M][N] = {1,2,3,4,5,6} ;
	int b[N][K] = {1,0,0,1,1,0};
	int c[M][K] = {0};
	
	int i,j,k;
	for(i = 0;i<M;i++){
		for(j=0;j<K;j++){
			for(k=0;k<N;k++){
				c[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	for(i=0;i<M;i++){
		for(j=0;j<K;j++){
			printf("%4d",c[i][j]);
		}
	printf("\n");
	}
}
int main(void){
	//exchange();
	//max();
	//sum();
	mul();
	return 0;
}
